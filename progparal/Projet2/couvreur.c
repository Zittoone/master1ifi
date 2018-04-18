#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* Matrix */
struct Matrix {
    int col;
    int line;
    int* matrix;
};

int getMatrixElement(struct Matrix*, int, int);
struct Matrix* createMatrix(int, int);

/* MPI */
int getSuccesseur(int rank, int numprocs);
int getPredecesseur(int rank, int numprocs);

/* Utils */
void afficherTableau(int* tab, int length);

void main(int argc, char* argv[]){
    int rank, numprocs;
    const int N = 500;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct Matrix* matrix = createMatrix(N, N);

    // TODO: init matrix with the file  and scatter it o the other workers

    MPI_Finalize();

}

struct Matrix* createMatrix(int line, int col){
    struct Matrix* matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->line = line;
    matrix->matrix = (int*) malloc(sizeof(int) * col * line);

    return matrix;
}

/*
 * Matrix struct has a 1D array as a matrix.
 * To get mat[line][col] we need to access mat[(line * col) + offset]
 * 
 * Ex: elem matrix[4][3] of matrix[5][5] is (4 * 5) + 3 which is the 23rd element
*/
int getMatrixElement(struct Matrix* mat, int line, int col){
    return mat->matrix[(line * mat->col) + line];
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