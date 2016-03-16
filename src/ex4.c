#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/util.h"

// 获取单位矩阵
int** E(int n) {
    int** e = createSpace(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        e[i][i] = 1;
    }
    return e;
}

/* LU分解 A = LU */
// L为对角元素为1的下三角矩阵
// U为上三角矩阵
void LU(double **data, int nrow, int ncol) {
    int i, j, k;
    for (i = 0; i < nrow - 1; i++) {
        for (j = i + 1; j < nrow; j++) {
            double factor = data[j][i] / data[i][i];    // 第j行消去因子
            data[j][i] = factor;    // 下三角元素
            for (k = i + 1; k < ncol; k++) {
                data[j][k] = data[j][k] - data[i][k] * factor;  // 上三角元素
            }
        }
    }
}

/* 列主元LU分解 PA = LU */
void major(double **data, int **p, int nrow, int ncol) {
    int i, j, k;
    for (i = 0; i < nrow - 1; i++) {
        // 找列主元
        double max = fabs(data[i][i]);
        int pos = i;
        for (j = i + 1; j < nrow; j++) {
            double cur = fabs(data[j][i]);
            if (max < cur) {
                max = cur;
                pos = j;
            }
        }

        if (i != pos) {
            // 交换矩阵data的i和pos两行
            for (j = i; j < ncol; j++) {
                double temp = data[i][j];
                data[i][j] = data[pos][j];
                data[pos][j] = temp;
            }

            // 计算P矩阵
            for (j = 0; j < ncol; j++) {
                int temp = p[i][j];
                p[i][j] = p[pos][j];
                p[pos][j] = temp;
            }
        }

        for (j = i + 1; j < nrow; j++) {
            double factor = data[j][i] / data[i][i];    // 第j行消去因子
            data[j][i] = factor;    // 下三角元素
            for (k = i + 1; k < ncol; k++) {
                data[j][k] = data[j][k] - data[i][k] * factor;  // 上三角元素
            }
        }
    }
}

/** 计算LU矩阵的逆 */
// LUX = E
void reverse(double **data, int n) {
    double **m = createDoubleSpace(n, n);

    int i, j, k;
    for (i = 0; i < n; i++) {
        // Ly_i = e_i, 计算y_i向量, 下三角求解方程
        for (j = 0; j < n; j++) {
            double sum = 0;
            for (k = 0; k < j; k++) {
                sum += data[j][k] * m[k][i];
            }
            int e = (i == j) ? 1 : 0;
            m[j][i] = e - sum;
        }

        // Ux_i = y_i, 计算x_i向量, 上三角求解方程
        for (j = n - 1; j >= 0; j--) {
            double sum = 0;
            for (k = n - 1; k > j; k--) {
                sum += data[j][k] * m[k][i];
            }
            m[j][i] = (m[j][i] - sum) / data[j][j];
        }
    }

    showDoubleData(m, n, n);
    freeDoubleSpace(m, n);
}

/** 计算LU矩阵的行列式 */
double det(double **lu, int n) {
    double m = 1;
    int i;
    for (i = 0; i < n; i++) {
        m *= lu[i][i];
    }
    return m;
}

void testLU(char* filename) {
    freopen(filename, "r", stdin);
    int nrow, ncol;
    scanf("%d %d", &nrow, &ncol);
    double **data = loadDoubleData(nrow, ncol);
    printf("origin data:\n");
    showDoubleData(data, nrow, ncol);

    LU(data, nrow, ncol);
    printf("After call LU:\n");
    showDoubleData(data, nrow, ncol);

    printf("Call reverse:\n");
    reverse(data, nrow);

    printf("det lu is %g\n", det(data, nrow));

    freeDoubleSpace(data, nrow);
}

void testMajor(char* filename) {
    freopen(filename, "r", stdin);
    int nrow, ncol;
    scanf("%d %d", &nrow, &ncol);
    double **data = loadDoubleData(nrow, ncol);
    printf("origin data:\n");
    showDoubleData(data, nrow, ncol);

    int **p = E(nrow);
    major(data, p, nrow, ncol);
    printf("After call major:\n");
    showDoubleData(data, nrow, ncol);

    printf("Matrix P is\n");
    showData(p, nrow, nrow);
    freeDoubleSpace(data, nrow);
    freeSpace(p, nrow);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    testLU(argv[1]);
    testMajor(argv[1]);
    return 0;
}