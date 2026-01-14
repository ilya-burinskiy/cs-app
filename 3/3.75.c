#include <complex.h>

/*
 * c_imag:
 *   movapd %xmm1, %xmm0
 *   ret
 * */
double c_imag(double complex x) {
  return cimag(x);
}

/*
 * c_real:
 *   rep; ret
 * */
double c_real(double complex x) {
  return creal(x);
}

/*
 * subsd %xmm2, %xmm0
 * subsd %xmm3, %xmm1
 * */
double complex c_sub(double complex x, double complex y) {
  return x - y;
}

/*
 * A. Парами в регистрах. 1 аргумент (xmm0, xmm1), 2 - (xmm2, xmm3) и тд.
 *    В первом элементе Re(z), во втором Im(z).
 * B. Через пару (xmm0, xmm1)
 * */
