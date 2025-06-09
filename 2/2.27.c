int uadd_ok(unsigned x, unsigned y);

int uadd_ok(unsigned x, unsigned y) {
    unsigned s = x + y;
    if s < x {
        return 0;
    }
    return 1;
}
