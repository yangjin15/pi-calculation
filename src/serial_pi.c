#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

double calculate_pi_serial(long n) {
    double sum = 0.0;
    double dx = 1.0 / n;
    
    for(long i = 0; i < n; i++) {
        double x = i * dx;
        sum += 4.0 / (1.0 + x * x);
    }
    
    return sum * dx;
}

int main(int argc, char *argv[]) {
    long n_values[] = {1000, 10000, 100000, 1000000};
    int n_sizes = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("Serial PI Calculation:\n");
    printf("N\tPI Value\tTime (seconds)\n");
    
    for(int i = 0; i < n_sizes; i++) {
        double start_time = get_time();
        double pi = calculate_pi_serial(n_values[i]);
        double end_time = get_time();
        
        printf("%ld\t%.6f\t%.6f\n", n_values[i], pi, end_time - start_time);
    }
    
    return 0;
} 