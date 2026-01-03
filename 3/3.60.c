/*
 * long loop(long x, int n)
 * x in rdi, n in esi
 * loop:
 *   movl %esi, %ecx      ecx = n
 *   movl $1, %edx        edx = 1
 *   movl $0, %eax        eax = 0
 *   jmp .L2
 * .L3:
 *   movq %rdi, %r8       r8 = x
 *   andq %rdx, %r8       r8 = r8 & rdx
 *   orq %r8, %rax        rax = rax | r8
 *   salq %cl, %rdx       rdx = rdx << n
 * .L2:
 *   testq %rdx, %rdx
 *   jne .L3              if rdx != 0 goto .L3
 *   rep; ret
 * */
long loop(long x, long n) {
  long result = 0;
  long mask;
  for (mask = 1; mask != 0; mask = mask << n) {
    result |= x & mask;
  }
  return result;
}
