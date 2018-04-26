#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Matrix */
struct Matrix
{
    int col;
    int row;
    int *matrix;
};

int getMatrixElement(struct Matrix *, int, int);
void setMatrixElement(struct Matrix *, int, int, int);
struct Matrix *allocateMatrix(int row, int col);
struct Matrix *allocateMatrixWithArray(int row, int col, int* m);
struct Matrix *allocateMatrixFromColumns(int row, int col, int* m);
struct Matrix *generateMatrix(char *);
void matrixProduct(struct Matrix *, struct Matrix *, struct Matrix *);
void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, int col_start, int col_end, int rank);
struct Matrix* transposeMatrix(struct Matrix *A);

/* MPI */
int getSuccessor(int rank, int numprocs);
int getPredecessor(int rank, int numprocs);

/* Utils */
void printArray(int *tab, int length);
void printMatrix(struct Matrix *);
char *readFileToBuffer(char *);
int getLines(char* in, char** out);

void main(int argc, char *argv[])
{
    int rank, numprocs, root;

    int N;
    root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct Matrix *m1;
    struct Matrix *m2;
    struct Matrix *m3;

    /*
     * READING THE FILE AND SENDING THE SIZE TO ALL P
     */
    if (rank == root)
    {

        char *fileA = readFileToBuffer(argv[1]);
        m1 = generateMatrix(fileA);
        free(fileA);

        char *fileB = readFileToBuffer(argv[2]);
        m2 = generateMatrix(fileB);
        free(fileB);

        N = m1->row;
        
        m3 = allocateMatrix(N, N);

        // matrixProduct(m1, m2, m3);

        // printMatrix(m3);
    }

    MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Now we have N we can compute the slices
    int count = N*N/numprocs;

    // Of matrix A
    int *rows_received = malloc(sizeof(int) * count);
    // Of matrix B
    int *cols_received = malloc(sizeof(int) * count);

    if(rank != root) {
        m1 = allocateMatrix(N, N);
        m2 = allocateMatrix(N, N);
        m3 = allocateMatrix(N, N);
    }

    // 1. Scatter Matrix A by lines to all processes
    MPI_Scatter(m1->matrix, count, MPI_INT, rows_received, count, MPI_INT, root, MPI_COMM_WORLD);

    // 2. Transpose matrix B to scatter it column by column if root
    if(rank == root) {
        m2 = transposeMatrix(m2);
    }

    // 3. Scatter matrix B
    MPI_Scatter(m2->matrix, count, MPI_INT, cols_received, count, MPI_INT, root, MPI_COMM_WORLD);

    // 4. Create pseudo matrices
    struct Matrix* A = allocateMatrixWithArray(count / N, N, rows_received);
    struct Matrix* B = allocateMatrixFromColumns(count / N, N, cols_received);
    struct Matrix* C = allocateMatrix(count / N, N);

    int nb_col = count / N;
    int col_start = nb_col * rank; // included
    int col_end = nb_col * (rank + 1); // excluded

    printf("[%d] partial product on columns [%d, %d[ on matrix row %d, col %d.\n",rank, col_start, col_end, A->row, A->col);
    partialMatrixProduct(A, B, C, col_start, col_end, rank);

    

    // Ring structure
    for(int i = 0; i < numprocs; i++) {
        
        if(rank == root) {
            printf("Processing turn %d ...\n", i);
            
            MPI_Send(cols_received, count, MPI_INT, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);
            printf("[%d] Sent data to process %d ...\n", rank, getSuccessor(rank, numprocs));

            MPI_Recv(cols_received, count, MPI_INT, getPredecessor(rank, numprocs), 0, MPI_COMM_WORLD, NULL);
            printf("[%d] Received data from process %d ...\n", rank, getPredecessor(rank, numprocs));

            // Do stuff ...
            B->matrix = cols_received;
            col_start = nb_col * (rank + (i + 1));
            col_end = nb_col * (rank + (i + 1));

            // printf("[%d] partial product on columns [%d, %d[ on matrix row %d, col %d.\n",rank, col_start, col_end, A->row, A->col);
            // partialMatrixProduct(A, B, C, col_start, col_end, rank);
            

        } else {


            MPI_Recv(cols_received, count, MPI_INT, getPredecessor(rank, numprocs), 0, MPI_COMM_WORLD, NULL);
            printf("[%d] Received data from process %d ...\n", rank, getPredecessor(rank, numprocs));

            // Do stuff ...
            B->matrix = cols_received;/*
            col_start = nb_col * (rank + (i + 1));
            col_end = nb_col * (rank + (i + 1));
            printf("[%d] partial product on columns [%d, %d[ on matrix row %d, col %d.\n",rank, col_start, col_end, A->row, A->col);*/
            //partialMatrixProduct(A, B, C, col_start, col_end);

            MPI_Send(cols_received, count, MPI_INT, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);
            printf("[%d] Sent data to process %d ...\n", rank, getSuccessor(rank, numprocs));
        }
    }

    if(rank == root) {
        printf("All processus have finished their work, now i gather !\n");
    }
    

    MPI_Gather(C->matrix, count, MPI_INT, m3->matrix, count, MPI_INT, root, MPI_COMM_WORLD);

    if(rank == root) {
        printf("Root gathered matrix is : \n");
        printMatrix(m3);
    }
    
    MPI_Finalize();
}

struct Matrix *allocateMatrix(int row, int col)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->matrix = (int *)malloc(sizeof(int) * col * row);

    for (int i = 0; i < col * row; i++)
    {
        matrix->matrix[i] = 0;
    }

    return matrix;
}

struct Matrix *allocateMatrixWithArray(int row, int col, int* m)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->matrix = m;

    return matrix;
}

// Meaning the array is by columns instead of rows
struct Matrix *allocateMatrixFromColumns(int row, int col, int* m)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->row = row;

    matrix->matrix = m;

    matrix = transposeMatrix(matrix);

    return matrix;
}

struct Matrix *generateMatrix(char *buffer)
{
    struct Matrix* matrix;

    int count = 0;
    char **lines = (char**) malloc(sizeof(char*) * 64);

    int nLines = getLines(buffer, lines);
    
    matrix = allocateMatrix(nLines, nLines);
    

    for(int i = 0; i < nLines; i++) {
        char *token = strtok(lines[i], " ");
        
        int j = 0;

        while(token != NULL) {
            
            int value = atoi(token);

            setMatrixElement(matrix, i, j, value);
            j++;

            token = strtok(NULL, " ");
        }
    }

    return matrix;
}

/*
 * Matrix struct has a 1D array as a matrix.
 * To get mat[row][col] we need to access mat[(row * col) + offset]
 * 
 * Ex: elem matrix[4][3] of matrix[5][5] is (4 * 5) + 3 which is the 23rd element
*/
int getMatrixElement(struct Matrix *mat, int row, int col)
{
    return mat->matrix[(row * mat->col) + col];
}

void setMatrixElement(struct Matrix *mat, int row, int col, int val)
{
    mat->matrix[(row * mat->col) + col] = val;
}

/*
 * To calculate this you need
 * A.col 
 * 

*/
void matrixProduct(struct Matrix *A, struct Matrix *B, struct Matrix *C)
{

    for (int i = 0; i < A->row; i++)
    {
        for (int j = 0; j < A->col; j++)
        {
            for (int k = 0; k < B->row; k++)
            {
                int newVal = getMatrixElement(C, i, j) + getMatrixElement(A, i, k) * getMatrixElement(B, k, j);
                setMatrixElement(C, i, j, newVal);
            }
        }
    }
}

void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, int col_start, int col_end, int rank) {

    for(int i = 0; i < A->row; i++)
    {
        for(int j = col_start; j < col_end; j++)
        {
            for (int k = 0; k < B_partial->row; k++)
            {

                int newVal = getMatrixElement(C, i, j) + getMatrixElement(A, i, k) * getMatrixElement(B_partial, k, j - col_start);
                // printf("[%d] C[%d][%d] = C[%d][%d] + A[%d][%d] * B[%d][%d] => %d + %d * %d = %d\n", rank, i, j, i, j, i, k, k, j, getMatrixElement(C, i, j), getMatrixElement(A, i, k), getMatrixElement(B_partial, k, j), newVal);
                setMatrixElement(C, i, j, newVal);
            }
        }
    }
}

struct Matrix* transposeMatrix(struct Matrix *A) {

    struct Matrix* B = allocateMatrix(A->col, A->row);

    for(int i = 0; i < A->row; i++) {
        for(int j = 0; j < A->col; j++) {
            setMatrixElement(B, j, i, getMatrixElement(A, i, j));
        }
    }

    return B;
}

int getSuccessor(int rank, int numprocs)
{
    return (rank + 1) % numprocs;
}

int getPredecessor(int rank, int numprocs)
{
    return (rank - 1 + numprocs) % numprocs;
}

void printArray(int *tab, int length)
{

    for (int i = 0; i < length; i++)
    {
        printf("data[%d] = %d\n", i, tab[i]);
    }
}

void printMatrix(struct Matrix *matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->col; j++)
        {
            printf("%d\t", getMatrixElement(matrix, i, j));
        }
        printf("\n");
    }
}

char *readFileToBuffer(char *fileName)
{
    FILE *pFile;
    long lSize;
    char *buffer;
    size_t result;

    pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        fputs("File error", stderr);
        exit(1);
    }

    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    buffer = (char *)malloc(sizeof(char) * lSize);
    if (buffer == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        exit(3);
    }

    fclose(pFile);
    return buffer;
}

/*
 * Split a buffer into lines and returns the number of lines
 * 
*/
int getLines(char* in, char** out) {
    int nbLines = 0;
    int size = 10;
    
    char *token = strtok(in, "\n");
    while (token != NULL)
    {
        
        out[nbLines] = token;
        
        nbLines++;

        /* TODO: realloc the pointer
        if(nbLines >= size) {
            size += 10;
            out = (char**) realloc(out, sizeof(char*) * size);
        }
        */
        
        token = strtok(NULL, "\n");
    }
    
    return nbLines;
}