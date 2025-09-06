#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

void *calloc(size_t nmemb, size_t size);

typedef struct S {
  int i;
  char j;
} S;

int main(int argc, char **argv) {
  S *a1, *a2, *a3;
  a1 = calloc(50, sizeof(S));
  for (int i = 0; i < 50; ++i) {
    assert(a1[i].i == 0 && a1[i].j == 0);
  }
  a2 = calloc((unsigned) (-1), sizeof(S));
  a3 = calloc(0, sizeof(S));
  assert(a2 == NULL);
  assert(a3 == NULL);
  free(a1);
  free(a2);
  free(a3);
  return 0;
}

void *calloc(size_t nmemb, size_t size) {
  void *arr = NULL;
  unsigned totsize = 0;
  if (nmemb != 0 && size != 0) {
    totsize = nmemb * size;
    if (totsize / nmemb == size) {
      arr = malloc(nmemb * size);
      memset(arr, 0, totsize);
    }
  }
  return arr;
}
