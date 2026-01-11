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
  float f;
  for (unsigned fb = 0; fb < UINT_MAX; fb++) {
    f = *((float *) &fb);
    assert(find_range1(f) == find_range2(f));
  }
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
// range_t find_range2(float x) {
//   range_t result;
//   asm (
//     "vxorps %[x], %[x], %[x]    # xmm1 = 0\n\t"
//     "vucomiss %[x], %%xmm0          # x:0\n\t"
//     "jp .nan                          # goto .nan if x is NaN\n\t"
//     "jb .below0                       # x < 0\n\t"
//     "ja .above0                       # x > 0\n\t"
//     "je .zero                         # x = 0\n\t"
//   ".nan:\n\t"
//     "movl $3, %[result]                  # res = OTHER\n\t"
//     "ret"
//   ".below0:\n\t"
//     "movl $0, %[result]                   # res = NEG\n\t"
//     "ret"
//   ".above0:\n\t"
//     "movl $2, %[result]                  # res = POS\n\t"
//     "ret"
//   ".zero:\n\t"
//     "movl $1, %[result]                   # res = ZERO\n\t"
//     "ret"
//     : [result] "=r" (result) /* outputs */
//     : [x] "r" (x)            /* inputs */
//     : "cc"         /* overwrites */
//   );
//   return result;
// }
