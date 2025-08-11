#include <stdio.h>

int leftmost_one(unsigned x);

int main(int argc, char **argv) {
  printf("0x%X -> 0x%X\n", 0xFF00, leftmost_one(0xFF00U));
  printf("0x%X -> 0x%X\n", 0x6600, leftmost_one(0x6600U));
  return 0;
}

/*
 * 1000 0000 // x
 * 1100 0000 // x | (x >> 1)
 * 1111 0000 // x | (x >> 2)
 * 1111 1111 // x | (x >> 4)
 *
 * 1010 1100 // x
 * 1111 1110 // x | (x >> 1)
 * 1111 1111 // x | (x >> 2)
 * 1111 1111 // x | (x >> 4)
 *
 * 0000 1000 // x
 * 0000 1100 // x | (x >> 1)
 * 0000 1111 // x | (x >> 2)
 * 0000 1111 // x | (x >> 4)
 */
int leftmost_one(unsigned x) {
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  x |= (x >> 8);
  x |= (x >> 16);

  return x ^ (x >> 1);
}
