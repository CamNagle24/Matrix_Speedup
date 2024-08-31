#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.h"

#define A_SEED 2021
#define B_SEED 4061

typedef struct timespec timespec_t;

double get_elapsed_time_sec(const timespec_t *start, const timespec_t *end) {
    long start_nanos = (long)1e9 * start->tv_sec + start->tv_nsec;
    long end_nanos = (long)1e9 * end->tv_sec + end->tv_nsec;
    return (double)(end_nanos - start_nanos) / 1e9;
}

int validate_results(const matrix_t *X, const matrix_t *Y, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (MGET(X, i, j) != MGET(Y, i, j)) {
                return 0;
            }
        }
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <a_rows> <a_cols/b_rows> <b_cols>\n", argv[0]);
        return 0;
    }
    int a_num_rows = atoi(argv[1]);
    int a_num_cols = atoi(argv[2]);
    int b_num_rows = a_num_cols;
    int b_num_cols = atoi(argv[3]);

    printf("Setting up random matrices...\n");
    matrix_t A;
    set_up_random_matrix(&A, a_num_rows, a_num_cols, A_SEED);
    matrix_t B;
    set_up_random_matrix(&B, b_num_rows, b_num_cols, B_SEED);
    matrix_t C;
    set_up_zero_matrix(&C, a_num_rows, b_num_cols);
    matrix_t D;
    set_up_zero_matrix(&D, a_num_rows, b_num_cols);

    timespec_t start;
    timespec_t end;
    double elapsed_time_sec_control;
    double elapsed_time_sec_student;

    printf("Running student version of matmul...\n");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    matmul_student(&A, &B, &D);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    elapsed_time_sec_student = get_elapsed_time_sec(&start, &end);
    printf("Completed in %.3f sec\n", elapsed_time_sec_student);

    printf("Running control version of matmul...\n");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    matmul(&A, &B, &C);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    elapsed_time_sec_control = get_elapsed_time_sec(&start, &end);
    printf("Completed in %.3f sec\n", elapsed_time_sec_control);

    printf("Validating results...\n");
    if (!validate_results(&C, &D, a_num_rows, b_num_cols)) {
        printf("Student matrix multiplication produced incorrect results.\n");
        return 0;
    }

    printf("\n");
    printf("Ratio of control time to student time: %.3f\n",
            elapsed_time_sec_control / elapsed_time_sec_student);
    return 0;
}
