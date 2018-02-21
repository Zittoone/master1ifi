#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>


void carre(long*, int);

int main(int argc, char* argv[]){

	if(argc != 2){
		return 1;
	}
	int size = atoi(argv[1]);

	long* tab = malloc(sizeof(long) * size);
	srand(time(NULL));

	for(int i = 0; i < size; i++){
		tab[i] = rand();
	}

	// Calcul du temps en fonction de la taille du tableau
	struct timeval t1, t2;

	gettimeofday (&t1, NULL);
	
	carre(tab, size);

	gettimeofday (&t2, NULL);

	float texec =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec);

	printf("%d %f\n", size, texec);
}

void carre(long* tab, int size){

	#pragma omp parallel for
	for(int i = 0; i < size; i++){		
		tab[i] = tab[i] * tab[i];
	}	
}
