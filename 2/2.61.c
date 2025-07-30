#include <stdio.h>

int any_bit_eq_1(int);
int any_bit_eq_0(int);
int any_bit_in_msb_eq_1(int);
int any_bit_in_msb_eq_0(int);

int main(int argc, char **argv) {
  printf("any bit of 1 equal 1: %d\n", any_bit_eq_1(1));
  printf("any bit of 0 equal 1: %d\n", any_bit_eq_1(0));

  printf("any bit of 1 equal 0: %d\n", any_bit_eq_0(1));
  printf("any bit of 0 equal 0: %d\n", any_bit_eq_0(0));
  printf("any bit of 0xFFFFFFFF equal 0: %d\n", any_bit_eq_0(0xFFFFFFFF));

  printf("any bit in the most significant byte of 0xFFFFFFFF equal 1: %d\n", any_bit_in_msb_eq_1(0xFFFFFFFF));
  printf("any bit in the most significant byte of 0x00FFFFFF equal 1: %d\n", any_bit_in_msb_eq_1(0x00FFFFFF));

  printf("any bit in the most significant byte of 0xFFFFFFFF equal 0: %d\n", any_bit_in_msb_eq_0(0xFFFFFFFF));
  printf("any bit in the most significant byte of 0x00FFFFFF equal 0: %d\n", any_bit_in_msb_eq_0(0x00FFFFFF));
  printf("any bit in the most significant byte of 0x01FFFFFF equal 0: %d\n", any_bit_in_msb_eq_0(0x01FFFFFF));

  return 0;
}

int any_bit_eq_1(int x) {
  return !!x;
}

int any_bit_eq_0(int x) {
  return !!(x ^ (~0));
}

int any_bit_in_msb_eq_1(int x) {
  return any_bit_eq_1(x >> 24);
}

int any_bit_in_msb_eq_0(int x) {
  return any_bit_eq_0(x >> 24);
}
