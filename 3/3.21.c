/*
 * # x in %rdi
 * # y in %rsi
 * test:
 *   leaq 12(%rsi), %rax        # rax <- y + 12
 *   testq %rdi, %rdi
 *   jge .L2                    # goto .L2 if x >= 0
 *   movq %rdi, %rax            # rax <- x
 *   imulq %rsi, %rax           # rax <- x * y
 *   movq %rdi, %rdx            # rdx <- x
 *   orq %rsi, %rdx             # rdx <- x | y
 *   cmpq %rsi, %rdi            # x:y
 *   cmovge %rdx, %rax          # rax <- rdx if x >= y
 *   ret
 * .L2:
 *   mov %rax, %rbx             # save rax in rbx
 *   mov %rdi, %rax             # move x in rax
 *   cqto
 *   idivq %rsi                 # rax <- x / y
 *   cmpq $10, %rsi             # y:10
 *   cmovl %rbx, %rax           # rax <- rbx if y < 10
 *   ret
 * */
long test(long x, long y) {
  long val = y + 12;
  if (x < 0) {
    if (x < y) {
      val = x * y;
    } else {
      val = x | y;
    }
  } else if (y >= 10) {
    val = x / y;
  }
  return val;
}
