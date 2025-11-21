#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

int float_f2i(float_bits f);
float u2f(unsigned u);

int main(int argc, char **argv) {
  // Inf, -Inf
  assert(float_f2i(0x7F800000) == 0x80000000);
  assert(float_f2i(0xFF800000) == 0x80000000);

  float_bits f_bin;
  int expected;

  // NaN
  for (int sign = 0; sign <= 1; ++sign) {
    f_bin = (sign << 31) | (0xFF << 23);
    for (int frac = 1; frac <= 0x7FFFFF; ++frac) {
      f_bin |= frac;
      assert(float_f2i(f_bin) == 0x80000000);
    }
  }

  // Denormalized
  for (int sign = 0; sign <= 1; ++sign) {
    f_bin = (sign << 31);
    for (int frac = 1; frac <= 0x7FFFFF; ++frac) {
      expected = (int) u2f(f_bin);
      assert(float_f2i(f_bin) == expected); 
    }
  }

  // Normalized
  for (int sign = 0; sign <= 1; ++sign) {
    f_bin = sign << 31;
    for (int exp = 1; exp <= 157; ++exp) {
      f_bin |= (exp << 23);
      for (int frac = 0; frac <= 0x7FFFFF; ++frac) {
        f_bin |= frac;
        expected = (int) u2f(f_bin);
        if (float_f2i(f_bin) != expected) {
          printf("f_bin = 0x%X; expected = 0x%X\n", f_bin, expected);
          goto Exit;
        }
      }
    }
  }

Exit:
  return 0;
}

int float_f2i(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  int exp_biased = exp - 127;
  unsigned frac = f & 0x7FFFFF;
  int res;
  if (exp_biased < 0) {
    res = 0;
  } else if (exp_biased < 31) {
    int diff = exp_biased - 23;
    if (diff >= 0) {
      res = (1 << exp_biased) | (frac << diff);
    } else if (diff < 0) {
      res = (1 << exp_biased) | (frac >> -diff);
    }
    res = sign ? -res : res;
  } else {
    res = 0x80000000;
  }

  return res;
}

float u2f(unsigned u) {
  return *((float *) &u);
}
