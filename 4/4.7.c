#include <stdio.h>

long pushtest();

int main() {
  printf("pushtest: %ld\n", pushtest());
  return 0;
}

/* rax <- rsp
 * rsp <- rsp-8
 * M[rsp] = rsp_x;
 * rdx <- rsp_x
 * rsp <- rsp+8
 *
 * rax - rdx = 0
 * rsp - rsp_x = 0
 * => rsp_x = rsp
 * pushq %rsp semantic is:
 *   tmp <- rsp
 *   rsp <- rsp - 8
 *   M[rsp] <- tmp
 * */
long pushtest() {
  long res;
  asm volatile (
    "movq %%rsp, %[res]\n\t"
    "pushq %%rsp\n\t"
    "popq %%rdx\n\t"
    "subq %%rdx, %[res]\n\t"
    : [res] "=r" (res) /* outputs */
    :                  /* inputs */
    : "rdx", "cc", "memory" /* clobbered registers */
  );
  return res;
}
