#include <stdio.h>

int main() {
  long sum = 0;
  long i;
  i = 0;
  goto loop_cond;
loop_body:
  if (i & 1) {
    goto loop_upd_expr;
  }
  sum += i;
loop_upd_expr:
  i++;
loop_cond:
  if (i < 10) {
    goto loop_body;
  }
  printf("sum = %li\n", sum);
  return 0;
}

/*
 *   long sum = 0;
 *   long i;
 *   i = 0;
 *   goto for_cond;
 * for_body:
 *   if (i & 1) {
 *     goto for_upd_expr;
 *   }
 *   sum += i;
 * for_upd_expr:
 *   i++;
 *   
 * for_cond:
 *   if (i < 10) {
 *     goto for_body;
 *   }
 * */
