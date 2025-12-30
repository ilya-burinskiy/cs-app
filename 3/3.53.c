typedef int arg1_t;
typedef long arg2_t;
typedef float arg3_t;
typedef double arg4_t;

/* 
 * funct1:
 *   vcvtsi2ssq %rsi, %xmm2, %xmm2    xmm2 = (float) rsi
 *   vaddss %xmm0, %xmm2, %xmm0       xmm0 = xmm2 + xmm0
 *   vcvtsi2ss %edi, %xmm2, %xmm2     xmm2 = (float) edi
 *   vdivss %xmm0, %xmm2, %xmm0       xmm0 = xmm2 / xmm0
 *   vunpcklps $xmm0, %xmm2, %xmm0
 *   vcvtps2pd %xmm0, %xmm0           xmm0 = (double) xmm0
 *   vsubsd %xmm1, %xmm0, %xmm0       xmm0 = xmm0 - xmm1
 * */
double funct1(arg1_t p, arg2_t q, arg3_t r, arg4_t s) {
  return p/(q+r) - s;
}
