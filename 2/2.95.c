#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f);
float u2f(unsigned u);
unsigned f2u(float f);

int main(int argc, char **argv) {
  // unsigned not_eq_cnt = 0;
  // float expected, half_f;
  // for (unsigned f_bin = 0; f_bin < UINT_MAX; ++f_bin) {
  //   expected = u2f(f_bin) * 0.5;
  //   half_f = u2f(float_half(f_bin));
  //   if (expected != half_f) {
  //     ++not_eq_cnt;
  //   }
  // }
  // expected = u2f(UINT_MAX) * 0.5;
  // half_f = u2f(float_half(UINT_MAX));
  // if (expected != half_f) {
  //   ++not_eq_cnt;
  // }
  // printf("not_eq_cnt = 0x%X\n", not_eq_cnt);
  unsigned x;
  unsigned errors = 0;

  for (x = 0; ; x++) {
    float_bits fb = x;
    float f = u2f(fb);
    float_bits expected = f2u(0.5f * f);
    float_bits actual = float_half(fb);

    // NaN check: they don't compare equal
    if (isnan(f) && isnan(u2f(actual))) {
      ; // OK
    } else if (expected != actual) {
      printf("Mismatch for 0x%08x:\n", fb);
      printf("Expected: 0x%08x, got: 0x%08x\n", expected, actual);
      errors++;
      if (errors > 10) {
        break;
      }
    }
    if (x == 0xFFFFFFFF) {
        break;
    }
  }

  if (errors == 0) {
    printf("All tests passed!\n");
  } else {
    printf("Test failed with %u mismatches.\n", errors);
  }

  return 0;
}

/*
Эталонное решение
Mismatch for 0x00ffffff:
Expected: 0x00800000, got: 0x00000000
Mismatch for 0x80ffffff:
Expected: 0x80800000, got: 0x80000000 */

/*
float_bits float_half(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  unsigned add;

  if (exp == 0xFF) {
      // NaN or infinity
      return f;
  }

  if (exp == 0 || exp == 1) {
      if (exp == 1)
          frac |= 0x800000;  // restore implicit leading 1
      add = (frac & 3) == 3; // round to even
      frac = (frac >> 1) + add;
      exp = 0;
  } else {
      exp -= 1;
  }

  return (sign << 31) | (exp << 23) | (frac & 0x7FFFFF);
}
*/

/*
Mismatch for 0x00ffffff:
Expected: 0x00800000, got: 0x00000000
Mismatch for 0x80000000:
Expected: 0x80000000, got: 0x00000000
Mismatch for 0x80ffffff:
Expected: 0x80800000, got: 0x80000000
*/
float_bits float_half(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  float_bits res;
  if (exp == 0xFF) {
    // NaN or Inf
    res = f;
  } else if (!exp && !frac) {
    // Zero
    res = 0;
  } else if (exp) {
    // Normalized
    exp -= 1;
    if (exp) {
      // Half f is normalized
      res = (sign << 31) | (exp << 23) | frac;
    } else {
      // Half f is denormalized
      unsigned add = (frac & 3) == 3;
      frac = ((1 << 22) + (frac >> 1) + add) & 0x7FFFFF;
      res = (sign << 31) | frac;
    }
  } else {
    // Denormalized
    unsigned add = (frac & 3) == 3;
    frac = ((frac >> 1) + add) & 0x7FFFFF;
    res = (sign << 31) | frac;
  }

  return res;
}

float u2f(unsigned u) {
  return *((float *) &u);
}

unsigned f2u(float f) {
  return *((unsigned *) &f);
}
