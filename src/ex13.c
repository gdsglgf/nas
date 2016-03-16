#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/math_util.h"

double f(double x) {
    return x * x * sin(x);
}

void test() {
    int n[4] = {20, 40, 80, 200};
    int i;
    for (i = 0; i < 4; i++) {
        printf("%g,%g\n", t(f, -2, 2, n[i]), simpson(f, -2, 2, n[i]));
    }
}

int main() {
    test();

    return 0;
}