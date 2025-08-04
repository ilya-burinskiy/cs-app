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

int odd_ones(unsigned x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return x & 0x1;
}
