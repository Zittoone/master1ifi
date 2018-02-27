#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

int size;
void produit_matriciel(int** A, int** B, int** result);

int main(int argc, char* argv[]){

	if(argc == 3){
		omp_set_num_threads(atoi(argv[2]));
	} else if(argc != 2){
		return 1;
	}

	size = atoi(argv[1]);

	// Create a size * size matrix
	int **mat = (int **)malloc(size * sizeof(int*));
	int **matresult = (int **)malloc(size * sizeof(int*));

	for(int i = 0; i < size; i++){
		mat[i] = (int *)malloc(size * sizeof(int));
		matresult[i] = (int *)malloc(size * sizeof(int));
		for(int j = 0; j < size; j++){
			mat[i][j] = i + j;
			matresult[i][j] = 0;
		}
	}

	// Calcul du temps en fonction de la taille du tableau
	struct timeval t1, t2;

	gettimeofday (&t1, NULL);

	printf("Processing ...\n");
	produit_matriciel(mat, mat, matresult);

	gettimeofday (&t2, NULL);

	float texec =
	(float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
	t1.tv_usec);

	printf("Matrix multiplication of two %d * %d matrices took %f\n", size, size, texec);
	printf("matresult[%d][%d] = %d\n", size-1, size-1, matresult[size-1][size-1]);

}

void produit_matriciel(int** A, int** B, int** result){


	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			#pragma parralel for
			for (int k = 0; k < size; k++){
				result[i][j] = A[i][k] * B[k][j] + result[i][j];
			}
		}
	}

}
