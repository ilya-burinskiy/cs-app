#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int tmult_ok(int x, int y) {
    // Если написать int64_t p = x * y; то сначала будет вычислено произведение
    // (вероятно с переполнением) и потом расширение до 64 битов
    int64_t p = (int64_t) x * y;
    return p == (int) p;
}

int main(int argc, char **argv) {
    int x = 3500000000;
    int y = 100;
    printf("res = %d\n", tmult_ok(x, y));
    return 0;
}
