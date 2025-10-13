#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f);
float u2f(unsigned u);

int main(int argc, char **argv) {
  unsigned not_eq_cnt = 0;
  float expected, f_neg_u;
  for (unsigned u = 0; u < UINT_MAX; ++u) {
    expected = -u2f(u);
    f_neg_u = u2f(float_negate((float_bits) u));
    if (expected != f_neg_u) {
      ++not_eq_cnt;
    }
  }
  expected = -u2f(UINT_MAX);
  f_neg_u = u2f(float_negate((float_bits) UINT_MAX));
  if (expected != f_neg_u) {
    ++not_eq_cnt;
  }
  // 2^24 - 2; +inf, -inf
  assert(not_eq_cnt == (1 << 24) - 2);
  return 0;
}

float_bits float_negate(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  float_bits res;
  if (exp == 0xFF && frac != 0) {
    // NaN
    res = f;
  } else {
    res = ((!sign) << 31) | (exp << 23) | frac;
  }
  return res;
}

float u2f(unsigned u) {
  return *((float *) &u);
}
