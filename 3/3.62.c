typedef enum {
  MODE_A,
  MODE_B,
  MODE_C,
  MODE_D,
  MODE_E
} mode_t;

/*
 * p1 in rdi
 * p2 in rsi
 * action in edx
 * switch3:
 * .L8:                 MODE_E
 *   movl $27, %eax
 *   ret
 * .L3:                 MODE_A
 *   movq (%rsi), %rax  rax = *p2
 *   movq (%rdi), %rdx  rdx = *p1
 *   movq %rdx, (%rsi)  *p2 = rdx
 *   ret
 * .L5:                 MODE_B
 *   movq (%rdi), %rax  rax = *p1
 *   addq (%rsi), %rax  rax = rax + *p2
 *   movq %rax, (%rdi)  *p1 = rax
 *   ret
 * .L6:                 MODE_C
 *   movq $59, (%rdi)   *p1 = 59
 *   movq (%rsi), %rax  rax = *p2
 *   ret
 * .L7:                 MODE_D
 *   movq (%rsi), %rax  rax = *p2
 *   movq %rax, (%rdi)  *p1 = *p2
 *   movl $27, %eax     eax = 27
 *   ret
 * .L9:                 default
 *   movl $12, %eax
 *   ret
 * */
long switch3(long *p1, long *p2, mode_t action) {
  long result = 0;
  switch (action) {
  case MODE_A:
    result = *p2;
    *p2 = *p1;
    break;
  case MODE_B:
    result = *p1 + *p2;
    *p1 = result;
    break;
  case MODE_C:
    *p1 = 59;
    result = *p2;
    break;
  case MODE_D:
    *p1 = *p2;
    result = 27;
    break;
  case MODE_E:
    result = 27;
    break;
  default:
    result = 12;
  }
  return result;
}
