#define A 9
#define B 5

/*
 * align = 8
 * [8*k, 8*k + 4*A*B)
 * [8*k + 4*A*B + bias1, 8*(k+1) + 4*A*B + bias1)
 *
 * */
typedef struct {
  int x[A][B];
  long y;
} str1;

/*
 * 4*A*B + b1 = 184
 * B + b2 = 8
 * 2*A + b3 = 20
 *
 * A*B = 46 => A = 23, B = 2 => b3 = -26
 * A*B = 45 => A = 9, B = 5 => b1 = 4, b2 = 3, b3 = 2
 * */
typedef struct {
  char array[B];
  int t;
  short s[A];
  long u;
} str2;

/*
 * setVal:
 *   moslq 8(%rsi), %rax        rax = (long) q->t
 *   addq 32(%rsi), %rax        rax = rax + q->u
 *   movq %rax, 184(%rdi)       p->y = rax
 * */
void setVal(str1 *p, str2 *q) {
  long v1 = q->t;
  long v2 = q->u;
  p->y = v1 + v2;
}
