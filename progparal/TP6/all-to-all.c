#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


void afficherTableau(int* tab, int length){

    for(int i = 0; i < length; i++){
        printf("data[%d] = %d\n", i, tab[i]);
    }
}

void main(int argc, char* argv[]){
    int rank, numprocs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int * buf = malloc(sizeof(int) * numprocs);

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