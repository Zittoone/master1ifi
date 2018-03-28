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
    int * data_received = malloc(sizeof(int));
    MPI_Status status;

    /* Je suis l'émetteur
     * On suppose que le premier est le processus 0, 
     * on pourra par la suite le mettre en argument (variable p)
     */
    if(rank == p) {
        /* L'émetteur envoie l'information en premier, tandis que tous les autres reoivent d'abord.
         * Puis il recoit le dernier message
         */
        int data = 4;
        MPI_Send(&data, sizeof(int), MPI_INT, getSuccesseur(rank, numprocs), 0, MPI_COMM_WORLD);
        MPI_Recv(data_received, sizeof(int), MPI_INT, getPredecesseur(rank, numprocs), 0, MPI_COMM_WORLD, &status);
        printf("Je suis %d et j'ai reçu la valeur %d du processus %d (tour terminé).\n",rank, *data_received, getPredecesseur(rank, numprocs));

    } else {

        MPI_Recv(data_received, sizeof(int), MPI_INT, getPredecesseur(rank, numprocs), 0, MPI_COMM_WORLD, &status);
        MPI_Send(data_received, sizeof(int), MPI_INT, getSuccesseur(rank, numprocs), 0, MPI_COMM_WORLD);
        printf("Je suis %d et j'ai reçu la valeur %d, je la transmets au processus %d.\n",rank, *data_received, getSuccesseur(rank, numprocs));
    }

    MPI_Finalize();

}

int getSuccesseur(int rank, int numprocs){
    return (rank + 1) % numprocs;
}

int getPredecesseur(int rank, int numprocs){
    return (rank - 1 + numprocs) % numprocs;
}