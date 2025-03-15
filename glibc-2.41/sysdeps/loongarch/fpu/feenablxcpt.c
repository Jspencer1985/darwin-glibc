/* Enable floating-point exceptions.
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

#include <fenv.h>
#include <fenv_libc.h>
#include <fpu_control.h>

int
feenableexcept (int excepts)
{
  unsigned int new_exc, old_exc;

  /* Get the current control word.  */
  _FPU_GETCW (new_exc);

  old_exc = (new_exc & ENABLE_MASK) << ENABLE_SHIFT;

  excepts &= FE_ALL_EXCEPT;

  new_exc |= excepts >> ENABLE_SHIFT;
  _FPU_SETCW (new_exc);

  return old_exc;
}
