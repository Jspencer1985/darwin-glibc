/* Complex sine function.  m68k fpu version
   Copyright (C) 1997-2025 Free Software Foundation, Inc.
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

#include <complex.h>
#include <math.h>
#include "mathimpl.h"

#define s(name) M_SUF (name)
#define m81(func) __m81_u(s(func))

CFLOAT
s(__csin) (CFLOAT x)
{
  CFLOAT retval;
  unsigned long rx_cond = __m81_test (__real__ x);

  if ((rx_cond & (__M81_COND_INF|__M81_COND_NAN)) == 0)
    {
      /* Real part is finite.  */
      FLOAT sin_rx, cos_rx;

      __asm ("fsincos%.x %2,%1:%0" : "=f" (sin_rx), "=f" (cos_rx)
	     : "f" (__real__ x));
      if (rx_cond & __M81_COND_ZERO)
	__real__ retval = __real__ x;
      else
	__real__ retval = sin_rx * m81(__ieee754_cosh) (__imag__ x);
      __imag__ retval = cos_rx * m81(__ieee754_sinh) (__imag__ x);
    }
  else
    {
      unsigned long ix_cond = __m81_test (__imag__ x);

      __real__ retval = __real__ x - __real__ x;
      if (ix_cond & (__M81_COND_ZERO|__M81_COND_INF|__M81_COND_NAN))
	__imag__ retval = __imag__ x;
      else
	__imag__ retval = __real__ retval;
    }

  return retval;
}
declare_mgen_alias (__csin, csin)
