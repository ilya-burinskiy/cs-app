#include <stdio.h>

void inplace_swap(int *x, int *y);
void print_array(int *arr, size_t n);
void reverse_array(int a[], int cnt);

int main(int argc, char **argv) {
    int arr1[1] = {1};
    int arr2[2] = {1, 2};
    int arr3[3] = {1, 2, 3};

    reverse_array(arr1, 1);
    reverse_array(arr2, 2);
    reverse_array(arr3, 3);

    print_array(arr1, 1);
    print_array(arr2, 2);
    print_array(arr3, 3);
}

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void print_array(int *arr, size_t n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%d\n", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }
}

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1; first < last; first++, last--) {
        inplace_swap(&a[first], &a[last]);
    }
}
