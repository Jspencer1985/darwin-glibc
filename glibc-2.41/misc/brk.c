/* Copyright (C) 1991-2025 Free Software Foundation, Inc.
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

#include <errno.h>
#include <unistd.h>

/* sbrk.c expects this.  */
void *__curbrk;

/* Set the end of the process's data space to ADDR.
   Return 0 if successful, -1 if not.  */
int
__brk (void *addr)
{
  __set_errno (ENOSYS);
  return -1;
}
stub_warning (brk)

weak_alias (__brk, brk)
