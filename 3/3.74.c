#include <limits.h>
#include <assert.h>
#include <stdio.h>

typedef enum {
  NEG,
  ZERO,
  POS,
  OTHER
} range_t;

range_t find_range1(float x);
range_t find_range2(float x);

int main() {
  unsigned fb;
  float f;
  for (fb = 0; fb < UINT_MAX; fb++) {
    f = *((float *) &fb);
    assert(find_range1(f) == find_range2(f));
  }
  fb = UINT_MAX;
  f = *((float *) &fb);
  assert(find_range1(f) == find_range2(f));
  return 0;
}

range_t find_range1(float x) {
  int result;
  if (x < 0) {
    result = NEG;
  } else if (x == 0) {
    result = ZERO;
  } else if (x > 0) {
    result = POS;
  } else {
    result = OTHER;
  }
  return result;
}

/*
 * Ordering S2:S1    CF    ZF    PF
 * Unordered         1     1     1
 * S2 < S1           1     0     0
 * S2 = S1           0     1     0
 * S2 > S1           0     0     0
 * */
range_t find_range2(float x) {
  range_t result;
  asm volatile (
    "vxorps %%xmm1, %%xmm1, %%xmm1    # xmm1 = 0\n\t"
    "vucomiss %%xmm1, %%xmm0          # x:0\n\t"
    "movl $0, %%ecx                   # ecx = NEG\n\t"
    "movl $1, %%edi                   # edi = ZERO\n\t"
    "movl $2, %%esi                   # esi = POS\n\t"
    "movl $3, %%edx                   # edx = OTHER\n\t"
    "cmovb %%ecx, %[result]           # ecx = NEG\n\t"
    "cmova %%esi, %[result]           # if x > 0 res = POS\n\t"
    "cmove %%edi, %[result]           # if x = 0 res = ZERO\n\t"
    "cmovp %%edx, %[result]           # if x is NaN res = OTHER\n\t"
    : [result] "=r" (result) /* outputs */
    : "x" (x)                /* inputs */
    : "ecx", "edi", "esi", "edx",
      "xmm1", "cc"           /* overwrites */
  );
  return result;
}
