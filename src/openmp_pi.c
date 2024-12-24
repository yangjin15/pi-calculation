#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4

double calculate_pi_openmp(long n) {
    double sum = 0.0;
    double dx = 1.0 / n;
    
    omp_set_num_threads(NUM_THREADS);
    
    #pragma omp parallel reduction(+:sum)
    {
        #pragma omp for
        for(long i = 0; i < n; i++) {
            double x = i * dx;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    
    return sum * dx;
}

int main(int argc, char *argv[]) {
    long n_values[] = {1000, 10000, 100000, 1000000};
    int n_sizes = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("OpenMP PI Calculation with %d threads:\n", NUM_THREADS);
    printf("N\tPI Value\tTime (seconds)\n");
    
    for(int i = 0; i < n_sizes; i++) {
        double start_time = omp_get_wtime();
        double pi = calculate_pi_openmp(n_values[i]);
        double end_time = omp_get_wtime();
        
        printf("%ld\t%.6f\t%.6f\n", n_values[i], pi, end_time - start_time);
    }
    
    return 0;
} 