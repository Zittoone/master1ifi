#include <mpi.h>
#include <stdio.h>

void main(int argc, char* argv[]){
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Hello !\n");
    } else if (rank == 1) {
        printf("Bye !!\n");
    }

    MPI_Finalize();

}