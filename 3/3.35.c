/*
 * long rfun(unsigned long x)
 * rdi <- rdi
 * rfun:
 *   pushq %rbx          save rbx
 *   movq %rdi, %rbx     rbx <- rdi
 *   movl $0, %eax       eax <- 0
 *   testq %rdi, %rdi
 *   je .L2              if rdi == 0 goto .L2
 *   shrq $2, %rdi       rdi <- rdi >> 2
 *   call rfun
 *   addq %rbx, %rax     rax <- rax + rbx
 * .L2:
 *   popq %rbx
 *   ret
 * */
long rfun(unsigned long x) {
  if (x == 0) {
    return 0;
  }
  unsigned long nx = x >> 2;
  long rv = rfun(nx);
  return x + rv;
}

/*
 * A. Argument x.
 * */
