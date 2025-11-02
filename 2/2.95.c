#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f);
float u2f(unsigned u);
unsigned f2u(float f);

int main(int argc, char **argv) {
  unsigned errors = 0;
  float expected, half_f;
  for (unsigned f_bin = 0; f_bin < UINT_MAX; ++f_bin) {
    expected = u2f(f_bin) * 0.5;
    half_f = u2f(float_half(f_bin));
    if (isnan(expected) && isnan(half_f)) {
      continue;
    }

    if (expected != half_f) {
      printf("Mismatch for 0x%X:\n", f_bin);
      printf("Expected: 0x%X, got: 0x%X\n", f2u(expected), f2u(half_f));
      errors++;
      if (errors > 10) {
        break;
      }
    }
  }
  expected = u2f(UINT_MAX) * 0.5;
  half_f = u2f(float_half(UINT_MAX));
  assert(isnan(expected) && isnan(half_f));

  return 0;
}

float_bits float_half(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;

  if (exp && exp != 0xFF) {
    // Normalized
    exp -= 1;
    if (!exp) {
      // Half f is denormalized
      unsigned add = (frac & 3) == 3;
      frac = ((1 << 22) + (frac >> 1) + add);
    }
  } else if (!exp) {
    // Denormalized
    unsigned add = (frac & 3) == 3;
    frac = ((frac >> 1) + add);
  }

  return (sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned u) {
  return *((float *) &u);
}

unsigned f2u(float f) {
  return *((unsigned *) &f);
}
