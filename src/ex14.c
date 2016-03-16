#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/math_util.h"

double f(double x) {
    return x * x * cos(x);
}

void test() {
    printf("%g\n", t(f, 0, M_PI / 2, 1));
    printf("%g\n", simpson(f, 0, M_PI / 2, 1));
    printf("%g\n", cotes(f, 0, M_PI / 2, 1));
}

int main() {
    test();

    return 0;
}