/*
 * double fcvt2(int *ip, float *fp, double *dp, long l) {
 * ip in %rdi, fp in %rsi, dp in %rdx, l in %rcx
 * fcvt2:
 *   movl (%rdi), %eax              eax = *ip
 *   vmovss (%rsi), %xmm0           xmm0 = *fp
 *   vcvttsd2si (%rdx), %r8d        r8d = (int) *dp
 *   movl %r8d, (%rdi)              xmm1 = (float) eax
 *   vcvtsi2ss %eax, %xmm1, %xmm1   *fp = xmm1
 *   vmovss %xm1, (%rsi)            xmm1 = (double) l
 *   vcvtsi2sdq %rcx, %xmm1, %xmm1  *dp = xmm1
 *   vmovsd %xmm1, (%rdx)
 *   vunpcklps %xmm0, %xmm0, %xmm0  xmm0 = (double) xmm0
 * */
double fcvt2(int *ip, float *fp, double *dp, long l) {
  int i = *ip; float f = *fp; double d = *dp;
  *ip = (int) d;
  *fp = (float) i;
  *dp = (double) l;
  return (double) f;
}
