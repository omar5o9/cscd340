
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define MAX_THREADS 8

int counter = 0;

void increment_counter() {
    counter++;
}

void parallel_increment(int num_threads, int threshold) {
    #pragma omp parallel num_threads(num_threads)
    {
        int i;
        for (i = 0; i < threshold; i++) {
            increment_counter();
        }
    }
}

void approximate_increment(int threshold) {
    int i;
    for (i = 0; i < threshold; i++) {
        increment_counter();
    }
}

int main() {
    int num_threads, threshold, i;
    double start_time, end_time, elapsed_time;
    struct timeval t1, t2;

    printf("Enter the number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &num_threads);

    printf("Enter the threshold value: ");
    scanf("%d", &threshold);

    gettimeofday(&t1, NULL);

    if (num_threads == 1) {
        approximate_increment(threshold);
    } else {
        parallel_increment(num_threads, threshold);
    }

    gettimeofday(&t2, NULL);
    elapsed_time = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0;

    printf("Counter value: %d\n", counter);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
