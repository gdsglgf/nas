#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/util.h"

// 矩阵cholesky分解
// A = LL^T
// L为下三角矩阵
// L^T为L的转置矩阵
void cholesky(double** m, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            double sum = 0;
            for (k = 0; k < i; k++) {
                sum += m[j][k] * m[i][k];
            }
            if (i == j) {
                m[i][i] = sqrt(m[i][i] - sum);
            } else {
                m[j][i] = (m[j][i] - sum) / m[i][i];
                m[i][j] = m[j][i];
            }
        }
    }
}

// 下三角矩阵求解方程组
// 求解顺序为从上到下
// Ly = b
double* solveDown(double** l, int n, double* b) {
    double* y = createDoubleArray(n);
    int i, j;
    for (i = 0; i < n; i++) {
        double sum = 0;
        for (j = 0; j < i; j++) {
            sum += l[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / l[i][i];
    }
    return y;
}

// 上三角矩阵求解方程组
// 求解顺序为从下往上
// Ux = y
double* solveUp(double** u, int n, double* y) {
    double* x = createDoubleArray(n);
    int i, j;
    for (i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (j = n - 1; j > i; j--) {
            sum += u[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / u[i][i];
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

void testCholesky(char* filename) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    double **data = loadDoubleData(n, n);
    double *b = loadDoubleArray(n);

    printf("origin data:\n");
    showDoubleData(data, n, n);
    showDoubleArray(b, n);

    cholesky(data, n);
    printf("After call cholesky:\n");
    showDoubleData(data, n, n);

    printf("Call solve\n");
    solve(data, n, b);

    freeDoubleSpace(data, n);
    free(b);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    testCholesky(argv[1]);
    return 0;
}