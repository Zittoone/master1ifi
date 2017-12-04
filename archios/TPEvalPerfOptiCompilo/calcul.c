#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void additionVecteur(int*, int*, int*, int);
void multiplicationMatrice(int**, int**, int**, int);
void multuplicationVecteurScalaire(int*, int, int);

int main(void){
    
	srand(time(NULL));

	struct timeval t1, t2;

	gettimeofday (&t1, NULL);

    int taille = 1000;
    int *vA = malloc(taille * sizeof(int));
	int *vB = malloc(taille * sizeof(int));
	int	*vC = malloc(taille * sizeof(int));

    int i, j;
    for(i = 0; i < taille; i++){
        *(vA + i) = rand()%9+1;
        *(vB + i) = rand()%9+1;
        *(vC + i) = rand()%9+1;
    }

    additionVecteur(vA, vB, vC, taille);

    multuplicationVecteurScalaire(vA, 5, taille);

    additionVecteur(vA, vB, vC, taille);

    int **mA = (int **)malloc(taille * sizeof(int*));
	int **mB = (int **)malloc(taille * sizeof(int*));
	int **mC = (int **)malloc(taille * sizeof(int*));

	for(i = 0; i < taille; i++){
		mA[i] = (int *)malloc(taille * sizeof(int));
		mB[i] = (int *)malloc(taille * sizeof(int));
		mC[i] = (int *)malloc(taille * sizeof(int));
	}

    for(i = 0; i < taille; i++){
        for(j = 0; i < taille; i++){
            mA[i][j] = rand()%9+1;
            mB[i][j] = rand()%9+1;
            mC[i][j] = rand()%9+1;
        }
    }

    multiplicationMatrice(mA, mB, mC, taille);

	additionVecteur(vA, vB, vC, taille);

    multuplicationVecteurScalaire(vA, 5, taille);

    additionVecteur(vA, vB, vC, taille);

	multiplicationMatrice(mA, mB, mC, taille);

	gettimeofday (&t2, NULL);

	float texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

      printf("Le temps d’éxecution est de %f microsecondes.\n", texec);

	return 0;
}

void additionVecteur(int *A, int *B, int *C, int N){

    int i;
    for(i = 0; i < N; i++){
        *(C + i) = *(A + i) + *(B + i);
    }
}

void multiplicationMatrice(int **A, int **B, int **C, int taille){

    int i, j, k;
    for(i = 0; i < taille; i++){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void multuplicationVecteurScalaire(int *A, int s, int N){

    int i;
    for(i = 0; i < N; i++){
        A[i] = A[i] * s;
    }
}
