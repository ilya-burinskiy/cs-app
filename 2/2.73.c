#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y);

int main(int argc, char **argv) {
  assert(saturating_add(INT_MAX, INT_MAX) == INT_MAX);
  assert(saturating_add(INT_MAX, 0) == INT_MAX);
  assert(saturating_add(INT_MAX, 1) == INT_MAX);
  assert(saturating_add(INT_MIN, INT_MIN) == INT_MIN);
  assert(saturating_add(INT_MIN, 0) == INT_MIN);
  assert(saturating_add(INT_MIN, -1) == INT_MIN);
  assert(saturating_add(1, 2) == 3);
  return 0;
}

int saturating_add(int x, int y) {
  int sum, xlt0, ylt0, sum_lt0, neg_overflow_cond, pos_overflow_cond;
  sum = x + y;
  xlt0 = ~(x >> 31) + 1;
  ylt0 = ~(y >> 31) + 1;
  sum_lt0 = ~(sum >> 31) + 1;
  pos_overflow_cond = ~(~xlt0 & ~ylt0 & sum_lt0) + 1;
  neg_overflow_cond = ~(xlt0 & ylt0 & ~sum_lt0) + 1;

  return (pos_overflow_cond & INT_MAX)
         | (~pos_overflow_cond
             & ((neg_overflow_cond & INT_MIN)
               | (~neg_overflow_cond & sum)));
}
