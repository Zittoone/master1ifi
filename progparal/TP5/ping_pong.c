#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        // Maître
        int data = 4;
        for(int i = 1; i < numprocs; i++){
            MPI_Send(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
    } else {
        int* data = malloc(sizeof(int));
        MPI_Status status;
        MPI_Recv(data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Proc %d deceived : %d !!\n", rank, *data);
    }

    MPI_Finalize();

}