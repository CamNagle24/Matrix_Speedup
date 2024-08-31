#include <stdlib.h>
#include "matrix.h"

void get_every_fifth(const matrix_t *matrix, long results[RESULTS_LEN]) {
    for (int i = 0; i < matrix->nrows; i++) {
        for (int j = 0; j < matrix->ncols; j++) {
            int q = j % RESULTS_LEN;
            results[q] += MGET(matrix, i, j);
        }
    }
}

long get_every(const matrix_t *matrix) {
    long sum = 0;
    for (int i = 0; i < matrix->nrows; i++) {
        for (int j = 0; j < matrix->ncols; j++) {
            sum += MGET(matrix, i, j);
        }
    }
    return sum;
}

void initialize_results(long results[RESULTS_LEN]) {
    for (int i = 0; i < RESULTS_LEN; i++) {
        results[i] = 0;
    }
}

void set_up_random_matrix(matrix_t *matrix, int nrows, int ncols, int seed) {
    if (matrix == NULL) {
        return;
    }
    matrix->nrows = nrows;
    matrix->ncols = ncols;
    matrix->data = malloc(sizeof(int) * nrows * ncols);
    srand(seed);
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            MSET(matrix, i, j, rand() % 100);
        }
    }
}

void set_up_zero_matrix(matrix_t *matrix, int nrows, int ncols) {
    if (matrix == NULL) {
        return;
    }
    matrix->nrows = nrows;
    matrix->ncols = ncols;
    matrix->data = calloc(nrows * ncols, sizeof(int));
}

void free_matrix(matrix_t *matrix) {
    free(matrix->data);
}
