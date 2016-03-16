#include <stdio.h>

int f(int a[], int n, int x) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum = sum * x + a[i];
    }
    return sum;
}

int main() {
    int a[] = {7, 3, -5, 11};
    printf("%d\n", f(a, 4, 23));

    int b[] = {1, 1, 1, 1};
    printf("%d\n", f(b, 4, 1));

    return 0;
}