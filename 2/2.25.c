float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;
    /*
    0 - 1
    0 + T2U(-1)
    0 + UMax_32 - 1
    2^32 - 1
    Solution: i < length
    */
    for (i = 0; i <= length - 1; i++) {
        result += a[i];
    }
    return result;
}
