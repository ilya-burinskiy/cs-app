/*
 * # rdi <- x
 * fun_b:
 *   movl $64, %edx   # edx <- 64 (i)
 *   movl $0, %eax    # eax <- 0 (val)
 * .L10:
 *   movq %rdi, %rcx  # rcx <- x
 *   andl %1, %ecx    # ecx <- x & 1
 *   addq %rax, %rax  # rax <- rax + rax
 *   orq %rcx, %rax   # rax <- rax | rcx
 *   shrq %rdi        # rdi <- rdi >> 1
 *   subq $1, %rdx    # rdx <- rdx - 1
 *   jne .L10         # if rdx != 0 goto .L10
 *   rep; ret
 *
 * B. 64 != 0
 * C. -
 * */
long fun_b(unsigned long x) {
  long val = 0;
  long i;
  for (i = 64; i != 0; i--;) {
    val = (val << 1) | (x & 1); // 2 * val == val << 1
    x = x >> 1;
  }
  return val;
}
