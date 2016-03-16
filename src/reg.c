#include <stdio.h>
#include <stdlib.h>
#include "include/util.h"

void fillData(int **data, int n) {
    int i, j, mid = n / 2;
    data[mid][mid] = 1;
    int v = mid + 1, end = n;
    for (i = 0; i < mid; i++) {
        for (j = i; j < end; j++) {
            data[i][j] = v;
            data[j][i] = v;
            data[2 * mid - i][2 * mid - j] = v;
            data[2 * mid - j][2 * mid - i] = v;
        }
        v--;
        end--;
    }
}

int main(int argc, char *argv[]) {
    int n = 2 * atoi(argv[1]) - 1;
    printf("%d\n", n);
    if (n > 1) {
        int** mat = createSpace(n, n);
        fillData(mat, n);
        showData(mat, n, n);
        freeSpace(mat, n);
    }    

    return 0;
}