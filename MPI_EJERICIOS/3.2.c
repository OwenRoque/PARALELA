#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

double square_dist(double x, double y) {
    return x * x + y * y;
}

int rand_toss_gen(long long int num_tosses, int rank) {
    int number_in_circle = 0;
    double x, y, distance_squared;
    srand((unsigned)time(NULL));
    for (long long int toss = 0; toss < num_tosses; toss++) {
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        distance_squared = square_dist(x, y);
        // printf("%lf\n", distance_squared)
        if (distance_squared <= 1) {
            number_in_circle++;
        }
    }
    // printf(" Rank %d has %lld within circles \n", rank,number_in_circle);
    return number_in_circle;
}

double estimate_pi(long long int num_tosses, long long int global_toss_sum, int size) {
    double pi = 4 * (global_toss_sum / num_tosses);
    return (pi / size);
}

int main(int argc, char* argv[]) {
    int rank, size;
    long long int num_tosses, number_in_circle = 0, global_toss_sum;
    double pi;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        // Leer nro de intentos desde proceso 0
        printf("Enter the total number of tosses: ");
        scanf("%lld", &num_tosses);
    }

    // Broadcast num_tosses a todos los demás procesos
    MPI_Bcast(&num_tosses, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    // Find number of tosses in the circle generated randomly 
    number_in_circle = rand_toss_gen(num_tosses, rank);
    printf("Rank %d has %lld tosses in the circle \n",rank, number_in_circle);

    // Reduce to find global sum 
    MPI_Reduce(&number_in_circle, &global_toss_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result from process 0
    if (rank == 0) {
        printf(" Global sum of tosses: %lld \n", global_toss_sum);
        printf(" Number of tasks %d \n", size);
        pi = estimate_pi(num_tosses, global_toss_sum, size);
        printf(" Pi value is %lf \n ", pi);
    }

    MPI_Finalize();
    return 0;
}