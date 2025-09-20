#include <stdio.h>
#include <assert.h>

int float_le(float x, float y);
unsigned f2u(float x);

int main(int argc, char **argv) {
  assert((8.0 <= 8.0) == (float_le(8.0, 8.0)));
  assert((-8.0 <= -8.0) == (float_le(-8.0, -8.0)));
  assert((-8.0 <= 8.1) == (float_le(-8.0, 8.1)));
  assert((-8.0 <= -10.0) == (float_le(-8.0, -10.0)));
  assert((-0 <= +0) == float_le(-0, +0));
  assert((+0 <= -0) == float_le(+0, -0));
  return 0;
}

int float_le(float x, float y) {
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;
  return (sx > sy) ||
         ((sx == sy == 0) && (ux <= uy)) ||
         ((sx == sy == 1) && (ux >= uy));
}

unsigned f2u(float x) {
  return *((unsigned *) &x);
}
