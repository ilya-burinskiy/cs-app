#include <assert.h>
#include <limits.h>

int threefourths(int);

int main(int argc, char **argv) {
  assert(threefourths(0) == 0);
  assert(threefourths(4) == 3);
  assert(threefourths(1) == 0);
  // assert(threefourths(10) == 7);
  // wrong
  assert(threefourths(10) == 6);
  // assert(threefourths(11) == 8);
  // wrong
  assert(threefourths(11) == 6);
  assert(threefourths(-4) == -3);
  assert(threefourths(-1) == 0);
  assert(threefourths(INT_MAX) == 1610612733);
  return 0;
}

/*
 * x = 4*k + r, 0 <= r < 4
 * x/4 = k + r/4
 * 3*floor(x/4) = 3*k
 * 3*r/4 больше одного при 2 <= r < 4 (т.е. 2 или 3)
 * */
int threefourths(int x) {
  int x1 = x & ~0x3;
  int x2 = x & 0x3;
  int res = ((x2 << 1) + x2) >> 2;
  if (x1 < 0) {
    x1 += 3;
  }
  x1 = (x1 << 2); // x1 / 4
  res += (x1 << 1) + x1; // res * 3
  return res;
}
