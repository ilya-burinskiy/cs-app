#include <assert.h>
#include <limits.h>
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits);
float u2f(unsigned);

int main(int argc, char **argv) {
  unsigned not_eq_cnt = 0;
  float expected, f_abs_u;
  for (unsigned u = 0; u < UINT_MAX; ++u) {
    expected = u2f(u);
    if (expected < 0) {
      expected = -expected;
    }
    f_abs_u = u2f(float_absval((float_bits) u));
    if (expected != f_abs_u) {
      ++not_eq_cnt;
    }
  }
  expected = u2f(UINT_MAX);
  if (expected < 0) {
    expected = -expected;
  }
  f_abs_u = u2f(float_absval((float_bits) UINT_MAX));
  if (expected != f_abs_u) {
    ++not_eq_cnt;
  }
  assert(not_eq_cnt == (1 << 24) - 2);
  return 0;
}

float_bits float_absval(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  float_bits res;
  if (exp == 0xFF && frac != 0) {
    res = f;
  } else if (sign) {
    res = (exp << 23) | frac;
  } else {
    res = f;
  }
  return res;
}

float u2f(unsigned u) {
  return *((float *) &u);
}
