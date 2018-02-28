#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallelRegion(void);

int main(int argc, char* argv[]){

	if(argc == 2){
		omp_set_num_threads(atoi(argv[1]));
	}


	#pragma omp parallel
	parallelRegion();
	
	return 0;
}

void parallelRegion(void){

	printf("Execution de la méthode parallelRegion\n");
}
