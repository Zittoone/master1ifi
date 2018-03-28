#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int getSuccesseur(int rank, int numprocs);
int getPredecesseur(int rank, int numprocs);

void main(int argc, char* argv[]){
    int numprocs, rank, p;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    p = 0;
    int * rangPredecesseur = malloc(sizeof(int));
    MPI_Status status;

    /* Je suis l'émetteur
     * On suppose que le premier est le processus 0, 
     * on pourra par la suite le mettre en argument (variable p)
     */
    if(rank == p) {
        /* L'émetteur envoie l'information en premier, tandis que tous les autres reoivent d'abord.
         * Puis il recoit le dernier message
         */
        MPI_Send(&rank, sizeof(int), MPI_INT, getSuccesseur(rank, numprocs), 0, MPI_COMM_WORLD);
        MPI_Recv(rangPredecesseur, sizeof(int), MPI_INT, getPredecesseur(rank, numprocs), 0, MPI_COMM_WORLD, &status);

    } else {

        MPI_Recv(rangPredecesseur, sizeof(int), MPI_INT, getPredecesseur(rank, numprocs), 0, MPI_COMM_WORLD, &status);
        MPI_Send(&rank, sizeof(int), MPI_INT, getSuccesseur(rank, numprocs), 0, MPI_COMM_WORLD);

    }

    printf("Je suis le proc %d, mon prédécesseur est le %d.\n", rank, *rangPredecesseur);

    MPI_Finalize();

}

int getSuccesseur(int rank, int numprocs){
    return (rank + 1) % numprocs;
}

int getPredecesseur(int rank, int numprocs){
    return (rank - 1 + numprocs) % numprocs;
}