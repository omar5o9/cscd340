
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_INCREMENTS 1000000

int counter = 0;

void increment_counter(int *ptr) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        (*ptr)++;
    }
}

void *thread_function(void *arg) {
    int *ptr = (int *) arg;
    increment_counter(ptr);
    return NULL;
}

int main() {
    int num_threads;
    printf("Enter the number of threads to use: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    int thread_counters[num_threads];

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        thread_counters[i] = 0;
        pthread_create(&threads[i], NULL, thread_function, &thread_counters[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        counter += thread_counters[i];
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Counter value: %d\n", counter);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
