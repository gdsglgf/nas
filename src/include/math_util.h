#include <stdio.h>
#include <stdlib.h>

// 定义函数指针
typedef double (*func)(double x);

double totalSum(func f, int begin, int end, double k, double h) {
    int i;
    double sum = 0;
    for (i = begin; i < end; i++) {
        sum += f(k);
        k += h;
    }
    return sum;
}

// 复化梯形公式求解定积分
// f 积分方程
// a 积分下限
// b 积分上限
// n 划分积分区间的份数
double t(func f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = totalSum(f, 1, n, a + h, h) * 2;
    sum = sum + f(a) + f(b);
    return sum * h / 2;
}

// 复化simpson公式求解定积分
double simpson(func f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum1 = totalSum(f, 0, n, a + h / 2, h) * 4;
    double sum2 = totalSum(f, 1, n, a + h, h) * 2;
    double sum = sum1 + sum2 + f(a) + f(b);

    return sum * h / 6;
}

double cotes(func f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum1 = totalSum(f, 0, n, a + h / 4, h) * 32;
    double sum2 = totalSum(f, 0, n, a + h / 2, h) * 12;
    double sum3 = totalSum(f, 0, n, a + h * 3 / 4, h) * 32;
    double sum4 = totalSum(f, 1, n, a + h, h) * 14;
    double sum = 7 * (f(a) + f(b)) + sum1 + sum2 + sum3 + sum4;

    return sum * h / 90;
}