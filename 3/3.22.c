#include <stdio.h>

int main() {
  int res = 1;
  int n = 14;
  do {
    res *= n;
    --n;
  } while (n > 1);
  printf("n! = %i\n", res); /* 1 278 945 280 */

  n = 14;
  long lres = 1;
  do {
    lres *= n;
    --n;
  } while (n > 1);
  printf("n! = %li\n", lres); /* 87 178 291 200 */
  return 0;
}
