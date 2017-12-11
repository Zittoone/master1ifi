#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define taille 1000

void multiplicationMatrice();
void multiplicationMatriceDeroule7Fois();
void multiplicationMatriceDerouleExt2Fois();
void multiplicationMatriceIKJ();
void multiplicationMatriceJIK();
void multiplicationMatriceJKI();


static int vA[taille];
static int vB[taille];
static int vC[taille];

static int mA[taille][taille];
static int mB[taille][taille];
static int mC[taille][taille];

int main(void){
    
	srand(time(NULL));

	struct timeval t1, t2;
/*
    int taille = 1000;
    int *vA = malloc(taille * sizeof(int));
	int *vB = malloc(taille * sizeof(int));
	int	*vC = malloc(taille * sizeof(int));
*/
    int i, j;
    for(i = 0; i < taille; i++){
        *(vA + i) = rand()%9+1;
        *(vB + i) = rand()%9+1;
        *(vC + i) = rand()%9+1;
    }
/*
    int **mA = (int **)malloc(taille * sizeof(int*));
	int **mB = (int **)malloc(taille * sizeof(int*));
	int **mC = (int **)malloc(taille * sizeof(int*));

	for(i = 0; i < taille; i++){
		mA[i] = (int *)malloc(taille * sizeof(int));
		mB[i] = (int *)malloc(taille * sizeof(int));
		mC[i] = (int *)malloc(taille * sizeof(int));
	}
*/
    for(i = 0; i < taille; i++){
        for(j = 0; i < taille; i++){
            mA[i][j] = rand()%9+1;
            mB[i][j] = rand()%9+1;
            mC[i][j] = rand()%9+1;
        }
    }

	// Sans déroulage
	gettimeofday (&t1, NULL);

    //multiplicationMatrice();
	multiplicationMatriceIKJ();

	gettimeofday(&t2, NULL);

	float texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

    printf("Le temps d’éxecution sans déroulage IKJ est de %f microsecondes.\n", texec);

	gettimeofday (&t1, NULL);

	multiplicationMatriceJIK();

	gettimeofday(&t2, NULL);

	texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

    printf("Le temps d’éxecution sans déroulage JIK est de %f microsecondes.\n", texec);

	gettimeofday (&t1, NULL);

	multiplicationMatriceJKI();

	gettimeofday(&t2, NULL);

	texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

    printf("Le temps d’éxecution sans déroulage JKI est de %f microsecondes.\n", texec);

	// Avec déroulage
	gettimeofday (&t1, NULL);

    multiplicationMatriceDeroule7Fois();
	//multiplicationMatriceDerouleExt2Fois();

	gettimeofday (&t2, NULL);

	texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

      printf("Le temps d’éxecution avec déroulage est de %f microsecondes.\n", texec);
	printf("Matrice 2 dernier elem : %d\n", mA[0][0]);
	return 0;
}


void multiplicationMatrice(){

    int i, j, k;
    for(i = 0; i < taille; i++){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}

void multiplicationMatriceDeroule7Fois(){

    int i, j, k, reste;
	reste = taille%8;
    for(i = 0; i < taille; i++){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k+=8){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
				mC[i+1][j+1] = mC[i+1][j+1] + mA[i+1][k+1] * mB[k+1][j+1];
				mC[i+2][j+2] = mC[i+2][j+2] + mA[i+2][k+2] * mB[k+2][j+2];
				mC[i+3][j+3] = mC[i+3][j+3] + mA[i+3][k+3] * mB[k+3][j+3];
				mC[i+4][j+4] = mC[i+4][j+4] + mA[i+4][k+4] * mB[k+4][j+4];
				mC[i+5][j+5] = mC[i+5][j+5] + mA[i+5][k+5] * mB[k+5][j+5];
				mC[i+6][j+6] = mC[i+6][j+6] + mA[i+6][k+6] * mB[k+6][j+6];
				mC[i+7][j+7] = mC[i+7][j+7] + mA[i+7][k+7] * mB[k+7][j+7];
            }
        }
    }
	for(i = 0; i < taille; i++){
        for(j = 0; j < taille; j++){
            for(k = taille - reste; k < taille; k++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}

void multiplicationMatriceDerouleExt2Fois(){

    int i, j, k, reste;
	reste = taille%3;
    for(i = 0; i < taille; i+=3){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
		for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                mC[i+1][j] = mC[i+1][j] + mA[i+1][k] * mB[k][j];
            }
        }
		for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                mC[i+2][j] = mC[i+2][j] + mA[i+2][k] * mB[k][j];
            }
        }
    }

/*
	for(i = 0; i < taille; i+=3){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
				C[i+1][j] = C[i+1][j] + A[i+1][k] * B[k][j];
				C[i+2][j] = C[i+2][j] + A[i+2][k] * B[k][j];
            }
        }
    }
*/
	for(i = taille - reste; i < taille; i++){
        for(j = 0; j < taille; j++){
            for(k = 0; k < taille; k++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}

void multiplicationMatriceIKJ(){
	int i, j, k;
    for(i = 0; i < taille; i++){
        for(k = 0; k < taille; k++){
            for(j = 0; j < taille; j++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}

void multiplicationMatriceJIK(){
	int i, j, k;
    for(j = 0; j < taille; j++){
        for(i = 0; i < taille; i++){
            for(k = 0; k < taille; k++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}

void multiplicationMatriceJKI(){
	int i, j, k;
    for(j = 0; j < taille; j++){
        for(k = 0; k < taille; k++){
            for(i = 0; i < taille; i++){
                mC[i][j] = mC[i][j] + mA[i][k] * mB[k][j];
            }
        }
    }
}


