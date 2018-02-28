#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void privateScope0(void); 
void privateScope1(void); 

int global = 0;

int main(int argc, char* argv[]){

	if(argc == 2){
		omp_set_num_threads(atoi(argv[1]));
	}

	// privateScope0();
	privateScope1();

	printf("La valeur de `global` est %d\n", global);
	
	return 0;
}

void privateScope0(void){
	#pragma omp parallel for
	for(int i = 0; i < 10000; i++){
		global += i;
	}
}

void privateScope1(void){
	#pragma omp parallel for private(global)
	for(int i = 0; i < 10000; i++){
		global += i;
	}
}
