#include <stdio.h>

#define BUF_SIZE 512

void good_echo();

int main() {
  good_echo();
  return 0;
}

void good_echo() {
  char buf[BUF_SIZE];
  while (fgets(buf, BUF_SIZE, stdin) != NULL) {
    printf("%s", buf);
  }
}
