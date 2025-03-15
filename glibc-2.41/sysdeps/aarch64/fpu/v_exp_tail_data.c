/* Lookup table for high-precision exp(x, tail) function

   Copyright (C) 2024-2025 Free Software Foundation, Inc.
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

#include "vecmath_config.h"

/* 2^(j/N), j=0..N, N=2^8=256.  */
const uint64_t __v_exp_tail_data[] = {
  0x3ff0000000000000, 0x3feffb1afa5abcbf, 0x3feff63da9fb3335,
  0x3feff168143b0281, 0x3fefec9a3e778061, 0x3fefe7d42e11bbcc,
  0x3fefe315e86e7f85, 0x3fefde5f72f654b1, 0x3fefd9b0d3158574,
  0x3fefd50a0e3c1f89, 0x3fefd06b29ddf6de, 0x3fefcbd42b72a836,
  0x3fefc74518759bc8, 0x3fefc2bdf66607e0, 0x3fefbe3ecac6f383,
  0x3fefb9c79b1f3919, 0x3fefb5586cf9890f, 0x3fefb0f145e46c85,
  0x3fefac922b7247f7, 0x3fefa83b23395dec, 0x3fefa3ec32d3d1a2,
  0x3fef9fa55fdfa9c5, 0x3fef9b66affed31b, 0x3fef973028d7233e,
  0x3fef9301d0125b51, 0x3fef8edbab5e2ab6, 0x3fef8abdc06c31cc,
  0x3fef86a814f204ab, 0x3fef829aaea92de0, 0x3fef7e95934f312e,
  0x3fef7a98c8a58e51, 0x3fef76a45471c3c2, 0x3fef72b83c7d517b,
  0x3fef6ed48695bbc0, 0x3fef6af9388c8dea, 0x3fef672658375d2f,
  0x3fef635beb6fcb75, 0x3fef5f99f8138a1c, 0x3fef5be084045cd4,
  0x3fef582f95281c6b, 0x3fef54873168b9aa, 0x3fef50e75eb44027,
  0x3fef4d5022fcd91d, 0x3fef49c18438ce4d, 0x3fef463b88628cd6,
  0x3fef42be3578a819, 0x3fef3f49917ddc96, 0x3fef3bdda27912d1,
  0x3fef387a6e756238, 0x3fef351ffb82140a, 0x3fef31ce4fb2a63f,
  0x3fef2e85711ece75, 0x3fef2b4565e27cdd, 0x3fef280e341ddf29,
  0x3fef24dfe1f56381, 0x3fef21ba7591bb70, 0x3fef1e9df51fdee1,
  0x3fef1b8a66d10f13, 0x3fef187fd0dad990, 0x3fef157e39771b2f,
  0x3fef1285a6e4030b, 0x3fef0f961f641589, 0x3fef0cafa93e2f56,
  0x3fef09d24abd886b, 0x3fef06fe0a31b715, 0x3fef0432edeeb2fd,
  0x3fef0170fc4cd831, 0x3feefeb83ba8ea32, 0x3feefc08b26416ff,
  0x3feef96266e3fa2d, 0x3feef6c55f929ff1, 0x3feef431a2de883b,
  0x3feef1a7373aa9cb, 0x3feeef26231e754a, 0x3feeecae6d05d866,
  0x3feeea401b7140ef, 0x3feee7db34e59ff7, 0x3feee57fbfec6cf4,
  0x3feee32dc313a8e5, 0x3feee0e544ede173, 0x3feedea64c123422,
  0x3feedc70df1c5175, 0x3feeda4504ac801c, 0x3feed822c367a024,
  0x3feed60a21f72e2a, 0x3feed3fb2709468a, 0x3feed1f5d950a897,
  0x3feecffa3f84b9d4, 0x3feece086061892d, 0x3feecc2042a7d232,
  0x3feeca41ed1d0057, 0x3feec86d668b3237, 0x3feec6a2b5c13cd0,
  0x3feec4e1e192aed2, 0x3feec32af0d7d3de, 0x3feec17dea6db7d7,
  0x3feebfdad5362a27, 0x3feebe41b817c114, 0x3feebcb299fddd0d,
  0x3feebb2d81d8abff, 0x3feeb9b2769d2ca7, 0x3feeb8417f4531ee,
  0x3feeb6daa2cf6642, 0x3feeb57de83f4eef, 0x3feeb42b569d4f82,
  0x3feeb2e2f4f6ad27, 0x3feeb1a4ca5d920f, 0x3feeb070dde910d2,
  0x3feeaf4736b527da, 0x3feeae27dbe2c4cf, 0x3feead12d497c7fd,
  0x3feeac0827ff07cc, 0x3feeab07dd485429, 0x3feeaa11fba87a03,
  0x3feea9268a5946b7, 0x3feea84590998b93, 0x3feea76f15ad2148,
  0x3feea6a320dceb71, 0x3feea5e1b976dc09, 0x3feea52ae6cdf6f4,
  0x3feea47eb03a5585, 0x3feea3dd1d1929fd, 0x3feea34634ccc320,
  0x3feea2b9febc8fb7, 0x3feea23882552225, 0x3feea1c1c70833f6,
  0x3feea155d44ca973, 0x3feea0f4b19e9538, 0x3feea09e667f3bcd,
  0x3feea052fa75173e, 0x3feea012750bdabf, 0x3fee9fdcddd47645,
  0x3fee9fb23c651a2f, 0x3fee9f9298593ae5, 0x3fee9f7df9519484,
  0x3fee9f7466f42e87, 0x3fee9f75e8ec5f74, 0x3fee9f8286ead08a,
  0x3fee9f9a48a58174, 0x3fee9fbd35d7cbfd, 0x3fee9feb564267c9,
  0x3feea024b1ab6e09, 0x3feea0694fde5d3f, 0x3feea0b938ac1cf6,
  0x3feea11473eb0187, 0x3feea17b0976cfdb, 0x3feea1ed0130c132,
  0x3feea26a62ff86f0, 0x3feea2f336cf4e62, 0x3feea3878491c491,
  0x3feea427543e1a12, 0x3feea4d2add106d9, 0x3feea589994cce13,
  0x3feea64c1eb941f7, 0x3feea71a4623c7ad, 0x3feea7f4179f5b21,
  0x3feea8d99b4492ed, 0x3feea9cad931a436, 0x3feeaac7d98a6699,
  0x3feeabd0a478580f, 0x3feeace5422aa0db, 0x3feeae05bad61778,
  0x3feeaf3216b5448c, 0x3feeb06a5e0866d9, 0x3feeb1ae99157736,
  0x3feeb2fed0282c8a, 0x3feeb45b0b91ffc6, 0x3feeb5c353aa2fe2,
  0x3feeb737b0cdc5e5, 0x3feeb8b82b5f98e5, 0x3feeba44cbc8520f,
  0x3feebbdd9a7670b3, 0x3feebd829fde4e50, 0x3feebf33e47a22a2,
  0x3feec0f170ca07ba, 0x3feec2bb4d53fe0d, 0x3feec49182a3f090,
  0x3feec674194bb8d5, 0x3feec86319e32323, 0x3feeca5e8d07f29e,
  0x3feecc667b5de565, 0x3feece7aed8eb8bb, 0x3feed09bec4a2d33,
  0x3feed2c980460ad8, 0x3feed503b23e255d, 0x3feed74a8af46052,
  0x3feed99e1330b358, 0x3feedbfe53c12e59, 0x3feede6b5579fdbf,
  0x3feee0e521356eba, 0x3feee36bbfd3f37a, 0x3feee5ff3a3c2774,
  0x3feee89f995ad3ad, 0x3feeeb4ce622f2ff, 0x3feeee07298db666,
  0x3feef0ce6c9a8952, 0x3feef3a2b84f15fb, 0x3feef68415b749b1,
  0x3feef9728de5593a, 0x3feefc6e29f1c52a, 0x3feeff76f2fb5e47,
  0x3fef028cf22749e4, 0x3fef05b030a1064a, 0x3fef08e0b79a6f1f,
  0x3fef0c1e904bc1d2, 0x3fef0f69c3f3a207, 0x3fef12c25bd71e09,
  0x3fef16286141b33d, 0x3fef199bdd85529c, 0x3fef1d1cd9fa652c,
  0x3fef20ab5fffd07a, 0x3fef244778fafb22, 0x3fef27f12e57d14b,
  0x3fef2ba88988c933, 0x3fef2f6d9406e7b5, 0x3fef33405751c4db,
  0x3fef3720dcef9069, 0x3fef3b0f2e6d1675, 0x3fef3f0b555dc3fa,
  0x3fef43155b5bab74, 0x3fef472d4a07897c, 0x3fef4b532b08c968,
  0x3fef4f87080d89f2, 0x3fef53c8eacaa1d6, 0x3fef5818dcfba487,
  0x3fef5c76e862e6d3, 0x3fef60e316c98398, 0x3fef655d71ff6075,
  0x3fef69e603db3285, 0x3fef6e7cd63a8315, 0x3fef7321f301b460,
  0x3fef77d5641c0658, 0x3fef7c97337b9b5f, 0x3fef81676b197d17,
  0x3fef864614f5a129, 0x3fef8b333b16ee12, 0x3fef902ee78b3ff6,
  0x3fef953924676d76, 0x3fef9a51fbc74c83, 0x3fef9f7977cdb740,
  0x3fefa4afa2a490da, 0x3fefa9f4867cca6e, 0x3fefaf482d8e67f1,
  0x3fefb4aaa2188510, 0x3fefba1bee615a27, 0x3fefbf9c1cb6412a,
  0x3fefc52b376bba97, 0x3fefcac948dd7274, 0x3fefd0765b6e4540,
  0x3fefd632798844f8, 0x3fefdbfdad9cbe14, 0x3fefe1d802243c89,
  0x3fefe7c1819e90d8, 0x3fefedba3692d514, 0x3feff3c22b8f71f1,
  0x3feff9d96b2a23d9,
};
