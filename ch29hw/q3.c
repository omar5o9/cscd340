
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define THRESHOLD 1000000

typedef struct {
    int counter;
    pthread_mutex_t lock;
} approx_counter_t;

void approx_counter_init(approx_counter_t *c) {
    c->counter = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void approx_counter_increment(approx_counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->counter++;
    pthread_mutex_unlock(&c->lock);
}

int approx_counter_get(approx_counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int value = c->counter;
    pthread_mutex_unlock(&c->lock);
    return value;
}

void approx_counter_destroy(approx_counter_t *c) {
    pthread_mutex_destroy(&c->lock);
}

void *thread_func(void *arg) {
    approx_counter_t *c = (approx_counter_t *) arg;
    for (int i = 0; i < THRESHOLD; i++) {
        approx_counter_increment(c);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_threads = atoi(argv[1]);

    approx_counter_t counter;
    approx_counter_init(&counter);

    pthread_t threads[num_threads];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_func, &counter);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    int final_value = approx_counter_get(&counter);
    printf("Final value: %d\n", final_value);
    printf("Time taken: %f seconds\n", time_taken);

    approx_counter_destroy(&counter);

    return 0;
}
