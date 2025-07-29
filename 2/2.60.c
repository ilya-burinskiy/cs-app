#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);

int main(int argc, char **argv) {
  printf("replace_byte(0x%X, %d, 0x%X) = 0x%X\n", 0x12345678U, 2, 0xABU, replace_byte(0x12345678U, 2, 0xABU));
  printf("replace_byte(0x%X, %d, 0x%X) = 0x%X\n", 0x12345678U, 0, 0xABU, replace_byte(0x12345678U, 0, 0xABU));
  return 0;
}

/*
 * 0 0xFFFFFF00 = 0xFFFFFF00 | 0x00000000 = (~0 << 8)  | ~(~0 << 0)
 * 1 0xFFFF00FF = 0xFFFF0000 | 0x000000FF = (~0 << 16) | ~(~0 << 8)
 * 2 0xFF00FFFF = 0xFF000000 | 0x0000FFFF = (~0 << 24) | ~(~0 << 16)
 * 3 0x00FFFFFF = 0x00000000 | 0x00FFFFFF = 0          | ~(~0 << 24)
 * */
unsigned replace_byte(unsigned x, int i, unsigned char b) {
  int mask = (i == 3 ? 0 : (~0 << (8 * (i + 1)))) | ~(~0 << i * 8);
  int shift_val = i * 8;
  int ub = ((unsigned int) b) << shift_val;
  int res = (x & mask) | ub;
  return res;
}
