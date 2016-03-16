#include <stdio.h>
#include <math.h>

float down_sum(int n) {
    float sum = 0;
    int i;
    for (i = 2; i <= n; i++) {
        sum = sum + 1.0 / (i * i - 1);
    }
    return sum;
}

float up_sum(int n) {
    float sum = 0;
    int i;
    for (i = n; i >= 2; i--) {
        sum = sum + 1.0 / (i * i - 1);
    }
    return sum;
}

float actual_sum(int n) {
    return 0.5 * (1.5 - 1.0 / n - 1.0 / (n + 1));
}

int main() {
    int i;
    for (i = 2; i <= 6; i += 2) {
        int n = pow(10, i);
        printf("%d,%.20f,%.20f,%.20f\n", n, down_sum(n), up_sum(n), actual_sum(n));
    }   

    return 0;
}