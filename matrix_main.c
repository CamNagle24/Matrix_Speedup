#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.h"

#define RAND_SEED 2021
#define NUM_ROWS 14000
#define NUM_COLS 100000
#define NUM_ROWS_ODD 12439
#define NUM_COLS_ODD 113227

typedef struct timespec timespec_t;

double get_elapsed_time_sec(const timespec_t *start, const timespec_t *end) {
    long start_nanos = (long)1e9 * start->tv_sec + start->tv_nsec;
    long end_nanos = (long)1e9 * end->tv_sec + end->tv_nsec;
    return (double)(end_nanos - start_nanos) / 1e9;
}

int main(int argc, char **argv) {
    int is_even_size;
	if (argc != 2) {
		printf("Usage: %s <even/odd size>\n", argv[0]);
		return 1;
	} else {
        if (strcmp(argv[1], "--even") == 0) {
            is_even_size = 1;
        } else if (strcmp(argv[1], "--odd") == 0) {
            is_even_size = 0;
        } else {
            printf("Unkown command-line argument %s\n", argv[1]);
            return 1;
        }
    }

    timespec_t start_cpu;
    timespec_t end_cpu;
    timespec_t start_wall;
    timespec_t end_wall;

    double control_wall_time;
    double control_cpu_time;
    double student_wall_time;
    double student_cpu_time;

    matrix_t matrix;
    long results[RESULTS_LEN];
    long sum;

    printf("Setting up random matrix...\n");
    if (is_even_size) {
        set_up_random_matrix(&matrix, NUM_ROWS, NUM_COLS, RAND_SEED);
    } else {
        set_up_random_matrix(&matrix, NUM_ROWS_ODD, NUM_COLS_ODD, RAND_SEED);
    }

    // -------------------------- Control Get Every Fifth  ---------------------
    initialize_results(results);

    clock_gettime(CLOCK_REALTIME, &start_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);

    get_every_fifth(&matrix, results);

    clock_gettime(CLOCK_REALTIME, &end_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    control_cpu_time = get_elapsed_time_sec(&start_cpu, &end_cpu);
    control_wall_time = get_elapsed_time_sec(&start_wall, &end_wall);

    printf("Contents of results array: {%ld, %ld, %ld, %ld, %ld}\n", results[0],
           results[1], results[2], results[3], results[4]);
    printf("CPU time for control implementation: %.3f sec.\n", control_cpu_time);
    printf("Wall time for control implementation: %.3f sec.\n\n", control_wall_time);

    // ------------------------- Student Get Every Fifth  ----------------------
    initialize_results(results);

    clock_gettime(CLOCK_REALTIME, &start_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);

    get_every_fifth_student(&matrix, results);

    clock_gettime(CLOCK_REALTIME, &end_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    student_cpu_time = get_elapsed_time_sec(&start_cpu, &end_cpu);
    student_wall_time = get_elapsed_time_sec(&start_wall, &end_wall);

    printf("Contents of results array: {%ld, %ld, %ld, %ld, %ld}\n", results[0],
            results[1], results[2], results[3], results[4]);
    printf("CPU time for student implementation: %.3f sec.\n", student_cpu_time);
    printf("Wall time for student implementation: %.3f sec.\n\n", student_wall_time);
    printf("Ratio of control speed to student speed (get_every_fifth): %f\n\n",
            control_cpu_time / student_cpu_time);

    // ------------------------- Control Get Every -----------------------------
    sum = 0;

    clock_gettime(CLOCK_REALTIME, &start_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);

    sum = get_every(&matrix);

    clock_gettime(CLOCK_REALTIME, &end_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    control_cpu_time = get_elapsed_time_sec(&start_cpu, &end_cpu);
    control_wall_time = get_elapsed_time_sec(&start_wall, &end_wall);

    printf("Sum of all elements in the array: %ld\n", sum);
    printf("CPU time for control implementation: %.3f sec.\n", control_cpu_time);
    printf("Wall time for control implementation: %.3f sec.\n\n", control_wall_time);

    // ------------------------- Student Get Every -----------------------------

    sum = 0;

    clock_gettime(CLOCK_REALTIME, &start_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);

    sum = get_every_student(&matrix);

    clock_gettime(CLOCK_REALTIME, &end_wall);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    student_cpu_time = get_elapsed_time_sec(&start_cpu, &end_cpu);
    student_wall_time = get_elapsed_time_sec(&start_wall, &end_wall);

    printf("Sum of all elements in the array: %ld\n", sum);
    printf("CPU time for student implementation: %.3f sec.\n", student_cpu_time);
    printf("Wall time for student implementation: %.3f sec.\n\n", student_wall_time);

    printf("Ratio of control speed to student speed (get_every): %f\n\n",
            control_cpu_time / student_cpu_time);

    // ------------------------- Clean Up Memory -------------------------------
    free_matrix(&matrix);
}
