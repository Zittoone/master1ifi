#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _NUM_THREADS 4

/* Matrix */
struct Matrix
{
    size_t col;
    size_t row;
    long long *matrix;
};

long long getMatrixElement(struct Matrix *matrix, size_t row, size_t col);
void setMatrixElement(struct Matrix *matrix, size_t row, size_t col, long long value);

struct Matrix *allocateMatrix(size_t row, size_t col, int shouldAlloc);
struct Matrix *allocateMatrixWithArray(size_t row, size_t col, long long *array);
struct Matrix *allocateMatrixFromColumns(size_t row, size_t col, long long *columns);
struct Matrix *transposeMatrix(struct Matrix *matrix);
struct Matrix *generateMatrix(char *buffer);

void matrixProduct(struct Matrix *, struct Matrix *, struct Matrix *);
void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, size_t col_start, size_t col_end, size_t rest);
void nonMultipleMatrixProduct(struct Matrix *, struct Matrix *, struct Matrix *, size_t);

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

    /* set number of threads to spawn */
    omp_set_num_threads(_NUM_THREADS);

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
    }

    if (numprocs == 1)
    {
        m3 = allocateMatrix(N, N, 1);
        matrixProduct(m1, m2, m3);
        printMatrix(m3);
        MPI_Finalize();
        exit(EXIT_SUCCESS);
    }

    MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Now we have N we can compute the slices
    int count = (N * N / numprocs);
    count -= (count % N);
    int rest = N * N % numprocs;

    // N < P
    if (count == 0)
    {
        m3 = allocateMatrix(N, N, 1);
        matrixProduct(m1, m2, m3);
        printMatrix(m3);
        MPI_Finalize();
        exit(EXIT_SUCCESS);
    }

    // Of matrix A
    long long *rows_received = malloc(sizeof(long long) * count);
    // Of matrix B
    long long *cols_received = malloc(sizeof(long long) * count);

    if (rank != root)
    {
        m1 = allocateMatrix(N, N, 0);
        m2 = allocateMatrix(N, N, 0);
    }

    m3 = allocateMatrix(N, N, 1);

    // 1. Scatter Matrix A by lines to all processes
    MPI_Scatter(m1->matrix, count, MPI_LONG_LONG, rows_received, count, MPI_LONG_LONG, root, MPI_COMM_WORLD);
    
    // 2. Transpose matrix B to scatter it column by column if root
    if (rank == root)
    {
        m2 = transposeMatrix(m2);
    }

    // 3. Scatter matrix B
    MPI_Scatter(m2->matrix, count, MPI_LONG_LONG, cols_received, count, MPI_LONG_LONG, root, MPI_COMM_WORLD);

    // 4. Create pseudo matrices
    int nb_col = count / N;
    int rest_nb_col = N % numprocs;
    struct Matrix *A = allocateMatrixWithArray(nb_col, N, rows_received);
    struct Matrix *B = allocateMatrixFromColumns(nb_col, N, cols_received);
    struct Matrix *C = allocateMatrix(nb_col, N, 1);

    int col_start; // included
    int col_end; // excluded


    // Ring structure
    for (int i = 0; i < numprocs; i++)
    {
        col_start = getColStart(rank, numprocs, nb_col, i);
        col_end = col_start + nb_col;

        // 1. Everyone computes
        partialMatrixProduct(A, B, C, col_start, col_end, 0);

        // 2. Root save into buffer old columns and others send their data
        if (rank != root)
        {
            // Send our columns
            MPI_Send(B->matrix, count, MPI_LONG_LONG, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);
        } else {
            memcpy(cols_received, B->matrix, sizeof(long long) * count);
        }

        // 3. Everyone receive
        MPI_Recv(B->matrix, count, MPI_LONG_LONG, getPredecessor(rank, numprocs), 0, MPI_COMM_WORLD, NULL);

        // 4. Root send, unlocking the ring
        if(rank == root)
        {
            // Send old columns
            MPI_Send(cols_received, count, MPI_LONG_LONG, getSuccessor(rank, numprocs), 0, MPI_COMM_WORLD);
        }
    }

    MPI_Gather(C->matrix, count, MPI_LONG_LONG, m3->matrix, count, MPI_LONG_LONG, root, MPI_COMM_WORLD);

    if (rank == root)
    {
        if(rest != 0) {
            m2 = transposeMatrix(m2);
            nonMultipleMatrixProduct(m1, m2, m3, N - rest);
        }
        printMatrix(m3);
    }

    MPI_Finalize();

    exit(EXIT_SUCCESS);
}

struct Matrix *allocateMatrix(size_t row, size_t col, int shouldAlloc)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->matrix = malloc(sizeof(long long) * col * row);

    if(matrix->matrix == NULL)
    {
        fputs("Memory error allocating matrix", stderr);
        exit(EXIT_FAILURE);
    }

    if(shouldAlloc) {
        #pragma omp parallel for
        for (int i = 0; i < col * row; i++)
        {
            matrix->matrix[i] = 0;
        }
    }
    

    return matrix;
}

struct Matrix *allocateMatrixWithArray(size_t row, size_t col, long long *m)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->matrix = m;

    return matrix;
}

// Meaning the array is by columns instead of rows
struct Matrix *allocateMatrixFromColumns(size_t row, size_t col, long long *m)
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

    matrix = allocateMatrix(nLines, nLines, 0);

    for (int i = 0; i < nLines; i++)
    {
        char *token = strtok(lines[i], " ");

        int j = 0;

        while (token != NULL)
        {

            long long value = atol(token); // les opticiens

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
long long getMatrixElement(struct Matrix *mat, size_t row, size_t col)
{
    return mat->matrix[(row * mat->col) + col];
}

void setMatrixElement(struct Matrix *mat, size_t row, size_t col, long long val)
{
    mat->matrix[(row * mat->col) + col] = val;
}

void matrixProduct(struct Matrix *A, struct Matrix *B, struct Matrix *C)
{

    size_t i,j,k;
    long long *a = A->matrix;
    long long *b = B->matrix;
    long long *c = C->matrix;
    #pragma omp parallel shared(a,b,c) private(i,j,k)
    {
        #pragma omp for
        for (i = 0; i < A->row; i++)
        {
            for (j = 0; j < A->col; j++)
            {
                for (k = 0; k < B->row; k++)
                {
                    c[(i * C->col) + j] = c[(i * C->col) + j] + a[(i * A->col) + k] * b[(k * B->col) + j];
                }
            }
    }
    }
}

void partialMatrixProduct(struct Matrix *A, struct Matrix *B_partial, struct Matrix *C, size_t col_start, size_t col_end, size_t rest)
{
    
    size_t i,j,k;
    long long *a = A->matrix;
    long long *b = B_partial->matrix;
    long long *c = C->matrix;
    #pragma omp parallel shared(a,b,c) private(i,j,k)
    {
        #pragma omp for
        for (i = rest; i < A->row; i++)
        {
            for (j = col_start; j < col_end; j++)
            {
                for (k = 0; k < B_partial->row; k++)
                {
                    c[(i * C->col) + j] = c[(i * C->col) + j] + a[(i * A->col) + k] * b[(k * B_partial->col) + j - col_start];
                }
            }
        }
    }
}

void nonMultipleMatrixProduct(struct Matrix *A, struct Matrix *B, struct Matrix *C, size_t rest)
{
    
    size_t i,j,k;
    long long *a = A->matrix;
    long long *b = B->matrix;
    long long *c = C->matrix;
    #pragma omp parallel shared(a,b,c) private(i,j,k)
    {
        #pragma omp for
        for (i = 0; i < A->row; i++)
        {
            for (j = 0; j < A->col; j++)
            {
                for (k = 0; k < B->row; k++)
                {
                    if(i >= rest || j >= rest)
                    c[(i * C->col) + j] = c[(i * C->col) + j] + a[(i * A->col) + k] * b[(k * B->col) + j];
                }
            }
        }
    }
}

struct Matrix *transposeMatrix(struct Matrix *A)
{

    struct Matrix *B = allocateMatrix(A->col, A->row, 1);

    #pragma omp parallel for
    for (size_t i = 0; i < A->row; i++)
    {
        for (size_t j = 0; j < A->col; j++)
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
            printf("%lld ", getMatrixElement(matrix, i, j));
        }
        printf("%lld\n", getMatrixElement(matrix, i, matrix->col - 1));
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