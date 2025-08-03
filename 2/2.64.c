#include <stdio.h>

int any_odd_one(unsigned x);

int main(int argc, char **argv) {
  printf("any_odd_one(%i): %i\n", 0, any_odd_one(0));
  printf("any_odd_one(%i): %i\n", 1, any_odd_one(1));
  printf("any_odd_one(%i): %i\n", 1, any_odd_one(4));
  printf("any_odd_one(%i): %i\n", 9, any_odd_one(9));
  return 0;
}

int any_odd_one(unsigned x) {
  int mask = 0x99999999;
  return (x & mask) != 0;
}
