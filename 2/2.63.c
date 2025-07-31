#include <stdio.h>
#include <limits.h>

unsigned srl(unsigned x, int k);
int sra(int x, int k);

int main(int argc, char **argv) {
  // unsigned int ushifted, uexpected;
  // for (unsigned x = 0; x < UINT_MAX; ++x) {
  //   for (int k = 0; k < (sizeof(int) << 3) - 1; ++k) {
  //     ushifted = srl(x, k);
  //     uexpected = x >> k;
  //     if (ushifted != uexpected) {
  //       printf("x: 0x%X; k: %d; srl: 0x%X; expected: 0x%X\n", x, k, ushifted, uexpected);
  //       return 1;
  //     }
  //   }
  // }
  // for (int k = 0; k < (sizeof(int) << 3) - 1; ++k) {
  //   ushifted = srl(x, k);
  //   uexpected = x >> k;
  //   if (ushifted != uexpected) {
  //     printf("x: 0x%X; k: %d; srl: 0x%X; expected: 0x%X\n", x, k, ushifted, uexpected);
  //     return 1;
  //   }
  // }

  int shifted, expected;
  for (int x = INT_MIN; x < INT_MAX; ++x) {
    for (int k = 0; k < (sizeof(int) << 3) - 1; ++k) {
      shifted = sra(x, k);
      expected = x >> k;
      if (shifted != expected) {
        printf("x: 0x%X; k: %d; sra: 0x%X; expected: 0x%X\n", x, k, shifted, expected);
        return 1;
      }
    }
  }
  return 0;
}

unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
  int int_bit_size = sizeof(int) << 3;
  int msb = x & (1 << (int_bit_size - 1));
  int msb_eq_0 = ~!msb + 1;
  int k_eq_0 = ~!k + 1;
  int shift_val = (k_eq_0 & (int_bit_size - 1)) | (~k_eq_0 & (int_bit_size - k));
  int cond = k_eq_0 | msb_eq_0;
  unsigned res = (cond & xsra) | (~cond & (xsra & ~(~0 << shift_val)));
  return res;
}

int sra(int x, int k) {
  int xsrl = (unsigned) x >> k;
  int int_bit_size = sizeof(int) << 3;
  int msb = x & (1 << (int_bit_size - 1));
  int msb_eq_0 = ~!msb + 1;
  int k_eq_0 = ~!k + 1;
  int shift_val = (k_eq_0 & (int_bit_size - 1)) | (~k_eq_0 & (int_bit_size - k));
  int cond = k_eq_0 | msb_eq_0;
  int res = (cond & xsrl) | (~cond & (xsrl | (~0 << shift_val)));
  return res;
}
