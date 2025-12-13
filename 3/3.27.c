#include <stdio.h>

long fibonacci(long);
long fibonacci_gd_goto(long n);

int main(int argc, char **argv) {
  for (int n = 0; n <= 10; ++n) {
    printf("fib(%i) = %li\n", n, fibonacci(n));
  }
  puts("");
  for (int n = 0; n <= 10; ++n) {
    printf("fib2(%i) = %li\n", n, fibonacci_gd_goto(n));
  }
  return 0;
}
/*
 * long fibonacci(long n) {
 *   if (n == 0 || n == 1) {
 *     return n;
 *   }
 *   long a = 0;
 *   long b = 1;
 *   long tmp;
 *   for (int i = 2; i <= n; ++i) {
 *     tmp = b;
 *     b += a;
 *     a = tmp;
 *   }
 *   return b;
 * }
 *
 * long fibonacci(long n) {
 *   if (n == 0 || n == 1) {
 *     return n;
 *   }
 *   long a = 0;
 *   long b = 1;
 *   long tmp;
 *   long i = 2;
 *   while (i <= n) {
 *     tmp = b;
 *     b += a;
 *     a = tmp;
 *     ++i;
 *   }
 *   return b;
 * }
 *
 * long fibonacci(long n) {
 *   if (n == 0 || n == 1) {
 *     return n;
 *   }
 *   long a = 0;
 *   long b = 1;
 *   long tmp;
 *   long i = 2;
 *   if (i > n) {
 *     goto done;
 *   }
 *   do {
 *     tmp = b;
 *     b += a;
 *     a = tmp;
 *     ++i;
 *   } (while i <= n);
 * done:
 *   return b;
 * }
 * */
long fibonacci(long n) {
  long a = 0;
  long b = 1;
  long i = 2;
  long tmp;
  if (i > n) {
    b = n;
    goto done;
  }
loop:
  tmp = b;
  b += a;
  a = tmp;
  ++i;
  if (i <= n) {
    goto loop;
  }
done:
  return b;
}

// From solutions
long fibonacci_gd_goto(long n) {
  long i = 2;
  long next, first = 0, second = 1;
  if (n <= 1)
    goto done;
loop:
  next = first + second;
  first = second; second = next;
  i++;
  if (i <= n) {
    goto loop;
  }
done:
  return n;
}
