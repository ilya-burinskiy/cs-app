#define OP /
/*
 * # x in %rdi
 * arith:
 *   leaq 15(%rdi), %rax   # rax <- 15 + x 
 *   testq %rdi, %rdi      # x & x
 *   cmovns %rdi, %rax     # rax <- x if x >= 0
 *   sarq $4, %rax         # rax <- rax >> 4
 *   ret
 *
 * A. -
 * B.
 *   if x >= 0
 *     x = x / 16  
 *   else
 *     x = (x + 15) / 16
 *   end
 *
 * */
long arith(long x) {
  return x OP 16;
}
