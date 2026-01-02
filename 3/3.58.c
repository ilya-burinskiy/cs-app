/*
 * decode2(long x, long y, long z)
 * x in rdi, y in rsi, z in rdx
 * decode2:
 *   subq %rdx, %rsi    rsi = y - z
 *   imulq %rsi, %rdi   rdi = x * (y - z)
 *   movq %rsi, %rax    rax = y - z
 *   salq $63, %rax     rax = rax << 63
 *   sarq $63, %rax     rax = rax >> 63
 *   xorq %rdi, %rax    rax = rax ^ rdi
 *   ret
 * */
long decode2(long x, long y, long z) {
  long res;
  y = y - z;
  x = x * y;
  res = y << 63;
  res = res >> 63;
  res = res ^ x;
  return res;
}
