#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void privateScope0(void); 
void privateScope1(void);
void privateScope2(void);
void privateScope2_sub(void);

int global = 0;
int N = 10000;

int main(int argc, char* argv[]){

	if(argc == 2){
		omp_set_num_threads(atoi(argv[1]));
	}

	// privateScope0();
	// privateScope1();
	privateScope2();

	printf("La valeur de `global` est %d\n", global);
	
	return 0;
}

void privateScope0(void){
	#pragma omp parallel for
	for(int i = 0; i < N; i++){
		global += i;
	}
}

void privateScope1(void){
	#pragma omp parallel for private(global)
	for(int i = 0; i < N; i++){
		global += i;
	}
}

void privateScope2(void){
	#pragma omp parallel for private(global)
	for(int i = 0; i < N; i++){
		privateScope2_sub();
	}
}

void privateScope2_sub(void){
	global++;
}
