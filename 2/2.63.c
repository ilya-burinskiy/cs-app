#include <stdio.h>
#include <assert.h>
#include <limits.h>

unsigned srl(unsigned x, int k);
int sra(int x, int k);

int main(int argc, char **argv) {
  // printf("x = 0x00000080; x >> 0 = 0x%X\n", srl(0x00000080U, 0));
  // printf("x = 0x00000080; x >> 1 = 0x%X\n", srl(0x00000080U, 1));
  // printf("x = 0x00000080; x >> 4 = 0x%X\n", srl(0x80000080U, 4));
  // printf("###########################\n");
  // printf("x = 0x7FFFFFFF; x >> 0 = 0x%X\n", sra(0x7FFFFFFF, 0));
  // printf("x = 0x00000080; x >> 1 = 0x%X\n", sra(0x00000080, 1));
  // printf("x = 0x80000080; x >> 4 = 0x%X\n", sra(0x80000080, 4));
  // printf("x = 0x80000000; x >> 24 = 0x%X\n", sra(0x80000000, 24));
  // printf("x = 0x70000000; x >> 24 = 0x%X\n", sra(0x70000000, 24));
  unsigned int shifted, expected;
  for (unsigned x = 0; x < UINT_MAX; ++x) {
    for (int k = 0; k < (sizeof(int) << 3) - 1; ++k) {
      shifted = srl(x, k);
      expected = x >> k;
      if (shifted != expected) {
        printf("x: 0x%X; k: %d; srl: 0x%X; expected: 0x%X\n", x, k, shifted, expected);
        return 1;
      }
    }
    // puts("");
  }
  // for (int k = 0; k < (sizeof(int) << 3) - 1; ++k) {
  //   assert(srl(UINT_MAX, k) == (UINT_MAX >> k));
  // }
  return 0;
}

unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
  int int_bit_size = sizeof(int) << 3;
  int k_eq_0 = ~!k + 1;
  int shift_val = (k_eq_0 & (int_bit_size - 1)) | (~k_eq_0 & (int_bit_size - k));
  unsigned res = xsra & ~(~0 << shift_val);
  return res;
}

int sra(int x, int k) {
  int xsrl = (unsigned) x >> k;
  int int_bit_size = sizeof(int) << 3;
  int sign = x & (1 << (int_bit_size - 1));
  int x_gte_0 = ~!sign + 1;
  int k_eq_0 = ~!k + 1;
  int shift_val = (k_eq_0 & (int_bit_size - 1)) | (~k_eq_0 & (int_bit_size - k));
  int cond = k_eq_0 | x_gte_0;
  int res = (cond & xsrl) | (~cond & (xsrl | (~0 << shift_val)));
  return res;
}
