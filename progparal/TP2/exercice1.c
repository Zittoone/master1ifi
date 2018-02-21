
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	
	carre(tab, size);

	for(int i = 0; i < size; i++){
		printf("%ld\n", tab[i]);
	}
}

void carre(long* tab, int size){
	for(int i = 0; i < size; i++){
		tab[i] = tab[i] * tab[i];
	}
}
