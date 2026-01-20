/*
 * phase_4:
 *   sub    $0x18, %rsp                      # alloc 24 bytes
 *   lea    0xc(%rsp), %rcx                  # rcx = &x1
 *   lea    0x8(%rsp), %rdx                  # rdx = &x0
 *   mov    $0x4025cf, %esi
 *   mov    $0x0, %eax                       # eax = 0
 *   call   __isoc99_sscanf@plt              # eax = sscanf(,"%d %d", &x0, &x1)
 *   cmp    $0x2, %eax                       # eax:2
 *   jne    .L0                              # if eax != 2 goto .L0
 *   # eax == 2
 *   cmpl   $0xe, 0x8(%rsp)                  # x0:14
 *   jbe    .L1                              # if x0 <= 14 goto .L1
 * .L0:
 *   # x0 > 14
 *   call   explode_bomb
 * .L1:
 *   mov    $0xe,%edx                        # edx = 14
 *   mov    $0x0,%esi                        # esi = 0
 *   mov    0x8(%rsp),%edi                   # edi = x0
 *   call   func4
 *   test   %eax,%eax
 *   jne    .L2                              # if eax != 0 goto .L2
 *   cmpl   $0x0,0xc(%rsp)                   # x1:0
 *   je     .L3                              # if x1 == 0 goto .L3
 * .L2:
 *   call   explode_bomb
 * .L3:
 *   add    $0x18,%rsp
 *   ret
 *
 * # x in edi
 * # p0 in esi
 * # p1 id edx
 * # ecx > x => 2*func4(x, p0, ((long) ecx) - 1)
 * # ecx = x => 0
 * # ecx < x => 3*func4(x)
 * func4:
 *   sub    $0x8, %rsp
 *   mov    %edx, %eax             # eax = p1
 *   sub    %esi, %eax             # eax = p1 - p0
 *   mov    %eax, %ecx             # ecx = p1 - p0
 *   shr    $0x1f, %ecx            # ecx = ((unsigned) (p1 - p0)) >> 31
 *   add    %ecx, %eax             # eax = p1 - p0 + (((unsigned) (p1 - p0)) >> 31)
 *   sar    $1, %eax               # eax = eax / 2
 *   lea    (%rax,%rsi,1), %ecx    # ecx = ((long) eax) + ((long) p0)
 *   cmp    %edi, %ecx             # ecx:x
 *   jle    .L0                    # if ecx <= x goto .L0
 *   # ecx > x
 *   lea    -0x1(%rcx), %edx       # p1 = ((long) ecx) - 1
 *   call   func4                  # eax = func4(x, p0, p1)
 *   add    %eax, %eax             # eax = 2*eax
 *   jmp    .L1
 * .L0:
 *   # ecx <= x
 *   mov    $0x0, %eax             # eax = 0
 *   cmp    %edi, %ecx             # ecx:x
 *   jge    .L1                    # if ecx >= x goto .L1
 *   # ecx < x
 *   lea    0x1(%rcx), %esi        # p0 = ((long) ecx) + 1
 *   call   func4                  # eax = func4(x, p0, p1)
 *   lea    0x1(%rax,%rax,1), %eax # eax = 3*eax
 * .L1:
 *   add    $0x8,%rsp
 *   ret
 */
int func4(int x, int p0, int p1) {
  int eax, ecx;
  eax = p1 - p0;
  ecx = ((unsigned) eax) >> 31;
  eax = (eax + ecx) >> 1;
  ecx = ((long) eax) + ((long) p0);
  if (ecx > x) {
      return 2 * func4(x, p0, ecx - 1);
  } else if (ecx < x) {
      return 3 * func4(x, ecx + 1, p1);
  } else {
      return 0;
  }
}
