#include <limits.h>
#include <assert.h>

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
    "jp 1f                            # goto 1 if x is NaN\n\t"
    "jb 2f                            # goto 2 if x < 0\n\t"
    "ja 3f                            # goto 3 if x > 0\n\t"
    "je 4f                            # x = 0\n\t"
    "1:\n\t"
    "movl $3, %[result]               # res = OTHER\n\t"
    "jmp 5f\n\t"

    "2:\n\t"
    "movl $0, %[result]               # res = NEG\n\t"
    "jmp 5f\n\t"

    "3:\n\t"
    "movl $2, %[result]               # res = POS\n\t"
    "jmp 5f\n\t"

    "4:\n\t"
    "movl $1, %[result]               # res = ZERO\n\t"
    "jmp 5f\n\t"

    "5:\n\t"
    : [result] "=r" (result) /* outputs */
    : "x" (x)                /* inputs */
    : "xmm1", "cc"           /* overwrites */
  );
  return result;
}
