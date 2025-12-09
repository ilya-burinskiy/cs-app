#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i);

int main() {
  unsigned errors = 0;
  float f_expected;
  float_bits f_bin, f_bin_expected;
  for (int i = 0; i < INT_MAX; ++i) {
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
      if (errors > 10) {
        break;
      }
    }
  }

  return 0;
}

float_bits float_i2f(int i) {
  if (i == 0) {
    return 0;
  }
  unsigned sign, exp, frac;
  sign = i & 0x80000000;
  unsigned e = 0;
  // посчитать число ведущих нулевых битов
  while ((i & 0x80000000) != 0x80000000 && e < 32) {
    i <<= 1;
    ++e;
  }
  // неявная единица
  ++e;
  i <<= 1;
  exp = (32 - e) + 127;
  if (exp >= 151) {
    unsigned char sticky = i & 0xFF;
    sticky |= (sticky >> 4);
    sticky |= (sticky >> 2);
    sticky |= (sticky >> 1);
    sticky &= 1;
    unsigned guard_round_sticky = ((i & 0x300) >> 7) | sticky;
    switch (guard_round_sticky) {
    case 0x2:
      i -= 1 << 8;
      break;
    case 0x3:
    case 0x6:
    case 0x7:
      unsigned i_tmp = i;
      i_tmp += 1 << 8;
      // переполнение
      if (i_tmp < i) {
        ++exp;
      }
      i = i_tmp;
      break;
    default:
      break;
    }
  }
  frac = ((unsigned) i) >> 9;
  return sign | (exp << 23) | frac;
}
