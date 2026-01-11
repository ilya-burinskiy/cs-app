#include <alloca.h>

/*
 * n in rdi, idx in rsi, q in rdx
 * aframe:
 *   pushq %rbp
 *   movq %rsp, %rbp
 *   subq $16, %rsp               alloc space for i (rsp = s1)
 *   leaq 30(,%rdi,8), %rax       rax = 8*n + 30
 *   andq $-16, %rax              rax = rax - (rax mod 16)
 *   subq %rax, %rsp              alloc space for p (rsp = s2)
 *   leaq 15(%rsp), %r8           r8 = rsp + 15
 *   andq $-16, %r8               r8 = r8 - (r8 mod 16); set r8 to &p[0]
 *
 *   |*******|**********|************|*******|
 *           s1     &p[n-1]        &p[0]     s2
 *
 * e1 = s1 - &p[n-1]
 * e2 = &p[0] - s2
 *
 * A. (+)
 * N = 8*n + 30
 * Alloc M = N - (N mod 16) bytes. 16\M
 *
 * B. (+)
 * s2 + 15 - ((s2 + 15) mod 16)
 * s2 = 16*m + r, 0 <= r < 16, 15 <= r+15 < 31
 * = 16*m + r + 15 - ((16*m + r + 15) mod 16)
 * = 16*m + r + 15 - ((r + 15) mod 16)
 * if r = 0: 16*m
 * if r != 0:
 *   16*m + r + 15 - (r - 1)
 *   = 16*m + r + 15 - r + 1
 *   = 16*(m+1)
 * r никогда не равен нулю, поэтому p = 16*(m + 1)
 *
 * C. (-)
 * 16\s1 - предположение
 * a mod b = a - floor(a/b)*b
 *
 * -17 mod 16 = -17 - 16*floor(-17/16)
 *            = -17 + 16*2 = 32 - 17 = 15
 * n = 1
 * rax = 38; rax = 38 - 6 = 32; rsp = s1 - 32
 * r8 = rsp + 15 = s1 - 32 + 15 = s1 - 17;
 * r8 = s1 - 17 - (s1 - 17 mod 16)
 *    = s1 - 17 - 15 = s1 - 2*16
 *
 * D. (-)
 * p and s2 are aligned by 16
 * */
long aframe(long n, long idx, long *q) {
  long i;
  long **p = alloca(n * sizeof(long *));
  p[0] = &i;
  for (i = 1; i < n; i++) {
    p[i] = q;
  }
  return *p[idx];
}
