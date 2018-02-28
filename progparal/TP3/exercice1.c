#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallelRegion(void);
void paralleRegionForOutside(void);
void parallelRegionForInside(void);
void parallelRegionForInsideWithPragma(void);

int main(int argc, char* argv[]){

	if(argc == 2){
		omp_set_num_threads(atoi(argv[1]));
	}

	// parallelRegion();
	// paralleRegionForOutside();
	// parallelRegionForInside();
	parallelRegionForInsideWithPragma();
	
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

void parallelRegionForInside(void){
	
	#pragma omp parallel
	{
		printf("Execution de la méthode parallelRegionForInside1\n");

		for(int i = 0; i < 4; i++){
			printf("Execution de la méthode parallelRegionForInside2\n");
		}	
	}
}

void parallelRegionForInsideWithPragma(void){

	#pragma omp parallel
	{
		printf("Execution de la méthode parallelRegionForInside1\n");

		#pragma omp for
		for(int i = 0; i < 4; i++){
			printf("Execution de la méthode parallelRegionForInside2\n");
		}	
	}
}
