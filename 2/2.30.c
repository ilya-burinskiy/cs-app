int tadd_ok(int x, int y);

int tadd_ok(int x, int y) {
    int s = x + y;
    if (x >= 0 && y >= 0 && s < 0) {
        return 0;
    } else if (x < 0 && y < 0 && s >= 0) {
        return 0;
    } else {
        return 1;
    }
    return 0;
}
