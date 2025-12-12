/*
 * # rdi <- a, rsi <- b
 * loop_while2:
 *   testq %rsi, %rsi
 *   jle .L8          # if b <= 0 goto .L8
 *   movq %rsi, %rax  # rax <- b
 * .L7:
 *   imulq %rdi, %rax # rax <- rax * a
 *   subq %rdi, %rsi  # rsi <- rsi - a
 *   testq %rsi, %rsi
 *   jg  .L7          # if b > 0 goto .L7
 *   rep; ret
 * .L8
 *   movq %rsi, %rax  # rax <- b
 *   ret
 * */
long loop_while2(long a, long b) {
  long result = b;
  while (b > 0) {
    result = result * a;
    b = b - a;
  }
  return result;
}
