#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits);
float u2f(unsigned);
unsigned f2u(float);

int main(int argc, char **argv) {
  unsigned errors = 0;
  float expected, abs_f;
  for (unsigned f_bin = 0; f_bin < UINT_MAX; ++f_bin) {
    expected = u2f(f_bin);
    if (expected < 0) {
      expected = -expected;
    }
    abs_f = u2f(float_absval(f_bin));
    if (isnan(expected) && isnan(abs_f)) {
      continue;
    }

    if (expected != abs_f) {
      printf("Mismatch for 0x%X:\n", f_bin);
      printf("Expected: 0x%X, got: 0x%X\n", f2u(expected), f2u(abs_f));
      errors++;
      if (errors > 10) {
        break;
      }
    }
  }

  expected = u2f(UINT_MAX) * 0.5;
  abs_f = u2f(float_absval(UINT_MAX));
  assert(isnan(expected) && isnan(abs_f));

  return 0;
}

float_bits float_absval(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if (sign) {
    sign = 0;
  }
  return (sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned u) {
  return *((float *) &u);
}

unsigned f2u(float f) {
  return *((unsigned *) &f);
}
