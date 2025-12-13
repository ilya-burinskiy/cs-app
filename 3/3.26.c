#include <assert.h>
#include <stdio.h>

long test_one(unsigned long x);
long parity(unsigned long x);

int main(int argc, char **argv) {
  // assert(test_one(0) == parity(0));
  // assert(test_one(1) == parity(1));
  // assert(test_one(2) == parity(2));
  // assert(test_one(3) == parity(3));
  // assert(test_one(4) == parity(4));
  // assert(test_one(5) == parity(5));

  assert(test_one(0) == parity(0));
  assert(test_one(1) == parity(1));
  assert(test_one(2) == parity(2));
  assert(test_one(3) == parity(3));
  return 0;
}

/*
 * # rdi <- x
 * test_one:
 *   movl $0, %eax # rax <- 0 (val)
 *   jmp .L5
 * .L6:
 *   xorq %rdi, %rax  # rax <- rax ^ x
 *   shrq %rdi        # rdi <- rdi >> 1 (x / 2)
 * .L5:
 *   testq %rdi, %rdi
 *   jne .L6          # if x != 0 goto .L6
 *   andl $1, %eax    # eax <- eax & 1
 *   ret
 * */
long test_one(unsigned long x) {
  long val = 0;
  while (x != 0) {
    val = val ^ x;
    x = x >> 1;
  }
  return val & 1;
}

// returns 1 if there an odd number of 1 in x, 0 if even
long parity(unsigned long x) {
  x = x ^ (x >> 1);
  x = x ^ (x >> 2);
  x = x ^ (x >> 4);
  x = x ^ (x >> 8);
  x = x ^ (x >> 16);
  x = x ^ (x >> 32);
  return x & 1;
}
