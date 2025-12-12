/*
 * # Orig
 * # %rdi <- a, %rsi <- b
 * loop_while:
 *   movl $0, %eax
 *   jmp .L2
 * .L3:
 *   leaq (,%rsi,%rdi), %rdx # rdx <- b * a
 *   addq %rdx, %rax         # rax <- rax + b * a
 *   subq $1, %rdi           # rdi <- rdi - 1
 * .L2:
 *   cmpq %rsi, %rdi # a:b
 *   jg .L3          # if a > b goto L3
 *   rep; ret
 * */
long loop_while(long a, long b) {
  long result = 0;
  while (a > b) {
    result = result + b * a;
    a = a - 1;
  }
  return result;
}
