#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallelRegion(void);
void paralleRegionForOutside(void);

int main(int argc, char* argv[]){

	if(argc == 2){
		omp_set_num_threads(atoi(argv[1]));
	}

	// parallelRegion();
	paralleRegionForOutside();
	
	return 0;
}

void parallelRegion(void){

	#pragma omp parallel
	printf("Execution de la méthode parallelRegion\n");
}

void paralleRegionForOutside(void){

	#pragma omp parallel
	printf("Execution de la méthode paralleRegionForOutside1\n");

	for(int i = 0; i < 4; i++){
		printf("Execution de la méthode paralleRegionForOutside2\n");
	}	
}
