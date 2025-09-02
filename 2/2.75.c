#include <assert.h>
#include <limits.h>

unsigned unsigned_high_prod(unsigned, unsigned);
int signed_high_prod(int, int);

int main(int argc, char **argv) {
  unsigned x, y, lower_bits, high_bits;
  y = x = UINT_MAX;
  lower_bits = x * y;
  high_bits = unsigned_high_prod(x, y);
  assert(lower_bits == );
  assert(high_bits == 1);
  return 0;
}

/*
 *          1111
 *          1111
 *          ----
 *          1111
 *         1111
 *        1111
 *       1111
 *       -------
 *    1101010101
 * (0) 1
 * (0) 1 + 1 = 10
 * (10) 1 + 1 + 1 = 11 + 10 = 101
 * (100) 1 + 1 + 1 + 1 = 100 + 100 = 1000
 * (1000) 1 + 1 + 1 = 11 + 1000 = 1011
 * (1010) 1 + 1 = 10 + 1010 = 1100
 * */
unsigned unsigned_high_prod(unsigned x, unsigned y) {
  return 1;
}

int signed_high_prod(int x, int y) {
  return 1;
}
