#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f);
float u2f(unsigned);
unsigned f2u(float);

int main(int argc, char **argv) {
  unsigned errors = 0;
  float expected, double_f;
  for (unsigned f_bin = 0; f_bin < UINT_MAX; ++f_bin) {
    expected = 2.0 * u2f(f_bin);
    double_f = u2f(float_twice(f_bin));
    if (isnan(expected) && isnan(double_f)) {
      continue;
    }

    if (expected != double_f) {
      printf("Mismatch for 0x%X:\n", f_bin);
      printf("Expected: 0x%X, got: 0x%X\n", f2u(expected), f2u(double_f));
      errors++;
      if (errors > 10) {
        break;
      }
    }
  }

  expected = 2.0 * u2f(UINT_MAX);
  double_f = u2f(float_twice(UINT_MAX));
  assert(isnan(expected) && double_f);

  return 0;
}

float_bits float_twice(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;

  if (exp && exp != 0xFF) {
    // Normalized
    exp = exp + 1;
    if (exp == 0xFF) {
      frac = 0;
    }
  } else if (!exp) {
    // Denormalized
    frac <<= 1;
  }

  return (sign << 31) | (exp << 23) | frac; 
}

float u2f(unsigned u) {
  return *((float *) &u);
}

unsigned f2u(float f) {
  return *((unsigned *) &f);
}
