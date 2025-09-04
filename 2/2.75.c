#include <assert.h>
#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

unsigned unsigned_high_prod(unsigned, unsigned);
unsigned unsigned_high_prod2(unsigned, unsigned);
int signed_high_prod(int, int);

int main(int argc, char **argv) {
  unsigned x1, y1, z1, z2;
  x1 = 0x7FFFFFFFU;
  y1 = 0x12345678U;
  z1 = unsigned_high_prod(x1, y1);
  z2 = unsigned_high_prod2(x1, y1);
  assert(z1 == z2);
  return 0;
}

/*
 * T2U x | x < 0  = x + 2^w
 *       | x >= 0 = x
 *
 * x * y                                   <- lower w bits
 * u = x_w-1*y + y_w-1*x + x_w-1*y_w-1*2^w
 *     -----------------   ---------------
 *        signed high       cast to U part
 *           prod
 * */
unsigned unsigned_high_prod(unsigned x, unsigned y) {
  int high32bits = signed_high_prod((int) x, (int) y);
  int xmsb = x >> 31;
  int ymsb = y >> 31;
  return high32bits + xmsb * y + ymsb * x;
}

unsigned unsigned_high_prod2(unsigned x, unsigned y) {
  uint64_t res = (uint64_t) x * y;
  return res >> 32;
}

int signed_high_prod(int x, int y) {
  int64_t res = (int64_t) x * y;
  return res >> 32;
}
