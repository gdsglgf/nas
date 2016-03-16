#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return x * cos(x) - 2;
}

int isSameSign(double x, double y) {
    if (x * y > 0) {
        return 1;
    }
    return 0;
}

void binary() {
    double from = -4;
    double to = -2;
    double mid;
    double temp;
    while (1) {
        mid = (to + from) / 2;
        temp = f(mid);
        if (fabs(temp) < 1e-6) {
            break;
        }
        if (isSameSign(temp, f(from))) {
            from = mid;
        } else {
            to = mid;
        }
        if (fabs(to - from) < 1e-6) {
            break;
        }
    }
    printf("%g\n", mid);
}

int main() {
    binary();

    return 0;
}