#include "matrix.h"

void matmul(const matrix_t *A, const matrix_t *B, matrix_t *C) {
    for (int i = 0; i < A->nrows; i++) {
        for (int j = 0; j < B->ncols; j++) {
            int sum = 0;
            for (int k = 0; k < A->ncols; k++) {
                sum += MGET(A, i, k) * MGET(B, k, j);
            }
            MSET(C, i, j, sum);
        }
    }
}
