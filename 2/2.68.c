#include <stdio.h>

int lower_one_mask(int n);

int main(int argc, char **argv) {
  for (int i = 1; i <= sizeof(int) * 8; i++) {
    printf("lower_one_mask(%d): 0x%X\n", i, lower_one_mask(i));
  }
  return 0;
}

/*
 * n = 6 --> 0x3F
 * n = 17 --> 0x1FFFF
 * n = 32 --> 0xFFFFFFFF
 * 1 <= n <= sizeof(int) * 8
 *
 * sizeof int = 8, n = 6
 * a = 0001 0000
 * -a = 1110 1111 + 1 = 1111 0000
 * -a ^ a = 0001 0000 ^ 1111 000 = 1110 0000
 * ~(-a ^ a) = 0001 1111
 * */
int lower_one_mask(int n) {
  int a = (1 << (n - 1));
  return ~(-a ^ a);
}
