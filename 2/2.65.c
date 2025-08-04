#include <stdio.h>

int odd_ones(unsigned x);

int main(int argc, char **argv) {
  printf("odd_ones(0x%X): %i\n", 0, odd_ones(0)); // 0
  printf("odd_ones(0x%X): %i\n", 1, odd_ones(1)); // 1
  printf("odd_ones(0x%X): %i\n", 2, odd_ones(2)); // 1
  printf("odd_ones(0x%X): %i\n", 3, odd_ones(3)); // 0
  printf("odd_ones(0x%X): %i\n", 4, odd_ones(4)); // 1
  printf("odd_ones(0x%X): %i\n", 5, odd_ones(5)); // 0
  return 0;
}

/*
 * Какие биты складываем, если ((x >> 1) & 0x55) + (x & 0x55)
 * b[7] + b[6], b[5] + b[4], b[3] + b[2], b[1] + b[0]
 * 0 + 1 (b[7] + b[6])
 * 1 + 0 (b[5] + b[4])
 * 1 + 1 (b[3] + b[2])
 * 1 + 0 (b[1] + b[0])
 *
 *       7654 3210
 * x:    0110 1110
 *       0101 0101
 *       -765 4321
 * x>>1: 0011 0111
 *       0101 0101
 * 0100 0100 +
 * 0001 0101
 * ---------
 * 0101 1001
 *
 *       7654 3210
 * x:    0101 1001
 *       0011 0011
 *       --76 5432
 * x>>2: 0001 0110
 *       0011 0011
 * ----
 * 1110
 * */
int odd_ones(unsigned x) {
  x = ((x >> 1) & 0x55555555) + (x & 0x55555555);
  x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
  x = ((x >> 4) & 0x0F0F0F0F) + (x & 0x0F0F0F0F);
  x = ((x >> 8) & 0x00FF00FF) + (x & 0x00FF00FF);
  x = (x >> 16) + (x & 0x0000FFFF);
  return x & 0x1;
}
