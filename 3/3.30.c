/*
 * # rdi <- x
 * switch2:
 *   addq $1, %rdi # x <- x + 1
 *   cmpq $8, %rdi # x+1:8
 *   ja .L2        # if x+1>8 goto .L2
 *   jmp *.L4(,%rdi,8)
 *
 * .L4
 *   .quad .L9 0 x=-1
 *   .quad .L5 1 x=0 
 *   .quad .L6 2 x=1
 *   .quad .L7 3 x=2
 *   .quad .L2 4 x=3
 *   .quad .L7 5 x=4
 *   .quad .L8 6 x=5
 *   .quad .L2 7 x=6
 *   .quad .L5 8 x=7
 *
 * x + 1 > 8, x > 7, goto default
 * */
void switch2(long x, long *dest) {
  long val = 0;
  switch (x) {
  case -1: /* .L9 */
    break;
  case 7:
  case 0: /* .L5 */
    break;
  case 1: /* .L6 */
    break;
  case 4:
  case 2: /* .L7 */
    break;
  case 5: /* .L8 */
    break;
  default: /* .L2 */
    break;
  }
  *dest = val;
}
