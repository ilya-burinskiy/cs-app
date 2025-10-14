#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f);
float u2f(unsigned);

int main(int argc, char **argv) {
  unsigned not_eq_cnt = 0;
  float expected, f_x2;
  for (unsigned f_bin = 0; f_bin < UINT_MAX; ++f_bin) {
    expected = u2f(f_bin);
    expected *= 2.0;
    f_x2 = u2f(float_twice(f_bin));
    if (expected != f_x2) {
      ++not_eq_cnt;
    }
  }
  expected = u2f(UINT_MAX);
  expected *= 2.0;
  f_x2 = u2f(float_twice(UINT_MAX));
  if (expected != f_x2) {
    ++not_eq_cnt;
  }
  assert(not_eq_cnt == (1 << 24) - 2);

  return 0;
}

float_bits float_twice(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  float_bits res;
  if (exp == 0xFF && frac) {
    // NaN
    res = f;
  } else if (exp == 0xFF && !frac) {
    // Inf
    res = f;
  } else if (!exp && !frac) {
    // Zero
    res = 0;
  } else if (exp) {
    // Normalized
    unsigned new_exp = exp + 1;
    if (new_exp == 0xFF) {
      res = (sign << 31) | (new_exp << 23);
    } else {
      res = (sign << 31) | (new_exp << 23) | frac;
    }
  } else {
    // Denormalized
    res = (sign << 31) | (frac << 1);
  }
  return res; 
}

float u2f(unsigned u) {
  return *((float *) &u);
}
