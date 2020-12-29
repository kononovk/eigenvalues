#include "source.h"

void output(int l, int n, int m, double *matrix) {
    printf("\n");
    for (int i = 0; i < l && i < m; ++i) {
        for (int j = 0; j < n && j < m; ++j) {
            printf("%10.3e", matrix[i * n + j]);
        }
        printf("\n");
    }
}

