#include <stdio.h>

int op(int x, int y);

int main(int argc, char **argv) {
  printf("res = 0x%X\n", op(0x89ABCDEF, 0x76543210));
  return 0;
}

int op(int x, int y) {
  return (x & 0xFF) | (y & (~0 << 8));
}
