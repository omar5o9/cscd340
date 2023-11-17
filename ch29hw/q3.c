
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 64

int thread_count;
long long n;
double threshold;
int counter = 0;
pthread_mutex_t mutex;

void* Thread_sum(void* rank);

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;
    struct timeval start, end;
    double elapsed_time;

    thread_count = strtol(argv[1], NULL, 10);
    n = strtoll(argv[2], NULL, 10);
    threshold = strtod(argv[3], NULL);

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    gettimeofday(&start, NULL);
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }
    gettimeofday(&end, NULL);

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;

    printf("With n = %lld terms,\n", n);
    printf("    Our estimate of pi = %f\n", 4.0 * counter / ((double) n));
    printf("    Time elapsed = %f milliseconds\n", elapsed_time);
    printf("    Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);
    free(thread_handles);
    return 0;
}

void* Thread_sum(void* rank) {
    long my_rank = (long) rank;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    int my_count = 0;
    double factor;
    if (my_first_i % 2 == 0) {
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        if (factor * 1.0 / (2 * i + 1) > threshold) {
            my_count++;
        }
    }

    pthread_mutex_lock(&mutex);
    counter += my_count;
    pthread_mutex_unlock(&mutex);

    return NULL;
}
