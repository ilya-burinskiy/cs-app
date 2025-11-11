#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

int float_f2i(float_bits f);
float u2f(unsigned u);

int main(int argc, char **argv) {
  // Inf, -Inf
  assert(float_f2i(0x7F800000) == 0x80000000);
  assert(float_f2i(0xFF800000) == 0x80000000);

  // NaN
  float_bits pos_nan = 0x7F800000;
  float_bits neg_nan = 0xFF800000;
  int rounded;
  for (int frac = 1; frac <= 0x7FFFFF; ++frac) {
    pos_nan |= frac;
    rounded = float_f2i(pos_nan);
    assert(rounded == 0x80000000);
    neg_nan |= frac;
    rounded = float_f2i(neg_nan);
    assert(rounded == 0x80000000);
  }

  // Denormalized
  int expected;
  float_bits pos_denorm = 0x0;
  float_bits neg_denorm = 0x80000000;
  for (int frac = 1; frac <= 0x7FFFFF; ++frac) {
    pos_denorm |= frac;
    expected = (int) u2f(pos_denorm);
    rounded = float_f2i(pos_denorm);
    assert(expected == rounded);
    neg_denorm |= frac;
    expected = (int) u2f(neg_denorm);
    rounded = float_f2i(neg_denorm);
    assert(expected == rounded);
  }

  return 0;
}

/*
 * overflow -> 0x80000000
 * NaN      -> 0x80000000
 * Round toward zero
 * */
int float_f2i(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  int res;
  if (exp && exp != 0xFF) {
    // Normalized
    res = 0;
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
