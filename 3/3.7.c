/*
 * x in %rdi, y in %rsi, z in %rdx
 * scale3:
 *   leaq (%rsi,%rsi,9), %rbx
 *   leaq (%rbx, %rdx), %rbx
 *   leaq (%rbx,%rdi,%rsi), %rbx
 *   ret
 *
 *   10 * y
 *   10 * y + z
 *   10 * y + z + x * y
 * */
short scale3(short x, short y, short z) {
  short t = 10 * y + z + x * y;
  return t;
}
