#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>


void carre(long*, int);

// Var globales
int nbthread;
long total=9999;

int main(int argc, char* argv[]){

	if(argc == 3){
		omp_set_num_threads(atoi(argv[2]));
	} else if(argc != 2){
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

	printf("TOTAL: %ld\n", total);
	printf("%d %d %f\n", size, nbthread, texec);
}

void carre(long* tab, int size){

	#pragma omp parallel for private(total)
	for(int i = 0; i < size; i++){		
		tab[i] = tab[i] * tab[i];

		// Update total inside parallelized loop
		total += tab[i];

		if (i==0) {
			nbthread = omp_get_num_threads();
		}
	}	
}
