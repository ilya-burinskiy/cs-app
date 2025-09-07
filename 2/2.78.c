#include <assert.h>

int divide_power2(int x, int k);

int main(int argc, char **argv) {
  assert(divide_power2(1, 0) == 1);
  assert(divide_power2(2, 1) == 1);
  assert(divide_power2(7, 1) == 3);
  assert(divide_power2(7, 2) == 1);
  assert(divide_power2(-1, 0) == -1);
  assert(divide_power2(-2, 1) == -1);
  assert(divide_power2(-7, 2) == -1);
  assert(divide_power2(-7, 1) == -3);
  return 0;
}

// x >= 0  ==> floor(x / 2^k)
// x < 0   ==> ceil(x / 2^k)
//
// x >> k ==> floor(x / 2^k)
// (x + (1 << k) - 1) >> k ==> ceil(x / 2^k)
int divide_power2(int x, int k) {
  int xmsb = x >> 31;
  int xlt0 = ~xmsb + 1;
  return (xlt0 & ((x + (1 << k) - 1) >> k)) | (~xlt0 & (x >> k));
}
