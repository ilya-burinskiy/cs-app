#include <assert.h>
#include <limits.h>
#include <stdio.h>

int threefourths(int);
int threefourths2(int);

int main(int argc, char **argv) {
  assert(threefourths(0) == 0);
  assert(threefourths(4) == 3);
  assert(threefourths(1) == 0);
  assert(threefourths(-4) == -3);
  assert(threefourths(-1) == 0);
  assert(threefourths(INT_MAX) == 1610612735);
  return 0;
}

int threefourths(int x) {
  int f = x & ~0x3;
  int r = x & 0x3;
  int xlt0 = x >> 31; // 0xFFFFFFFF if x < 0, 0x0 otherwize
  int fdiv4 = f >> 2;
  int fdiv4mult3 = (fdiv4 << 1) + fdiv4;
  int rmult3 = (r << 1) + r;
  rmult3 += (xlt0 & 0x3);
  int rmult3div4 = rmult3 >> 2;
  return fdiv4mult3 + rmult3div4;
}

int threefourths2(int x) {
  int is_neg = x & INT_MIN;
  int f = x & ~0x3;
  int l = x & 0x3;

  int fd4 = f >> 2;
  int fd4m3 = (fd4 << 1) + fd4;

  int lm3 = (l << 1) + l;
  int bias = (1 << 2) - 1;
  (is_neg && (lm3 += bias));
  int lm3d4 = lm3 >> 2;

  return fd4m3 + lm3d4;
}
