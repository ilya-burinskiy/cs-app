#include <stdio.h>

void print_bits(unsigned char *val, size_t n);

/* 
A.
00000000001101011001000101000001
01001010010101100100010100000100

B.
00000000001101011001000101000001
           *********************
  01001010010101100100010100000100

21 bits
*/
int main(int argc, char **argv) {
    int ival = 3510593;
    float fval = 3510593.0;
    print_bits((unsigned char *) &ival, sizeof(int));
    print_bits((unsigned char *) &fval, sizeof(float));
}


void print_bits(unsigned char *val, size_t n) {
    for (int byte = n - 1; byte >= 0; byte--) {
        unsigned int mask = 0b10000000;
        for (int bit = 7; bit >= 0; bit--) {
            printf("%d", (val[byte] & mask) >> bit);
            mask = mask >> 1;
        }
    }
    printf("\n");
}
