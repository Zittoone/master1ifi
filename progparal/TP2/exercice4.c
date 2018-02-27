#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

void tri_fusion(long* tab, int size);

int main(int argc, char* argv[]){

	int size = atoi(argv[1]);

	long* tab = malloc(sizeof(long) * size);
	srand(time(NULL) % 10 + 1);

	for(int i = size -1; i > 0; i++){
		//tab[i] = rand();

	}

	// Calcul du temps en fonction de la taille du tableau
	struct timeval t1, t2;

	gettimeofday (&t1, NULL);

	tri_fusion(tab, size);

	gettimeofday (&t2, NULL);

	float texec =
	(float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
	t1.tv_usec);

	printf("%d %d %f\n", size, nbthread, texec);
}

void tri_fusion(long* tab, int size){

	for(int i = 0; i < size; i++){
		tab[i] = tab[i] * tab[i];

		if (i==0) {
			nbthread = omp_get_num_threads();
		}
	}
}
