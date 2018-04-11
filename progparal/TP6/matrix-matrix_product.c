#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int getSuccesseur(int rank, int numprocs);
int getPredecesseur(int rank, int numprocs);
void afficherTableau(int* tab, int length);

void main(int argc, char* argv[]){
    int rank, numprocs;
    const int N = 500;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Matrix allocation
    int ** matrix = (int **) malloc(sizeof(int*) * N);
    for(int i = 0; i < N; i++) {
        matrix[i] = malloc(sizeof(int) * N);
    }

    // Matrix definition
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            matrix[i][j] = i + j;
        }
    }

    for(int i = 0; i < numprocs; i++) {
        if(i == rank) {
            buf[i] = rank;
        } else {
            buf[i] = 0;
        }
    }
    
    for(int i = 0; i < numprocs; i++) {
        MPI_Bcast(&buf[i], 1, MPI_INT, i, MPI_COMM_WORLD);
    }

    printf("Tableau du processus %d :\n", rank);
    afficherTableau(buf, numprocs);

    MPI_Finalize();

}

int getSuccesseur(int rank, int numprocs){
    return (rank + 1) % numprocs;
}

int getPredecesseur(int rank, int numprocs){
    return (rank - 1 + numprocs) % numprocs;
}

void afficherTableau(int* tab, int length){

    for(int i = 0; i < length; i++){
        printf("data[%d] = %d\n", i, tab[i]);
    }
}