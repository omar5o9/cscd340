
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ARRAY_SIZE 1000000

int array[ARRAY_SIZE];
int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct thread_args {
    int threshold;
};

void *count_elements(void *arg) {
    struct thread_args *args = (struct thread_args *) arg;
    int local_count = 0;

    for (int i = 0; i < ARRAY_SIZE / (int) sizeof(array) / (int) sizeof(int); i++) {
        if (array[i] > args->threshold) {
            local_count++;
        }
    }

    pthread_mutex_lock(&mutex);
    count += local_count;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    int num_threads, threshold;
    pthread_t threads[num_threads];
    struct thread_args args;
    struct timeval start, end;
    double elapsed_time;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    printf("Enter the threshold value: ");
    scanf("%d", &threshold);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }

    args.threshold = threshold;

    gettimeofday(&start, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, count_elements, (void *) &args);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);

    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total count: %d\n", count);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
