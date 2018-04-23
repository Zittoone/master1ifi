#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Matrix */
struct Matrix
{
    int col;
    int line;
    int *matrix;
};

int getMatrixElement(struct Matrix *, int, int);
void setMatrixElement(struct Matrix *, int, int, int);
struct Matrix *allocateMatrix(int line, int col);
struct Matrix *generateMatrix(char *);
void matrixProduct(struct Matrix *, struct Matrix *, struct Matrix *);

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

        N = m1->line;
        
        m3 = allocateMatrix(N, N);

        matrixProduct(m1, m2, m3);

        printMatrix(m3);
    }

    MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);

    // printf("I am %d and N is %d\n", rank, N);

    // TODO: scatter it o the other workers

    MPI_Finalize();
}

struct Matrix *allocateMatrix(int line, int col)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->col = col;
    matrix->line = line;
    matrix->matrix = (int *)malloc(sizeof(int) * col * line);

    for (int i = 0; i < col * line; i++)
    {
        matrix->matrix[i] = 0;
    }

    return matrix;
}

struct Matrix *generateMatrix(char *buffer)
{
    struct Matrix* matrix;

    int count = 0;
    char **lines = (char**) malloc(sizeof(char*) * 10);

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
 * To get mat[line][col] we need to access mat[(line * col) + offset]
 * 
 * Ex: elem matrix[4][3] of matrix[5][5] is (4 * 5) + 3 which is the 23rd element
*/
int getMatrixElement(struct Matrix *mat, int line, int col)
{
    return mat->matrix[(line * mat->col) + col];
}

void setMatrixElement(struct Matrix *mat, int line, int col, int val)
{
    mat->matrix[(line * mat->col) + col] = val;
}

void matrixProduct(struct Matrix *A, struct Matrix *B, struct Matrix *C)
{

    for (int i = 0; i < A->line; i++)
    {
        for (int j = 0; j < A->col; j++)
        {
            for (int k = 0; k < B->line; k++)
            {
                int newVal = getMatrixElement(C, i, j) + getMatrixElement(A, i, k) * getMatrixElement(B, k, j);
                setMatrixElement(C, i, j, newVal);
            }
        }
    }
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
    for (int i = 0; i < matrix->line; i++)
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