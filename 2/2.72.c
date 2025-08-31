#include <stdio.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes);

int main(int argc, char **argv) {
  unsigned res = 1 - 2;
  printf("res = 0x%X\n", res);
  return 0;
}

// A. maxbytes приводится к unsigned int, maxbytes - sizeof(val) всегда
// больше или равно 0
// B. maxbytes >= (int) sizeof(val)
void copy_int(int val, void *buf, int maxbytes) {
  if (maxbytes - sizeof(val) >= 0) {
    memcpy(buf, (void *) &val, sizeof(val));
  }
}
