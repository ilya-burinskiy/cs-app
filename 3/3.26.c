/*
 * # rdi <- x
 * test_one:
 *   movl $1, %eax # rax <- 1 (val)
 *   jmp .L5
 * .L6:
 *   xorq %rdi, %rax  # rax <- rax ^ x
 *   shrq %rdi        # rdi <- rdi >> 1 (x / 2)
 * .L5:
 *   testq %rdi, %rdi
 *   jne .L6          # if x != 0 goto .L6
 *   andl $0, %eax    # eax <- 0
 *   ret
 * */
long test_one(unsigned long x) {
  long val = 1;
  while (x != 0) {
    val = val ^ x;
    x = x / 2;
  }
  return 0;
}
