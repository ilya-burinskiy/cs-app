/*
 * # rdi <- a
 * # rsi <- b
 * # rdx <- c
 * # rcx <- dest
 * switcher:
 *   cmpq $7, %rdi          # a:7
 *   ja .L2                 # goto .L2 if a > 7
 *   jmp *.L4(,%rdi,8)
 * .L7:
 *   xorq $15, %rsi         # b <- b ^ 15
 *   movq %rsi, %rdx        # c <- b
 * .L3:
 *   leaq 112(%rdx), %rdi   # a <- c + 112
 *   jmp .L6
 * .L5:
 *   leaq (%rdx,%rsi), %rdi # a <- b + c
 *   salq $2, %rdi          # a <- a << 2
 *   jmp .L6
 * .L2:
 *   movq %rsi, %rdi        # a <- b
 * .L6:
 *   movq %rdi, (%rcx)      # *dst <- a
 *   ret
 * 
 * .section .rodata
 * .switch_table:
 *   .quad .L3 # x=0
 *   .quad .L2 # x=1 default
 *   .quad .L5 # x=2
 *   .quad .L2 # x=3 default
 *   .quad .L6 # x=4
 *   .quad .L7 # x=5
 *   .quad .L2 # x=6 default
 *   .quad .L5 # x=7
 * */
void switcher2(long a, long b, long c, long *dest) {
  switch (a) {
  case 5: /* .L7 .L3 */
    b = b ^ 15;
    c = b;
  case 0: /* .L3 */
    a = c + 112;
    break;
  /* 1 goes to default */
  case 7: /* .L5 */
  case 2: /* .L5 */
    a = b + c;
    a = a << 2;
  /* 3 goes to default */
  case 4:break; /* .L6 */
  /* 6 goes to default */
  default:
    a = b;
  }
  *dst = a;
}

void switcher1(long a, long b, long c, long *dest) {
  long val;
  switch (a) {
  case 5: /* .L7 .L3 */
    c = b ^ 15;
  case 0: /* .L3 */
    val = c + 112;
    break;
  /* 1 goes to default */
  case 7: /* .L5 */
  case 2: /* .L5 */
    val = (b + c) << 2;
    break;
  /* 3 goes to default */
  case 4: /* .L6 */
    val = a;
    break;
  /* 6 goes to default */
  default:
    val = b;
  }
  *dst = val;
}
