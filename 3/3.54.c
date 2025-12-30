/*
 * funct2:
 *   vcvtsi2ss %edi, %xmm2, %xmm2    xmm2 = (float) x
 *   vmulss %xmm1, %xmm2, %xmm1      xmm1 = x * y
 *   vunpcklps %xmm1, %xmm1, %xmm1
 *   vcvtps2pd %xmm1, %xmm2          xmm2 = (double) (x * y)
 *   vcvtsi2sdq %rsi, %xmm1, %xmm1   xmm1 = (double) z
 *   vdivsd %xmm1, %xmm0, %xmm0      xmm0 = w / z
 *   vsubsd %xmm0, %xmm2, %xmm0      xmm0 = x * y - w / z
 *   ret
 * */
double funct2(double w, int x, float y, long z) {
  return x * y - w / z;
}
