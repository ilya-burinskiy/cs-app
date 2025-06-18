#include <stdio.h>

int div16(int x) {
    // x < 0 => bias = 0xf = 15
    // x >= 0 => bias = 0x0
    int bias = (x >> 31) & 0xf;
    return (x + bias) >> 4;
}

int main(int argc, char **argv) {
    printf("32 / 16 = %d\n", div16(37));
    return 0;
}
