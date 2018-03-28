#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int getSuccesseur(int rank, int numprocs);
int getPredecesseur(int rank, int numprocs);

void main(int argc, char* argv[]){
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int taille = atoi(argv[1]);

    int * tab = malloc(sizeof(int) * taille);
    MPI_Status status;

    MPI_Send(tab, taille, MPI_INT, getSuccesseur(rank, numprocs), 0, MPI_COMM_WORLD);
    MPI_Recv(tab, taille, MPI_INT, getPredecesseur(rank, numprocs), 0, MPI_COMM_WORLD, &status);
  
    MPI_Finalize();

}


int getSuccesseur(int rank, int numprocs){
    return (rank + 1) % numprocs;
}

int getPredecesseur(int rank, int numprocs){
    return (rank - 1 + numprocs) % numprocs;
}