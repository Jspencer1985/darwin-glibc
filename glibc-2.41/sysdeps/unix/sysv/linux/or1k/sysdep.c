/* OpenRISC wrapper for setting errno.
   Copyright (C) 2022-2025 Free Software Foundation, Inc.

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
   License along with the GNU C Library.  If not, see
   <https://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include <errno.h>

long int __syscall_error (long int err);
hidden_proto (__syscall_error)

/* This routine is jumped to by all the syscall handlers, to stash
   an error number into errno.  */
long int
__syscall_error (long int err)
{
  __set_errno (- err);
  return -1;
}
hidden_def (__syscall_error)
