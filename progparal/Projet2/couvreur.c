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
void setMatrixElement(struct Matrix*, int, int, int);
struct Matrix* createMatrix(int, int);
void matrixProduct(struct Matrix*, struct Matrix*, struct Matrix*);

/* MPI */
int getSuccessor(int rank, int numprocs);
int getPredecessor(int rank, int numprocs);

/* Utils */
void printArray(int* tab, int length);
void printMatrix(struct Matrix*);

void main(int argc, char* argv[]){
    int rank, numprocs;
    const int N = 3;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct Matrix* m1 = createMatrix(N, N);
    m1->matrix[0] = 1;
    m1->matrix[1] = 2;
    m1->matrix[2] = 3;
    m1->matrix[3] = 4;
    m1->matrix[4] = 5;
    m1->matrix[5] = 6;
    m1->matrix[6] = 7;
    m1->matrix[7] = 8;
    m1->matrix[8] = 9;


    struct Matrix* m2 = createMatrix(N, N);
    m2->matrix[0] = 1;
    m2->matrix[1] = 2;
    m2->matrix[2] = 3;
    m2->matrix[3] = 4;
    m2->matrix[4] = 5;
    m2->matrix[5] = 6;
    m2->matrix[6] = 7;
    m2->matrix[7] = 8;
    m2->matrix[8] = 9;

    struct Matrix* m3 = createMatrix(N, N);

    matrixProduct(m1, m2, m3);

    printMatrix(m3);

    // TODO: init matrix with the file  and scatter it o the other workers

    MPI_Finalize();

}

struct Matrix* createMatrix(int line, int col){
    struct Matrix* matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->line = line;
    matrix->matrix = (int*) malloc(sizeof(int) * col * line);

    for(int i = 0; i < col * line; i++) {
        matrix->matrix[i] = 0;
    }

    return matrix;
}

/*
 * Matrix struct has a 1D array as a matrix.
 * To get mat[line][col] we need to access mat[(line * col) + offset]
 * 
 * Ex: elem matrix[4][3] of matrix[5][5] is (4 * 5) + 3 which is the 23rd element
*/
int getMatrixElement(struct Matrix* mat, int line, int col){
    return mat->matrix[(line * mat->col) + col];
}

void setMatrixElement(struct Matrix* mat, int line, int col, int val){
    mat->matrix[(line* mat->col) + col] = val;
}

void matrixProduct(struct Matrix * A, struct Matrix * B, struct Matrix * C){

    for (int i = 0; i < A->line; i ++){
        for (int j = 0; j < A->col; j++){
            for (int k = 0 ; k < B->line; k++){
                int newVal = getMatrixElement(C, i, j) + getMatrixElement(A, i, k) * getMatrixElement(B, k, j);
                setMatrixElement(C, i, j, newVal);
            }
        }
    }
}

int getSuccessor(int rank, int numprocs){
    return (rank + 1) % numprocs;
}

int getPredecessor(int rank, int numprocs){
    return (rank - 1 + numprocs) % numprocs;
}

void printArray(int* tab, int length){

    for(int i = 0; i < length; i++){
        printf("data[%d] = %d\n", i, tab[i]);
    }
}

void printMatrix(struct Matrix* matrix){
    for(int i = 0; i < matrix->line; i++) {
        for(int j = 0; j < matrix->col; j++) {
            printf("%d\t", getMatrixElement(matrix, i, j));
        }
        printf("\n");
    }
}