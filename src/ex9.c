#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isEnd(double x, double y) {
    if (fabs(x - y) > 1e-6) {
        return 0;
    }
    return 1;
}

// 原函数f(x)
double f1(double x) {
    return (2 * x * x * x - 5 * x - 1);
}

// 原函数导数
double df1(double x) {
    return (6 * x * x - 5);
}

// newton法求解
void newton1() {
    double x = 1;
    double y;
    while (1) {
        y = x - f1(x) / df1(x);
        if (isEnd(x, y)) {
            break;
        }
        x = y;
    }
    printf("%g\n", x);
}

// 弦截法求解
void cut1() {
    double x = 1;
    double y = 2;
    double temp;
    while (1) {
        temp = x - f1(x) * (x - y) / (f1(x) - f1(y));
        if (isEnd(x, temp)) {
            break;
        }
        x = temp;
    }
    printf("%g\n", x);
}

double f2(double x) {
    return exp(x) * sin(x);
}

double df2(double x) {
    return exp(x) * (sin(x) + cos(x));
}

void newton2() {
    double x = -3;
    double y;
    while (1) {
        y = x - f2(x) / df2(x);
        if (isEnd(x, y)) {
            break;
        }
        x = y;
    }
    printf("%g\n", x);
}

void cut2() {
    double x = -4;
    double y = -3;
    double temp;
    while (1) {
        temp = x - f2(x) * (x - y) / (f2(x) - f2(y));
        if (isEnd(x, temp)) {
            break;
        }
        x = temp;
    }
    printf("%g\n", x);
}

int main() {
    newton1();
    cut1();

    newton2();
    cut2();

    return 0;
}