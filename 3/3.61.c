#include <assert.h>
#include <stddef.h>

/*
 * Такой вариант не работает, т.к. cmov сначала подгружает
 * данные, и потом проверяет условие, а не наоборот
 * cread_alt:
 *   xorl %eax, %eax
 *   testq  %rdi, %rdi
 *   cmovne (%rdi), %rax
 *   ret
 *
 * Вариант с static локальной переменной подсмотрел
 * */
long cread_alt(long *xp) {
  static long z = 0L;
  return *(xp ? xp : &z);
}

long cread(long *xp) {
  return (xp ? *xp : 0);
}

int main() {
  long x = 1;
  long *xp = &x;
  assert(cread(NULL) == cread_alt(NULL));
  assert(cread(xp) == cread_alt(xp));
  return 0;
}
