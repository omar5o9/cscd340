
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <sys/time.h>

#define MAX_THREADS 1000000

atomic_int counter;

void increment_counter(double threshold, double *elapsed_time) {
    int local_counter = 0;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < 1000000; i++) {
        double r = (double) rand() / RAND_MAX;
        if (r < threshold) {
            local_counter++;
        }
    }
    gettimeofday(&end_time, NULL);
    *elapsed_time += (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    atomic_fetch_add(&counter, local_counter);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num_threads threshold\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int num_threads = atoi(argv[1]);
    double threshold = atof(argv[2]);
    if (num_threads < 1 || num_threads > MAX_THREADS) {
        fprintf(stderr, "Invalid number of threads: %d\n", num_threads);
        exit(EXIT_FAILURE);
    }
    pthread_t threads[num_threads];
    double elapsed_time = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, (void *(*)(void *)) increment_counter, (void *) threshold, &elapsed_time);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Counter value: %d\n", counter);
    //printf("Elapsed time: %f microseconds\n", elapsed_time);
    printf("Time to calculate: %f microseconds\n", elapsed_time - num_threads * 1000000);
    return 0;
}
