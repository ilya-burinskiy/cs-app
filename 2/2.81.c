#include <stdio.h>

int A(int k);
int B(int k, int j);
void print_bits(unsigned char *val, size_t n);

int main(int argc, char **argv) {
  int res1, res2, res3, res4;
  res1 = A(2);
  res2 = A(3);
  res3 = A(4);
  res4 = B(4, 2);
  print_bits((unsigned char *) &res1, sizeof(int));
  print_bits((unsigned char *) &res2, sizeof(int));
  print_bits((unsigned char *) &res3, sizeof(int));
  print_bits((unsigned char *) &res4, sizeof(int));
  return 0;
}

/* 1^w-k 0^k
 * 1 << k == 00010..00
 *               -----
 *                 k
 *   00010...00
 * -          1
 *  ___________
 *   00001...11
 * */
int A(int k) {
  return ~((1 << k) - 1);
}

int B(int k, int j) {
  return ((1 << k) - 1) << j;
}

void print_bits(unsigned char *val, size_t n) {
    for (int byte = n - 1; byte >= 0; byte--) {
        unsigned int mask = 0b10000000;
        for (int bit = 7; bit >= 0; bit--) {
            printf("%d", (val[byte] & mask) >> bit);
            mask = mask >> 1;
        }
    }
    printf("\n");
}
