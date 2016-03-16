#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 创建nrow行ncol列的整数矩阵，元素值设为0
int** createSpace(int nrow, int ncol) {
    int **data;
    data = (int **)malloc(nrow * sizeof(int *));
    int i;
    for(i = 0; i < nrow; i++) {
        int size = ncol * sizeof(int);
        data[i] = (int*)malloc(size);
        memset(data[i], 0, size);
    }
    return data;
}

void freeSpace(int **a, int nrow) {
    int i;
    for (i = 0; i < nrow; i++) {
        free(a[i]);
    }
    free(a);
}

void showData(int **data, int nrow, int ncol) {
    int i, j;
    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}

// 创建nrow行ncol列的双精度矩阵，元素值设为0
double** createDoubleSpace(int nrow, int ncol) {
    double **data;
    data = (double **)malloc(nrow * sizeof(double *));
    int i;
    for(i = 0; i < nrow; i++) {
        int size = ncol * sizeof(double);
        data[i] = (double*)malloc(size);
        memset(data[i], 0, size);
    }
    return data;
}

void freeDoubleSpace(double **a, int nrow) {
    int i;
    for (i = 0; i < nrow; i++) {
        free(a[i]);
    }
    free(a);
}

double** loadDoubleData(int nrow, int ncol) {
    double **data = createDoubleSpace(nrow, ncol);
    int i, j;
    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) {
            scanf("%lf", &data[i][j]);
        }
    }
    return data;
}

void showDoubleData(double **data, int nrow, int ncol) {
    int i, j;
    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) {
            printf("%3g ", data[i][j]);
        }
        printf("\n");
    }
}

double* createDoubleArray(int n) {
    int size = n * sizeof(double);
    double* a = (double*)malloc(size);
    memset(a, 0, size);
    return a;
}

double* loadDoubleArray(int n) {
    double* a = createDoubleArray(n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
    }
    return a;
}

void showDoubleArray(double* a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%g ", a[i]);
    }
    printf("\n");
}