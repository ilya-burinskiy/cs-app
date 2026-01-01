/*
 * double funct2(int *ap, double b, long c, float *dp)
 * ap in %rdi, b in %xmm0, c in %rsi, dp in %rdx
 * funct3:
 *   vmovss (%rdx), %xmm1              xmm1 = *dp
 *   vcvtsi2sd (%rdi), %xmm2, %xmm2    xmm2 = (double) *ap
 *   vucomisd %xmm2, %xmm0             *dp:*ap
 *   jbe .L8                           if *dp <= *ap goto .L8
 *   vcvtsi2ssq %rsi, %xmm0, %xmm0     xmm0 = (float) c
 *   vmulss %xmm1, %xmm0, %xmm1        xmm1 = c * *dp
 *   vunpcklps %xmm1, %xmm1, %xmm1
 *   vcvtps2pd %xmm1, %xmm0            xmm0 = (double) (*dp * c)
 *   ret
 * .L8:
 *   vaddss %xmm1, %xmm1, %xmm1        xmm1 = 2 * *dp
 *   vcvtsi2ssq %rsi, %xmm0, %xmm0     xmm0 = (float) c
 *   vadds %xmm1, %xmm0, %xmm0         xmm0 = c + 2* *dp
 *   vunpcklps %xmm0, %xmm0, %xmm0
 *   vcvtps2pd %xmm0, %xmm0            xmm0 = (double) xmm0
 *   ret
 * */

double funct2(int *ap, double b, long c, float *dp) {
  float d = *dp;
  double a = (double) *ap;
  double res;

  if (d <= a) {
    res = 2*d + c;
  } else {
    res = d*c;
  }
  return res;
}
