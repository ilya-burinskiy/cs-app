#include <stdio.h>

typedef unsigned char *byte_pointer;

float fpwr2(int x);
float u2f(unsigned x);
void show_bytes(byte_pointer start, size_t len);

int main(int argc, char **argv) {
  float f1, f2, f3, f4, f5, f6, f7;
  f1 = fpwr2(-150);
  f2 = fpwr2(-149);
  f3 = fpwr2(-148);
  f4 = fpwr2(-127);
  f5 = fpwr2(-126);
  f6 = fpwr2(127);
  f7 = fpwr2(128);
  show_bytes((byte_pointer) &f1, 4);
  show_bytes((byte_pointer) &f2, 4);
  show_bytes((byte_pointer) &f3, 4);
  show_bytes((byte_pointer) &f4, 4);
  show_bytes((byte_pointer) &f5, 4);
  show_bytes((byte_pointer) &f6, 4);
  show_bytes((byte_pointer) &f7, 4);
  return 0;
}

void show_bytes(byte_pointer start, size_t len) {
  int i;
  for (i = len - 1; i >= 0; i--) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

float fpwr2(int x) {
  unsigned exp, frac;
  unsigned u;

  if (x < -149) {
    // Too small. Return 0.0
    exp = 0;
    frac = 0;
  } else if (x < -126) {
    // Denormalized result
    exp = 0;
    frac = 1 << (x + 149);
  } else if (x < 128) {
    // Normalized result
    exp = x + 127;
    frac = 0;
  } else {
    // Too big. Return +inf
    exp = 255;
    frac = 0;
  }

  u = exp << 23 | frac;
  return u2f(u);
}

float u2f(unsigned x) {
  return *((float *) &x);
}
