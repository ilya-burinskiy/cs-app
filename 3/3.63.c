/*
 * long switch_prob(long x, long n)
 * x in rdi, n in rsi
 * 1 0000000000400590 <switch_prob>:
 * 2   400590: 48 83 ee 3c          sub $0x3c,%rsi                rsi = rsi - 60
 * 3   400594: 48 83 fe 05          cmp $0x5,%rsi                 rsi:0x5
 * 4   400598: 77 29                ja 4005c3 <switch_prob+0x33>  if rsi>5 goto 4005c3
 * 5   40059a: ff 24 f5 f8 06 40 00 jmpq *0x4006f8(,%rsi,8)
 * 6   4005a1: 48 8d 04 fd 00 00 00 lea 0x0(,%rdi,8),%rax         rax = x*8
 * 7   4005a8: 00
 * 8   4005a9: c3                   retq
 * 9   4005aa: 48 89 f8             mov %rdi,%rax                 rax = x
 * 10  4005ad: 48 c1 f8 03          sar $0x3,%rax                 rax = x >> 3
 * 11  4005b1: c3                   retq
 * 12  4005b2: 48 89 f8             mov %rdi,%rax                 rax = x
 * 13  4005b5: 48 c1 e0 04          shl $0x4,%rax                 rax = rax << 4
 * 14  4005b9: 48 29 f8             sub %rdi,%rax                 rax = rax - x
 * 15  4005bc: 48 89 c7             mov %rax,%rdi                 rdi = rax
 * 16  4005bf: 48 0f af ff          imul %rdi,%rdi                rdi = rdi * rdi
 * 17  4005c3: 48 8d 47 4b          lea 0x4b(%rdi),%rax           rax = x + 0x4b
 * 18  4005c7: c3                   retq
 *
 * 0x4006f8 + 0x8 = 0x400700
 * 0x400708 + 0x8 = 0x400710
 * 0x400718 + 0x8 = 0x400720
 * Jump table:
 * 0x4006f8: 0x4005a1  0
 * 0x400700: 0x4005c3  1
 * 0x400708: 0x4005a1  2
 * 0x400710: 0x4005aa  3
 * 0x400718: 0x4005b2  4
 * 0x400720: 0x4005bf  5
 * */
long switch_prob(long x, long n) {
  long result = x;
  switch (n) {
  case 62: /* 2 */
  case 60: /* 0 */
    result *= 8;
    break;
  case 63: /* 3 */
    result /= 8;
    break;
  case 64: /* 4 */
    result *= 15;
  case 65: /* 5 */
    result *= result;
  default: /* 1 */
    result += 75;
  }
  return result;
}
