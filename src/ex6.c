#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/util.h"

// The tridiagonal matrix
// 三对角矩阵LU分解
// A = LU
void TDMLU(double** m, int n) {
    int i;
    for (i = 1; i < n; i++) {
        m[i][i - 1] = m[i][i - 1] / m[i - 1][i - 1];
        m[i][i] = m[i][i] - m[i][i - 1] * m[i - 1][i];
    }
}

// Ly = b
double* solveDown(double** m, int n, double* b) {
    double* y = createDoubleArray(n);
    y[0] = b[0];
    int i;
    for (i = 1; i < n; i++) {
        y[i] = b[i] - m[i][i - 1] * y[i - 1];
    }
    return y;
}

// Ux = y
double* solveUp(double** m, int n, double* y) {
    double* x = createDoubleArray(n);
    int end = n - 1;
    x[end] = y[end] / m[end][end];
    int i;
    for (i = end - 1; i >= 0; i--) {
        x[i] = (y[i] - m[i][i + 1] * x[i + 1]) / m[i][i];
    }
    return x;
}

// 求解方程组LUx = b
// m 已进行LU分解的方阵, m = LU
// n 方阵的维数
// b 方程组等式右边向量
void solve(double** m, int n, double* b) {
    double* y = solveDown(m, n, b);
    printf("y is\n");
    showDoubleArray(y, n);
    double* x = solveUp(m, n, y);
    printf("x is\n");
    showDoubleArray(x, n);
    free(x);
    free(y);
}

void testTDMLU(char* filename) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    double **data = loadDoubleData(n, n);
    double *b = loadDoubleArray(n);

    printf("origin data:\n");
    showDoubleData(data, n, n);
    showDoubleArray(b, n);

    TDMLU(data, n);
    printf("After call TDMLU:\n");
    showDoubleData(data, n, n);

    printf("Call solve\n");
    solve(data, n, b);

    freeDoubleSpace(data, n);
    free(b);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    testTDMLU(argv[1]);
    return 0;
}