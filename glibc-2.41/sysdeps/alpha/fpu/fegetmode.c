/* Store current floating-point control modes.  Alpha version.
   Copyright (C) 2016-2025 Free Software Foundation, Inc.
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

#include <fenv_libc.h>

int
fegetmode (femode_t *modep)
{
  unsigned long int fpcr;
  unsigned long int swcr;

  /* As in fegetenv.  */
  swcr = __ieee_get_fp_control ();
  __asm__ __volatile__ ("mf_fpcr %0" : "=f" (fpcr));
  *modep = ((fpcr & FPCR_ROUND_MASK) | (swcr & SWCR_ALL_MASK));

  return 0;
}
