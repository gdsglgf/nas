#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/util.h"

// 判断迭代结束条件, 结束精度为1e-6
int isEnd(double* x, double*y, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (fabs(x[i] - y[i]) > 1e-6) {
            return 0;
        }
    }
    return 1;
}

// jacobi迭代
void jacobi(double** m, int n, double* b) {
    double* x = createDoubleArray(n);
    double* y = createDoubleArray(n);
    int i, j;
    while(1) {
        for (i = 0; i < n; i++) {
            double sum = 0;
            for (j = 0; j < n; j++) {
                sum += m[i][j] * y[j];
            }
            x[i] = x[i] + (b[i] - sum) / m[i][i];
        }
        if (isEnd(x, y, n)) {
            break;
        }
        for (i = 0; i < n; i++) {
            y[i] = x[i];
        }
    }
    showDoubleArray(x, n);

    free(x);
    free(y);
}

// gauss_seidel迭代
void gauss_seidel(double** m, int n, double* b) {
    double* x = createDoubleArray(n);
    double* y = createDoubleArray(n);
    int i, j;
    while(1) {
        for (i = 0; i < n; i++) {
            double sum = 0;
            for (j = 0; j < i; j++) {
                sum += m[i][j] * x[j];
            }
            for (j = i; j < n; j++) {
                sum += m[i][j] * y[j];
            }
            x[i] = x[i] + (b[i] - sum) / m[i][i];
        }
        if (isEnd(x, y, n)) {
            break;
        }
        for (i = 0; i < n; i++) {
            y[i] = x[i];
        }
    }
    showDoubleArray(x, n);

    free(x);
    free(y);
}

void test(char* filename) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    double **data = loadDoubleData(n, n);
    double *b = loadDoubleArray(n);

    printf("origin data:\n");
    showDoubleData(data, n, n);
    showDoubleArray(b, n);

    printf("Call jacobi\n");
    jacobi(data, n, b);

    printf("Call gauss_seidel\n");
    gauss_seidel(data, n, b);

    freeDoubleSpace(data, n);
    free(b);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    test(argv[1]);
    return 0;
}