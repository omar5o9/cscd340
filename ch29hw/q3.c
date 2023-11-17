
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ARRAY_SIZE 1000000

int counter = 0;
int *array;

void *count_threshold(void *arg) {
    int thread_num = *(int *)arg;
    int start = thread_num * (ARRAY_SIZE / 4);
    int end = start + (ARRAY_SIZE / 4);
    int count = 0;

    for (int i = start; i < end; i++) {
        if (array[i] >= thread_num) {
            count++;
        }
    }

    counter += count;

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    array = malloc(sizeof(int) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }

    pthread_t threads[4];
    int thread_nums[4] = {0, 1, 2, 3};

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, count_threshold, &thread_nums[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    printf("Counter: %d\n", counter);
    printf("Time taken: %ld microseconds\n", ((end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec)));

    free(array);

    return 0;
}
