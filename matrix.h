#ifndef MATRX_H
#define MATRIX_H

#define MGET(mat, i, j) ((mat)->data[((i)*((mat)->ncols)) + (j)])
#define MSET(mat, i, j, x) ((mat)->data[((i)*((mat)->ncols)) + (j)] = (x))

#define RESULTS_LEN 5

// Struct to hold a matrix which has been "squished" to one dimension
typedef struct {
    long nrows;
    long ncols;
    int *data;
} matrix_t;

/*
 * Computes five different sums of elements in the array. Each sum is computed
 * from the set of elements with the same remainder when their respective
 * indexes are divided by 5. That is, results[x] is the sum of all matrix
 * elements with an index i such that i % 5 == x.
 * Arguments:
 *   matrix: Pointer to a matrix_t containing data to sum
 *   results: Array of 5 longs to hold sums
 */
void get_every_fifth(const matrix_t *matrix, long results[RESULTS_LEN]);

/*
 * A version of get_every_fifth to be written by YOU. Takes the same arguments
 * and should provide the same functionality but in a way which is better
 * optimized.
 */
void get_every_fifth_student(const matrix_t *matrix, long results[RESULTS_LEN]);

/*
 * Computes the sum of every element in a matrix
 * Arguments:
 *   matrix: Pointer to a matrix_t containing data to sum
 * Returns: Sum of all matrix elements
 */
long get_every(const matrix_t *matrix);

/*
 * A Version of get_every to be written by YOU. Takes the same arguments and
 * returns the same value. It should provide the same functionality as
 * get_every but in a way which is better optimized.
 */
long get_every_student(const matrix_t *matrix);

/*
 * Computes the product of two matrices and stores result in a third matrix
 * Mathematically: C = A*B
 * Assumes that A->ncols == B->nrows
 * Assumes C is already set up such that C->nrows == A->nrows and C->ncols == B->ncols
 * Arguments:
 *  A: First multiplication operand
 *  B: Second multiplication operand
 *  C: Destination
 */
void matmul(const matrix_t *A, const matrix_t *B, matrix_t *C);

/*
 * A version of matmul to be written by YOU. Takes the same arguments and should
 * provide the same functionality but in a way which is better optimized.
 */
void matmul_student(const matrix_t *A, const matrix_t *B, matrix_t *C);

/*
 * Takes in a matrix and its dimensions and fills the matrix with pseudorandom
 * numbers. Will fill the matrix with the same numbers every time.
 */
void set_up_random_matrix(matrix_t *matrix, int rows, int cols, int seed);

/*
 * Takes in a matrix and its dimensions and fills the matrix with all zeros.
 */
void set_up_zero_matrix(matrix_t *matrix, int rows, int cols);

/*
 * Frees the memory allocated for the given matrix
 */
void free_matrix(matrix_t *matrix);

/*
 * Initializes all values of the results array to zero
 */
void initialize_results(long results[RESULTS_LEN]);

#endif // MATRIX_H
