
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <sys/time.h>

#define MAX_THREADS 100

atomic_int counter;

void increment_counter(double threshold) {
    double r = (double) rand() / RAND_MAX;
    if (r < threshold) {
        atomic_fetch_add(&counter, 1);
    }
}

int get_counter() {
    return atomic_load(&counter);
}

void *worker(void *arg) {
    int num_iterations = *(int *) arg;
    for (int i = 0; i < num_iterations; i++) {
        increment_counter(0.5);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num_threads num_iterations\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_threads = atoi(argv[1]);
    int num_iterations = atoi(argv[2]);

    if (num_threads < 1 || num_threads > MAX_THREADS) {
        fprintf(stderr, "num_threads must be between 1 and %d\n", MAX_THREADS);
        exit(EXIT_FAILURE);
    }

    pthread_t threads[num_threads];
    int iterations_per_thread = num_iterations / num_threads;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker, &iterations_per_thread);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Counter value: %d\n", get_counter());
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
