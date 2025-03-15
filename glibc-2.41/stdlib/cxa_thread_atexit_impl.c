/* Register destructors for C++ TLS variables declared with thread_local.
   Copyright (C) 2013-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* CONCURRENCY NOTES:

   This documents concurrency for the non-POD TLS destructor registration,
   calling and destruction.  The functions __cxa_thread_atexit_impl,
   _dl_close_worker and __call_tls_dtors are the three main routines that may
   run concurrently and access shared data.  The shared data in all possible
   combinations of all three functions are the link map list, a link map for a
   DSO and the link map member l_tls_dtor_count.

   __cxa_thread_atexit_impl acquires the dl_load_lock before accessing any
   shared state and hence multiple of its instances can safely execute
   concurrently.

   _dl_close_worker acquires the dl_load_lock before accessing any shared state
   as well and hence can concurrently execute multiple of its own instances as
   well as those of __cxa_thread_atexit_impl safely.  Not all accesses to
   l_tls_dtor_count are protected by the dl_load_lock, so we need to
   synchronize using atomics.

   __call_tls_dtors accesses the l_tls_dtor_count without taking the lock; it
   decrements the value by one.  It does not need the big lock because it does
   not access any other shared state except for the current DSO link map and
   its member l_tls_dtor_count.

   Correspondingly, _dl_close_worker loads l_tls_dtor_count and if it is zero,
   unloads the DSO, thus deallocating the current link map.  This is the goal
   of maintaining l_tls_dtor_count - to unload the DSO and free resources if
   there are no pending destructors to be called.

   We want to eliminate the inconsistent state where the DSO is unloaded in
   _dl_close_worker before it is used in __call_tls_dtors.  This could happen
   if __call_tls_dtors uses the link map after it sets l_tls_dtor_count to 0,
   since _dl_close_worker will conclude from the 0 l_tls_dtor_count value that
   it is safe to unload the DSO.  Hence, to ensure that this does not happen,
   the following conditions must be met:

   1. In _dl_close_worker, the l_tls_dtor_count load happens before the DSO is
      unloaded and its link map is freed
   2. The link map dereference in __call_tls_dtors happens before the
      l_tls_dtor_count dereference.

   To ensure this, the l_tls_dtor_count decrement in __call_tls_dtors should
   have release semantics and the load in _dl_close_worker should have acquire
   semantics.

   Concurrent executions of __call_tls_dtors should only ensure that the value
   is accessed atomically; no reordering constraints need to be considered.
   Likewise for the increment of l_tls_dtor_count in __cxa_thread_atexit_impl.

   There is still a possibility on concurrent execution of _dl_close_worker and
   __call_tls_dtors where _dl_close_worker reads the value of l_tls_dtor_count
   as 1, __call_tls_dtors decrements the value of l_tls_dtor_count but
   _dl_close_worker does not unload the DSO, having read the old value.  This
   is not very different from a case where __call_tls_dtors is called after
   _dl_close_worker on the DSO and hence is an accepted execution.  */

#include <stdio.h>
#include <stdlib.h>
#include <ldsodefs.h>
#include <pointer_guard.h>

typedef void (*dtor_func) (void *);

struct dtor_list
{
  dtor_func func;
  void *obj;
  struct link_map *map;
  struct dtor_list *next;
};

static __thread struct dtor_list *tls_dtor_list;
static __thread void *dso_symbol_cache;
static __thread struct link_map *lm_cache;

/* Register a destructor for TLS variables declared with the 'thread_local'
   keyword.  This function is only called from code generated by the C++
   compiler.  FUNC is the destructor function and OBJ is the object to be
   passed to the destructor.  DSO_SYMBOL is the __dso_handle symbol that each
   DSO has at a unique address in its map, added from crtbegin.o during the
   linking phase.  */
int
__cxa_thread_atexit_impl (dtor_func func, void *obj, void *dso_symbol)
{
  PTR_MANGLE (func);

  /* Prepend.  */
  struct dtor_list *new = calloc (1, sizeof (struct dtor_list));
  if (__glibc_unlikely (new == NULL))
    __libc_fatal ("Fatal glibc error: failed to register TLS destructor: "
		  "out of memory\n");
  new->func = func;
  new->obj = obj;
  new->next = tls_dtor_list;
  tls_dtor_list = new;

  /* We have to acquire the big lock to prevent a racing dlclose from pulling
     our DSO from underneath us while we're setting up our destructor.  */
  __rtld_lock_lock_recursive (GL(dl_load_lock));

  /* See if we already encountered the DSO.  */
  if (__glibc_unlikely (dso_symbol_cache != dso_symbol))
    {
      ElfW(Addr) caller = (ElfW(Addr)) dso_symbol;

      struct link_map *l = _dl_find_dso_for_object (caller);

      /* If the address is not recognized the call comes from the main
	 program (we hope).  */
      lm_cache = l ? l : GL(dl_ns)[LM_ID_BASE]._ns_loaded;
    }

  /* This increment may only be concurrently observed either by the decrement
     in __call_tls_dtors since the other l_tls_dtor_count access in
     _dl_close_worker is protected by the dl_load_lock.  The execution in
     __call_tls_dtors does not really depend on this value beyond the fact that
     it should be atomic, so Relaxed MO should be sufficient.  */
  atomic_fetch_add_relaxed (&lm_cache->l_tls_dtor_count, 1);
  __rtld_lock_unlock_recursive (GL(dl_load_lock));

  new->map = lm_cache;

  return 0;
}

/* Call the destructors.  This is called either when a thread returns from the
   initial function or when the process exits via the exit function.  */
void
__call_tls_dtors (void)
{
  while (tls_dtor_list)
    {
      struct dtor_list *cur = tls_dtor_list;
      dtor_func func = cur->func;
      PTR_DEMANGLE (func);

      tls_dtor_list = tls_dtor_list->next;
      func (cur->obj);

      /* Ensure that the MAP dereference happens before
	 l_tls_dtor_count decrement.  That way, we protect this access from a
	 potential DSO unload in _dl_close_worker, which happens when
	 l_tls_dtor_count is 0.  See CONCURRENCY NOTES for more detail.  */
      atomic_fetch_add_release (&cur->map->l_tls_dtor_count, -1);
      free (cur);
    }
}
libc_hidden_def (__call_tls_dtors)
