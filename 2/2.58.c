#include <stdio.h>

int is_little_endian();

int main(int argc, char **argv) {
  printf("is little endian: %d\n", is_little_endian());
  return 0;
}

int is_little_endian() {
  int x = 1; 
  char *xbytes = (char *) &x;
  return *xbytes == 1;
}
