#include <stdio.h>

long poptest();

int main() {
  printf("poptest: 0x%lx\n", poptest());
  return 0;
}

/*
 * 0xxxxx     0xabcd
 *   rsp0      rsp+8
 * 1) rsp <- M[rsp]
 *
 * 2) rsp <- rsp - 8
 *    rsp <- 0xxxxx
 * Если res всегда равен 0xabcd, то popq %rsp читает данные по адрессу rsp и
 * затем сохраняет их в rsp
 * */
long poptest() {
  long res;
  asm volatile (
    "movq %%rsp, %%rdi\n\t"
    "pushq $0xabcd\n\t"
    "popq %%rsp\n\t"
    "movq %%rsp, %[res]\n\t"
    "movq %%rdi, %%rsp"
    : [res] "=r" (res)
    :
    : "rdi", "memory"
  );
  return res;
}
