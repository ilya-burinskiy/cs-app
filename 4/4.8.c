#include <stdio.h>

long poptest();

int main() {
  printf("poptest: 0x%lx\n", poptest());
  return 0;
}

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
