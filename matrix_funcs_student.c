#include "matrix.h"

void get_every_fifth_student(const matrix_t *matrix, long results[RESULTS_LEN]) {
    //Declare variables
    int size = matrix->ncols;
    int nums_left = size % 5;
    const int *data = matrix->data;
    int j, i;
    long temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0;
    //Initialize the results array to all 0s
    for(int k = 0; k < RESULTS_LEN; k++) {
        results[k] = 0;
    }
    //Go through each row addding up to the columns - the leftovers then adding the leftovers for each row
    for (i = 0; i < matrix->nrows; i++) {
        for (j = 0; j < matrix->ncols - nums_left; j += 5) {
            temp1 += *(data++);
            temp2 += *(data++);
            temp3 += *(data++);
            temp4 += *(data++);
            temp5 += *(data++);
        }
        for (; j < matrix->ncols; j++) {
            results[j % 5] += *(data++);
        }
    }
    //For each 5th number results we get add that to the results array
    results[0] += temp1;
    results[1] += temp2;
    results[2] += temp3;
    results[3] += temp4;
    results[4] += temp5;

}

long get_every_student(const matrix_t *matrix) {
    //Declare variables with size being the columns of the matrix
    long sum = 0;
    int size = matrix->ncols * matrix->nrows;
    int nums_left = size % 5;
    const int *data = matrix->data;
    long temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0;
    int i;
    //Go through the 1D array for each element in the row major ordering every 5 elements
    for (i = 0; i < size - nums_left; i += 5) {
        temp1 += *(data++);
        temp2 += *(data++);
        temp3 += *(data++);
        temp4 += *(data++);
        temp5 += *(data++);
    }
    //Go through the leftovers that we have
    for (; i < size; i++) {
        sum += *(data++);
    }
    //Add all the temp to the total sum
    sum += temp1 + temp2 + temp3 + temp4 + temp5;
    return sum;
}