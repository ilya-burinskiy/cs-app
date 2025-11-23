#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i);

/*
 * - if halfaway
 *   - if round downward
 *       discard trailing bits
 *   - if round upward
 *       add 0.0...1
 * - if not halfaway
 *     round upward
 * 
 * i = 0x2000006
 * 0000 0010 0...00 0110
 * _______*_ _...__ _**_
 *     6  1    22    2 1
 * i << 7
 * - halfaway
 * - 0...001 < 0...0011 < 0...010
 * 0...001100000000
 *       ^**.......
 *       | 
 *       r    9
 *        110000000
 * 7 + (32 - 7 - 23) = 9
 * 
 * i = 0x1000006
 * 0000 0001 0...00 0110
 * --------* -...__
 *     7   1   21    2 1
 * i << 8
 * 0...0011000000000
 *        ^*........
 *        | 
 *        r
 *        1100000000
 * 8 + (32 - 8 - 23) = 8 + 1 = 9
 *
 *
 * 32 - k - 23 = 9 - k
 * i << k = b_i + k
 *
 * 0...0011000000000
 *        ^**.......
 *        |  -------
 *        r     k   
 * */

int main(int argc, char **argv) {
  unsigned errors = 0;
  float f_expected;
  float_bits f_bin, f_bin_expected;
  // for (int i = 0; i < INT_MAX; ++i) {
    // int i = 0x1000000;
    // int i = 0x1000003;
    // 0000 0010 ... 0110
    // 0000 ... 0011 0000 0000
    // 0000 ... 0001 1000 0000
    // int i = 0x2000006;
    int i = 0x1000006;
    // int i = 0x2000003;
    f_bin = float_i2f(i);
    f_expected = (float) i;
    f_bin_expected = *((float_bits *) &f_expected);
    if (f_bin != f_bin_expected) {
      printf("Mismatch for 0x%X:\n", i);
      printf(
        "Expected: 0x%X (%f), got: 0x%X (%f)\n",
        f_bin_expected, *((float *) &f_bin_expected),
        f_bin, *((float *) &f_bin)
      );
      errors++;
      // if (errors > 10) {
      //   break;
      // }
    }
  // }

  return 0;
}

float_bits float_i2f(int i) {
  if (i == 0) {
    return 0;
  }
  unsigned sign, exp, frac;
  sign = 0;
  int i_tmp = i;
  unsigned leading_0bits = 0;
  while ((i & 0x80000000) != 0x80000000 && leading_0bits < 32) {
    i <<= 1;
    ++leading_0bits;
  }
  // неявная единица
  ++leading_0bits;
  i <<= 1;
  exp = (32 - leading_0bits) + 127;
  if (exp >= 151) {
    // unsigned trailing_bits_cnt = (32 - leading_0bits) - 23;
    unsigned add = ((i & (3 << 8)) == (3 << 8)) << 9; // 0x2000006
    unsigned sum = i + add;
    // переполнение
    if (sum < i) {
      ++exp;
    }
    i = sum;
  }
  frac = ((unsigned) i) >> 9;
  return (sign << 31) | (exp << 23) | frac;
}
