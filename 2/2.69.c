#include <stdio.h>

unsigned rotate_left(unsigned x, int n);

int main(int argc, char **argv) {
  unsigned x = 0x12345678U;
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 0, rotate_left(x, 0));
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 4, rotate_left(x, 4));
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 8, rotate_left(x, 8));
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 12, rotate_left(x, 12));
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 16, rotate_left(x, 16));
  printf("rotate_left(0x%X, %d): 0x%X\n", x, 20, rotate_left(x, 20));
  return 0;
}

/*
 * 0 <= n < w
 *
 * x = 0x12345678, w = 32
 * n=4 ->  0x23456781
 * n=20 -> 0x67812345
 *
 * 0x12345678 << 4:  0x23456780
 * 0x12345678 >> 28: 0x00000001
 * 0x23456781: 0x23456780 | 0x00000001
 *
 * ~(x == 0) + 1
 * 0xFFFFFFFF => x == 0
 * 0x00000000 => x != 0
 * */
unsigned rotate_left(unsigned x, int n) {
  int n_eq_0 = ~(x == 0) + 1;
  int rshift_val = (~n_eq_0 & (32 - n));
  unsigned lshifted = x << n;
  unsigned rshifted = x >> rshift_val;
  return lshifted | rshifted;
}
