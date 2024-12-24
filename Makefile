CC = gcc
MPICC = mpicc
CFLAGS = -Wall -O3 -march=native -I/usr/include/openmpi-x86_64
LDFLAGS = -lm

all: serial mpi pthread openmp

serial: src/serial_pi.c
	$(CC) $(CFLAGS) -o build/serial_pi src/serial_pi.c $(LDFLAGS)

mpi: src/mpi_pi.c
	$(MPICC) $(CFLAGS) -o build/mpi_pi src/mpi_pi.c $(LDFLAGS)

pthread: src/pthread_pi.c
	$(CC) $(CFLAGS) -o build/pthread_pi src/pthread_pi.c -pthread $(LDFLAGS)

openmp: src/openmp_pi.c
	$(CC) $(CFLAGS) -fopenmp -o build/openmp_pi src/openmp_pi.c $(LDFLAGS)

clean:
	rm -f build/*

.PHONY: all clean serial mpi pthread openmp 