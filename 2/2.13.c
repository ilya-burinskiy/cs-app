int bis(int x, int m); // bit set. set 1 at each bit position where m is 1
int bic(int x, int m); // bit clear. set 0 at each bit position where m is 0

/*
0111 `bis` 1000 = 1111 (x | m)
0011 `bis` 0100 = 0011 | 0100 = 0111

0111 `bic` 1000 = 0111 (x & ~m)

1011 & ~0010 = 1011 & 1101 = 1001

1011 ^ 0010 = 1001
(1011 | 0010) & ~(1011 & 0010) = 1011 & ~(0010) = 1011 & 1101 = 1001

^ === (a | b) & ~(a & b)
(a | b) & (~a | ~b) = (a | b) & ~a | (a | b) & ~b = a & ~a | b & ~a | a & ~b | b & ~b
= b & ~a | a & ~b
= bis(bic(x, y), bic(y, x))
*/
int bool_or(int x, int y) {
    int result = bis(x, y);
    return result;
}

int bool_xor(int x, int y) {
    int result = bis(bic(x, y), bic(y, x));
    return result;
}
