/* Single-precision AdvSIMD expm1

   Copyright (C) 2023-2025 Free Software Foundation, Inc.
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

#include "v_math.h"
#include "v_expm1f_inline.h"

static const struct data
{
  struct v_expm1f_data d;
#if WANT_SIMD_EXCEPT
  uint32x4_t thresh;
#else
  float32x4_t oflow_bound;
#endif
} data = {
  .d = V_EXPM1F_DATA,
#if !WANT_SIMD_EXCEPT
  /* Value above which expm1f(x) should overflow. Absolute value of the
     underflow bound is greater than this, so it catches both cases - there is
     a small window where fallbacks are triggered unnecessarily.  */
  .oflow_bound = V4 (0x1.5ebc4p+6),
#else
  /* asuint(oflow_bound) - asuint(0x1p-23), shifted left by 1 for absolute
     compare.  */
  .thresh = V4 (0x1d5ebc40),
#endif
};

/* asuint(0x1p-23), shifted by 1 for abs compare.  */
#define TinyBound v_u32 (0x34000000 << 1)

static float32x4_t VPCS_ATTR NOINLINE
special_case (float32x4_t x, uint32x4_t special, const struct data *d)
{
  return v_call_f32 (
      expm1f, x, expm1f_inline (v_zerofy_f32 (x, special), &d->d), special);
}

/* Single-precision vector exp(x) - 1 function.
   The maximum error is 1.62 ULP:
   _ZGVnN4v_expm1f(0x1.85f83p-2) got 0x1.da9f4p-2
				want 0x1.da9f44p-2.  */
float32x4_t VPCS_ATTR NOINLINE V_NAME_F1 (expm1) (float32x4_t x)
{
  const struct data *d = ptr_barrier (&data);

#if WANT_SIMD_EXCEPT
  uint32x4_t ix = vreinterpretq_u32_f32 (x);
  /* If fp exceptions are to be triggered correctly, fall back to scalar for
     |x| < 2^-23, |x| > oflow_bound, Inf & NaN. Add ix to itself for
     shift-left by 1, and compare with thresh which was left-shifted offline -
     this is effectively an absolute compare.  */
  uint32x4_t special
      = vcgeq_u32 (vsubq_u32 (vaddq_u32 (ix, ix), TinyBound), d->thresh);
#else
  /* Handles very large values (+ve and -ve), +/-NaN, +/-Inf.  */
  uint32x4_t special = vcagtq_f32 (x, d->oflow_bound);
#endif

  if (__glibc_unlikely (v_any_u32 (special)))
    return special_case (x, special, d);

  /* expm1(x) ~= p * t + (t - 1).  */
  return expm1f_inline (x, &d->d);
}
libmvec_hidden_def (V_NAME_F1 (expm1))
HALF_WIDTH_ALIAS_F1 (expm1)
