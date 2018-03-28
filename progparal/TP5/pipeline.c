#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
    int numprocs, rank, p;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    p = 0;

    /* Je suis le premier
     * On suppose que le premier est le processus 0, 
     * on pourra par la suite le mettre en argument (variable p)
     */
    if(rank == p) { 
        int data = 4;
        MPI_Send(&data, sizeof(int), MPI_INT, (rank + 1) % numprocs, 0, MPI_COMM_WORLD);
        printf("Proc %d sent initial data to %d\n", p, (rank + 1) % numprocs);
    } 
    /*  Je suis le dernier
     *
     * 
     */
    else if(rank == ((p - 1 + numprocs) % numprocs)) { 
        int* data = malloc(sizeof(int));
        MPI_Status status;
        MPI_Recv(data, sizeof(int), MPI_INT, (rank - 1) % numprocs, 0, MPI_COMM_WORLD, &status);
        printf("Proc %d received : %d (final state)!!\n", rank, *data);
    }
    /*  Cas général
     *
     * 
     */
    else {
        int* data = malloc(sizeof(int));
        MPI_Status status;

        MPI_Recv(data, sizeof(int), MPI_INT, (rank - 1) % numprocs, 0, MPI_COMM_WORLD, &status);
        MPI_Send(data, sizeof(int), MPI_INT, (rank + 1) % numprocs, 0, MPI_COMM_WORLD);
        printf("Proc %d received : %d !!\n", rank, *data);
    }

    MPI_Finalize();

}