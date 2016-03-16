#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "include/util.h"

double sqrSum(double* a, int n) {
    double sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }

    return sum;
}

double distance(double* a, int n) {
    return sqrt(sqrSum(a, n));
}

// 计算householder矩阵
double** householder(double* w, int n) {
    double d = distance(w, n);
    w[0] -= d;
    double** h = createDoubleSpace(n, n);
    double sum = sqrSum(w, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            h[i][j] = 0 - w[i] * w[j] * 2 / sum;
            h[j][i] = h[i][j];
        }
        h[i][i] = h[i][i] + 1;
    }
    return h;
}

// 方阵乘法
double** multi(double** a, double** b, int n) {
    double** m = createDoubleSpace(n, n);
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                m[i][j] = m[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    return m;
}

double** fillQ(double** h, int n, int size) {
    double** m = createDoubleSpace(size, size);
    int diff = size - n;
    int i, j;
    for (i = 0; i < diff; i++) {
        m[i][i] = 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            m[i + diff][j + diff] = h[i][j];
        }
    }
    return m;
}

void testMulti(char* filename) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    double **a = loadDoubleData(n, n);
    double **b = loadDoubleData(n, n);

    double **c = multi(a, b, n);

    printf("Matrix a:\n");
    showDoubleData(a, n, n);
    printf("Matrix b:\n");
    showDoubleData(b, n, n);
    printf("Matrix c:\n");
    showDoubleData(c, n, n);

    freeDoubleSpace(a, n);
    freeDoubleSpace(b, n);
    freeDoubleSpace(c, n);
}

void testHouseholder() {
    const int n = 3;
    double a[] = {1, 2, 2};
    double** h = householder(a, n);
    showDoubleData(h, n, n);

    freeDoubleSpace(h, n);
}

// 单位矩阵
double** E(int n) {
    double** e = createDoubleSpace(n, n);
    int i;
    for (i = 0; i < n; i++) {
        e[i][i] = 1;
    }
    return e;
}

// 去掉矩阵的第一行和第一列
double** extractA(double** a, int n) {
    double** m = createDoubleSpace(n - 1, n - 1);
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            m[i - 1][j - 1] = a[i][j];
        }
    }
    freeDoubleSpace(a, n);
    return m;
}

// 矩阵QR分解
void QR(double** a, int n) {
    double** q = E(n);
    double** temp = a;
    int i, j;
    for (i = n; i >= 2; i--) {
        double* w = createDoubleArray(n);
        for (j = 0; j < i; j++) {
            w[j] = temp[j][0];
        }

        double** h = householder(w, i);
        printf("h is \n");
        showDoubleData(h, i, i);
        double** q1 = fillQ(h, i, n);
        printf("q is \n");
        showDoubleData(q1, n, n);

        double** temp2 = multi(q1, q, n);
        freeDoubleSpace(q, n);
        q = temp2;

        double** temp3 = extractA(multi(h, temp, i), i);
        if (i != n) {
            freeDoubleSpace(temp, i);
        }
        temp = temp3;

        freeDoubleSpace(h, i);
        freeDoubleSpace(q1, i);
        free(w);
    }

    printf("last Q^T is \n");
    showDoubleData(q, n, n);
    double** r = multi(q, a, n);
    printf("R is \n");
    showDoubleData(r, n, n);

    freeDoubleSpace(q, n);
    freeDoubleSpace(r, n);
}

void testQR(char *filename) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    double **a = loadDoubleData(n, n);
    QR(a, n);
    freeDoubleSpace(a, n);
}

int main(int argc, char *argv[]) {
    // testHouseholder();
    assert(argc == 2);
    // testMulti(argv[1]);
    testQR(argv[1]);

    return 0;
}