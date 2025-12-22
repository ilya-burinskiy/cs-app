struct ELE {
  long v;
  struct ELE *p;
};

/*
 * rdi <- ptr
 * fun:
 *   movl $0, %eax            eax <- 0
 *   jmp .L2
 * .L3:
 *   addq (%rdi), %rax        rax <- rax + ptr.v
 *   movq 8(%rdi), %rdi       rdi <- ptr.p
 * .L2:
 *   testq %rdi, %rdi
 *   jne .L3                  if rdi != NULL goto .L3
 *   rep; ret
 * */
long fun(struct ELE *ptr) {
  long res = 0;
  while (ptr != NULL) {
    res += ptr.v;
    ptr = ptr.p;
  }
  return res;
}
