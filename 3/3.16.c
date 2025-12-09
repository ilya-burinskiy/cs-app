void cond(short a, short *p) {
  if (a && *p < a) {
    *p = a;
  }
}

/*
 * cond:
 *   testw %di, %di
 *   je .L1
 *   cmpw %di, (%rsi)
 *   jge .L1
 *   movw %di, (%rsi)
 * .L1:
 *   ret
 * */

// A.
void goto_cond(short a, short *p) {
  if (!a) {
    goto L1;
  }
  if (*p >= a) {
    goto L1;
  }
  *p = a;
L1:
  return;
}

// B. !(a && *p < a) == !a || *p >= a
