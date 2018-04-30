#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Matrix */
struct Matrix
{
    int col;
    int row;
    long *matrix;
};

long getMatrixElement(struct Matrix *matrix, int row, int col);
void setMatrixElement(struct Matrix *matrix, int row, int col, long value);

struct Matrix *allocateMatrix(int row, int col);
struct Matrix *allocateMatrixWithArray(int row, int col, long *array);
struct Matrix *allocateMatrixFromColumns(int row, int col, long *columns);
struct Matrix *transposeMatrix(struct Matrix *matrix);
struct Matrix *generateMatrix(char *buffer);

void matrixProduct(struct Matrix *, struct Matrix *, struct Matrix *);
void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, int col_start, int col_end);

/* MPI */
int getSuccessor(int rank, int numprocs);
int getPredecessor(int rank, int numprocs);
int getColStart(int rank, int numprocs, int nb_col, int iteration);

/* Utils */
void printMatrix(struct Matrix *);
char *readFileToBuffer(char *);
int getLines(char *in, char ***out);

int main(int argc, char *argv[])
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

        if (N % numprocs != 0)
        {
            printf("Warning! N is not multiple of P (N=%d, P=%d)!\n", N, numprocs);
        }

        m3 = allocateMatrix(N, N);
    }

    if (numprocs == 1)
    {
        matrixProduct(m1, m2, m3);
        printMatrix(m3);
        MPI_Finalize();
        exit(EXIT_SUCCESS);
    }

    MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Now we have N we can compute the slices
    long count = N * N / numprocs;

    // Of matrix A
    long *rows_received = malloc(sizeof(long) * count);
    // Of matrix B
    long *cols_received = malloc(sizeof(long) * count);

    if (rank != root)
    {
        m1 = allocateMatrix(N, N);
        m2 = allocateMatrix(N, N);
        m3 = allocateMatrix(N, N);
    }

    // 1. Scatter Matrix A by lines to all processes
    MPI_Scatter(m1->matrix, count, MPI_LONG, rows_received, count, MPI_LONG, root, MPI_COMM_WORLD);

    // 2. Transpose matrix B to scatter it column by column if root
    if (rank == root)
    {
        m2 = transposeMatrix(m2);
    }

    // 3. Scatter matrix B
    MPI_Scatter(m2->matrix, count, MPI_LONG, cols_received, count, MPI_LONG, root, MPI_COMM_WORLD);

    // 4. Create pseudo matrices
    struct Matrix *A = allocateMatrixWithArray(count / N, N, rows_received);
    struct Matrix *B = allocateMatrixFromColumns(count / N, N, cols_received);
    struct Matrix *C = allocateMatrix(count / N, N);

    int nb_col = count / N;
    int col_start = getColStart(rank, numprocs, nb_col, 0); // included
    int col_end = col_start + nb_col;                       // excluded

    partialMatrixProduct(A, B, C, col_start, col_end);

    // Ring structure
    for (int i = 1; i < numprocs; i++)
    {

        if (rank == root)
        {

            // Send our columns
            MPI_Send(B->matrix, count, MPI_LONG, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);

            // Receive the new columns to ompute into B
            MPI_Recv(B->matrix, count, MPI_LONG, getPredecessor(rank, numprocs), 0, MPI_COMM_WORLD, NULL);

            // Recalibrate columns
            col_start = getColStart(rank, numprocs, nb_col, i);
            col_end = col_start + nb_col;

            // Compute
            partialMatrixProduct(A, B, C, col_start, col_end);
        }
        else
        {

            // Copy old columns into buffer
            memcpy(cols_received, B->matrix, sizeof(int) * count);

            // Receive new columns
            MPI_Recv(B->matrix, count, MPI_LONG, getPredecessor(rank, numprocs), 0, MPI_COMM_WORLD, NULL);

            // Recalibrate columns
            col_start = getColStart(rank, numprocs, nb_col, i);
            col_end = col_start + nb_col;

            // Compute
            partialMatrixProduct(A, B, C, col_start, col_end);

            // Send old columns
            MPI_Send(cols_received, count, MPI_LONG, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);
        }
    }

    MPI_Gather(C->matrix, count, MPI_LONG, m3->matrix, count, MPI_LONG, root, MPI_COMM_WORLD);

    if (rank == root)
    {
        printMatrix(m3);
    }

    MPI_Finalize();

    exit(EXIT_SUCCESS);
}

struct Matrix *allocateMatrix(int row, int col)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->matrix = malloc(sizeof(long) * col * row);

    for (int i = 0; i < col * row; i++)
    {
        matrix->matrix[i] = 0;
    }

    return matrix;
}

struct Matrix *allocateMatrixWithArray(int row, int col, long *m)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->matrix = m;

    return matrix;
}

// Meaning the array is by columns instead of rows
struct Matrix *allocateMatrixFromColumns(int row, int col, long *m)
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
    struct Matrix *matrix;

    char **lines;

    int nLines = getLines(buffer, &lines);

    matrix = allocateMatrix(nLines, nLines);

    for (int i = 0; i < nLines; i++)
    {
        char *token = strtok(lines[i], " ");

        int j = 0;

        while (token != NULL)
        {

            long value = atol(token);

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
long getMatrixElement(struct Matrix *mat, int row, int col)
{
    return mat->matrix[(row * mat->col) + col];
}

void setMatrixElement(struct Matrix *mat, int row, int col, long val)
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

void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, int col_start, int col_end)
{

#pragma omp parallel for
    for (int i = 0; i < A->row; i++)
    {
        for (int j = col_start; j < col_end; j++)
        {
            for (int k = 0; k < B_partial->row; k++)
            {
                int newVal = getMatrixElement(C, i, j) + getMatrixElement(A, i, k) * getMatrixElement(B_partial, k, j - col_start);
                setMatrixElement(C, i, j, newVal);
            }
        }
    }
}

struct Matrix *transposeMatrix(struct Matrix *A)
{

    struct Matrix *B = allocateMatrix(A->col, A->row);

    for (int i = 0; i < A->row; i++)
    {
        for (int j = 0; j < A->col; j++)
        {
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

void printMatrix(struct Matrix *matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->col - 1; j++)
        {
            printf("%ld ", getMatrixElement(matrix, i, j));
        }
        printf("%ld\n", getMatrixElement(matrix, i, matrix->col - 1));
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

    buffer = (char *)malloc(sizeof(char) * lSize + 1);
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

    buffer[lSize] = '\0';
    return buffer;
}

/*
 * Split a buffer into lines and returns the number of lines
 * 
*/
int getLines(char *in, char ***out)
{

    int nbLines = 0;
    int size = 16;

    char **tmp = (char **)malloc(sizeof(char *) * size);

    char *token = strtok(in, "\n");
    while (token != NULL)
    {

        tmp[nbLines] = token;
        nbLines++;

        if (nbLines >= size)
        {

            size *= 2;

            tmp = (char **)realloc(tmp, sizeof(char *) * size);
            if (tmp == NULL)
            {
                fputs("Memory error", stderr);
                exit(2);
            }
        }

        token = strtok(NULL, "\n");
    }

    (*out) = tmp;
    return nbLines;
}

int getColStart(int rank, int numprocs, int nb_col, int iteration)
{
    for (int i = 0; i < iteration; i++)
    {
        rank = getPredecessor(rank, numprocs);
    }

    return rank * nb_col;
}