#include <stdio.h>

int shifts_are_ariphmetic();

int main(int argc, char **argv) {
  printf("shifts are ariphmetic: %d\n", shifts_are_ariphmetic());
  return 0;
}

int shifts_are_ariphmetic() {
  return !((-1 >> 1) ^ -1);
}
