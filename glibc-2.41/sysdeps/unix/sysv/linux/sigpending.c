/* Copyright (C) 1997-2025 Free Software Foundation, Inc.
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

#include <signal.h>
#include <sysdep.h>
#include <sigsetops.h>

/* Change the set of blocked signals to SET,
   wait until a signal arrives, and restore the set of blocked signals.  */
int
sigpending (sigset_t *set)
{
  return INLINE_SYSCALL_CALL (rt_sigpending, set, __NSIG_BYTES);
}
