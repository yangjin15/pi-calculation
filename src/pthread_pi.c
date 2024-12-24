#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 4

typedef struct {
    long start;
    long end;
    long n;
    double result;
} ThreadData;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double global_sum = 0.0;

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

void* calculate_pi_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double local_sum = 0.0;
    double dx = 1.0 / data->n;
    
    for(long i = data->start; i < data->end; i++) {
        double x = i * dx;
        local_sum += 4.0 / (1.0 + x * x);
    }
    
    data->result = local_sum * dx;
    
    pthread_mutex_lock(&mutex);
    global_sum += data->result;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

double calculate_pi_pthread(long n) {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    global_sum = 0.0;
    
    long items_per_thread = n / NUM_THREADS;
    
    for(int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * items_per_thread;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * items_per_thread;
        thread_data[i].n = n;
        thread_data[i].result = 0.0;
        
        pthread_create(&threads[i], NULL, calculate_pi_thread, &thread_data[i]);
    }
    
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return global_sum;
}

int main(int argc, char *argv[]) {
    long n_values[] = {1000, 10000, 100000, 1000000};
    int n_sizes = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("Pthread PI Calculation with %d threads:\n", NUM_THREADS);
    printf("N\tPI Value\tTime (seconds)\n");
    
    for(int i = 0; i < n_sizes; i++) {
        double start_time = get_time();
        double pi = calculate_pi_pthread(n_values[i]);
        double end_time = get_time();
        
        printf("%ld\t%.6f\t%.6f\n", n_values[i], pi, end_time - start_time);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
} 