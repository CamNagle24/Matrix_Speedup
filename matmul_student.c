#include "matrix.h"
#include <stdlib.h>
void matmul_student(const matrix_t *A, const matrix_t *B, matrix_t *C) {
    //declare variables
    int nrows_A = A->nrows;
    int ncols_A = A->ncols;
    int ncols_B = B->ncols;
    int ncols_C = B->ncols;
    const int *A_data = A->data;
    const int *B_data = B->data;
    int i, j, k, temp_val;
    int nums_left = ncols_B % 4;
    //Go through all the rows
    for (i = 0; i < nrows_A; i++) {
        for (k = 0; k < ncols_A; k++) {
            temp_val = A_data[i * ncols_A + k]; // Access A_data using row major order taught in the book
            for (j = 0; j < ncols_B - nums_left; j += 4) { //Loop unroll by 4
                C->data[i * ncols_C + j] += temp_val * B_data[k * ncols_B + j];
                C->data[i * ncols_C + j + 1] += temp_val * B_data[k * ncols_B + j + 1];
                C->data[i * ncols_C + j + 2] += temp_val * B_data[k * ncols_B + j + 2];
                C->data[i * ncols_C + j + 3] += temp_val * B_data[k * ncols_B + j + 3];
            }
            for (; j < ncols_B; j++) { //Handle remaining numbers
                C->data[i * ncols_C + j] += temp_val * B_data[k * ncols_B + j];
            }
        }
    }
}