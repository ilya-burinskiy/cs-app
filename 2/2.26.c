#include <stdio.h>

size_t strlen(const char *s);

int strlonger(char *s, char *t) {
    /*
    A. strlen(s) == 0, strlen(t) > 0
    B. 0 + T2U(-strlen(t))
       0 + 2^32 - strlen(t)
       2^32 - strlen(t)
    C. return strlen(s) > strlen(t)
    */
    return strlen(s) - strlen(t) > 0;
}
