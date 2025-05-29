#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

int main(int argc, char **argv) {
    int val = 0x87654321; // 0x21, 0x43, 0x65, 0x87
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1); // little endian: 21;       big endian: 87
    show_bytes(valp, 2); // little endian: 21 43;    big endian: 87 65
    show_bytes(valp, 3); // little endian: 21 43 65; big endian: 87 65 43

    return 0;
}
