
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

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
    int val;
    pthread_mutex_lock(&c->lock);
    val = c->counter;
    pthread_mutex_unlock(&c->lock);
    return val;
}

void approx_counter_destroy(approx_counter_t *c) {
    pthread_mutex_destroy(&c->lock);
}

void *thread_func(void *arg) {
    approx_counter_t *c = (approx_counter_t *) arg;
    int i;
    while (approx_counter_get(c) < c->counter) {
        approx_counter_increment(c);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_threads, i, threshold;
    pthread_t *threads;
    approx_counter_t counter;
    struct timeval start_time, end_time;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num_threads> <threshold> <counter>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    num_threads = atoi(argv[1]);
    threshold = atoi(argv[2]);
    counter.counter = atoi(argv[3]);
    threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));

    approx_counter_init(&counter);

    gettimeofday(&start_time, NULL);

    for (i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_func, &counter);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    printf("Counter value: %d\n", approx_counter_get(&counter));
    printf("Elapsed time: %ld microseconds\n", ((end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec)));

    approx_counter_destroy(&counter);

    free(threads);

    return 0;
}
