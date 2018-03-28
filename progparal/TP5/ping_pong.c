#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        int data = 4;
        MPI_Send(&data, sizeof(int), MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        int* data = malloc(sizeof(int));
        MPI_Status status;
        MPI_Recv(data, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Received : %d !!\n", *data);
    }

    MPI_Finalize();

}