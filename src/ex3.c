#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/util.h"

void gauss(double **data, int nrow, int ncol) {
    int i, j, k;
    for (i = 0; i < nrow - 1; i++) {
        for (j = i + 1; j < nrow; j++) {
            double factor = data[j][i] / data[i][i];    // 第j行消去因子
            for (k = i; k < ncol; k++) {
                data[j][k] = data[j][k] - data[i][k] * factor;
            }
        }
    }
}

void solve(double **data, int nrow, int ncol) {
    double* result = (double*)malloc(nrow * sizeof(double));
    int i, j;
    for (i = nrow - 1; i >= 0; i--) {
        double sum = 0;
        for (j = i + 1; j < ncol - 1; j++) {
            sum = sum + data[i][j] * result[j];
        }
        result[i] = (data[i][ncol - 1] - sum) / data[i][i];
    }

    printf("result is:\n");
    for (i = 0; i < nrow; i++) {
        printf("%g ", result[i]);
    }
    printf("\n");

    free(result);
}

void major(double **data, int nrow, int ncol) {
    int i, j, k;
    for (i = 0; i < nrow - 1; i++) {
        // find max
        double max = fabs(data[i][i]);
        int pos = i;
        for (j = i + 1; j < nrow; j++) {
            double cur = fabs(data[j][i]);
            if (max < cur) {
                max = cur;
                pos = j;
            }
        }

        // swap row of i and pos
        if (i != pos) {
            for (j = i; j < ncol; j++) {
                double temp = data[i][j];
                data[i][j] = data[pos][j];
                data[pos][j] = temp;
            }
        }

        for (j = i + 1; j < nrow; j++) {
            double factor = data[j][i] / data[i][i];    // 第j行消去因子
            for (k = i; k < ncol; k++) {
                data[j][k] = data[j][k] - data[i][k] * factor;
            }
        }
    }
}

void testGauss(char *filename) {
    freopen(filename, "r", stdin);
    int nrow, ncol;
    scanf("%d %d", &nrow, &ncol);
    double **data = loadDoubleData(nrow, ncol);
    printf("origin data:\n");
    showDoubleData(data, nrow, ncol);

    gauss(data, nrow, ncol);
    printf("After call gauss:\n");
    showDoubleData(data, nrow, ncol);
    solve(data, nrow, ncol);

    freeDoubleSpace(data, nrow);
}

void testMajor(char *filename) {
    freopen(filename, "r", stdin);
    int nrow, ncol;
    scanf("%d %d", &nrow, &ncol);
    double **data = loadDoubleData(nrow, ncol);
    printf("origin data:\n");
    showDoubleData(data, nrow, ncol);

    major(data, nrow, ncol);
    printf("After call major:\n");
    showDoubleData(data, nrow, ncol);
    solve(data, nrow, ncol);

    freeDoubleSpace(data, nrow);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    testGauss(argv[1]);
    testMajor(argv[1]);
    return 0;
}