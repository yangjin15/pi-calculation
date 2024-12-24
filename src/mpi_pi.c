#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

double calculate_pi_mpi(long n, int rank, int size) {
    double sum = 0.0;
    double dx = 1.0 / n;
    long items_per_proc = n / size;
    long start = rank * items_per_proc;
    long end = (rank == size - 1) ? n : start + items_per_proc;
    
    for(long i = start; i < end; i++) {
        double x = i * dx;
        sum += 4.0 / (1.0 + x * x);
    }
    
    return sum * dx;
}

int main(int argc, char *argv[]) {
    int rank, size;
    long n_values[] = {1000, 10000, 100000, 1000000};
    int n_sizes = sizeof(n_values) / sizeof(n_values[0]);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        printf("MPI PI Calculation with %d processes:\n", size);
        printf("N\tPI Value\tTime (seconds)\n");
    }
    
    for(int i = 0; i < n_sizes; i++) {
        double start_time = MPI_Wtime();
        double local_sum = calculate_pi_mpi(n_values[i], rank, size);
        double global_sum;
        
        MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        
        if(rank == 0) {
            double end_time = MPI_Wtime();
            printf("%ld\t%.6f\t%.6f\n", n_values[i], global_sum, end_time - start_time);
        }
    }
    
    MPI_Finalize();
    return 0;
} 