typedef unsigned float_bits

float_bits float_twice(float_bits f);

int main(int argc, char **argv) {
  return 0;
}

// Nan
// Zero
// Inf
// Normalized
// Denormalized
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

  }
  return res; 
}
