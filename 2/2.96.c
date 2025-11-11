#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

int float_f2i(float_bits f);
float u2f(unsigned u);
int pop(unsigned x);

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
  unsigned frac = f & 0x7FFFFF;
  int res;
  if (exp && exp != 0xFF) {
    // Normalized
    int e = exp - 127;
    if (e < 0) {
      res = 0;
    } else if (sign == 0 && e == 0) {
      res = 1;
    } else if (sign == 0 && e < 31) {
      // ~(x | -x) - слово с единицами в позициях завершающих нулевых битов
      // и с нулевыми битами во всех остальных местах
      int shift_val = 23 - pop(~(frac | -frac));
      frac >>= shift_val;
      res = (1 << e) + (1 << (e - shift_val)) * frac;
    } else if (sign == 0 && e >= 31) {
      res = 0x80000000;
    } else if (sign == 1 && e == 0) {
      res = -1;
    } else if (sign == 1 && e <= 31) {
      int shift_val = 23 - pop(~(frac | -frac));
      frac >>= shift_val;
      res = -((1 << e) + (1 << (e - shift_val)) * frac);
    } else if (sign == 1 && e > 31) {
      res = 0x80000000;
    }
  } else if (!exp) {
    // Denormalized
    res = 0;
  } else {
    // Inf or NaN
    res = 1 << 31;
  }
  return res;
}

float u2f(unsigned u) {
  return *((float *) &u);
}

int pop(unsigned x) {
  x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
  x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
  x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
  return x;
}
