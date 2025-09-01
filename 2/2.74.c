#include <assert.h>
#include <limits.h>

int tsub_ok(int, int);

int main(int argc, char **argv) {
  assert(!tsub_ok(INT_MIN, INT_MAX));
  assert(!tsub_ok(INT_MAX, INT_MIN));
  assert(tsub_ok(INT_MAX, 1));
  assert(tsub_ok(INT_MIN + 1, 1));
  return 0;
}

int tsub_ok(int x, int y) {
  int diff = x - y;
  if (x < 0 && y >= 0 && diff >= 0) {
    return 0;
  } else if (x >= 0 && y < 0 && diff < 0) {
    return 0;
  } else {
    return 1;
  }
}
