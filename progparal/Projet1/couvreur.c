#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

/* Structures */
struct tablo {
  int * tab;
  int size;
};

/* Headers */
void printArray(struct tablo*);
void sum_prefix(struct tablo*, struct tablo*);
void sum_suffix(struct tablo*, struct tablo*);
void max_suffix(struct tablo*, struct tablo*);
void max_prefix(struct tablo*, struct tablo*);
void generateArray(struct tablo*);

struct tablo * allocateTablo(int);


/*  */
int main(int argc, char* argv[]){

	/* args check */
	/*if(argc != 2){
		fprintf(stderr, "Usage : prog <file_name>");
		exit(EXIT_FAILURE);
	}*/

	/* file check */
	/*File* f = fopen(argv[1], "r");
	if(f == NULL){
		fprintf(stderr, "The file \"%s\" doesn't exist.", argv[1]);
		exit(EXIT_FAILURE);
	}*/

	/* file reading */
	/*char* inputs = NULL;
	if(getline(&inputs, NULL, f) == -1){
		fprintf(stderr, "An error occured reading the file \"%s\".", argv[1]);
		exit(EXIT_FAILURE);
	}*/

	/* close file */
	//fclose(f);

	/* compute */

	/*
	 * 1. Calculer les sum-prefix de Q et les mettre dans un tableau PSUM
	 */
	struct tablo Q, PSUM;
	generateArray(&Q); // TODO: replace this with file's input
	sum_prefix(&Q, &PSUM);

	printf("Tableau sum-prefix:\n");
	printArray(&PSUM);
	
	/*
	 * 2. Calculer le sum-suffix de Q et les mettre dans un tableau SSUM
	 */
	struct tablo SSUM;
	sum_suffix(&Q, &SSUM);

	printf("Tableau sum-suffix:\n");
	printArray(&SSUM);

	/*
	 * 3. Calculer le max-suffix de PSUM et le mettre dans SMAX
	 */
	struct tablo SMAX;
	max_suffix(&PSUM, &SMAX);

	/*
	 * 4. Calculer le max-prefix de SSUM et le mettre dans PMAX
	 */
	struct tablo PMAX;
	max_prefix(&SSUM, &PMAX);
	
	
}


























void printArray(struct tablo * tmp) {
  printf("---- Array of size %i ---- \n", tmp->size);
  int size = tmp->size;
  int i;
  for (i = 1; i < size; ++i) {
    printf("%i ", tmp->tab[i]);
  }
  printf("\n");
}

struct tablo * allocateTablo(int size) {
  struct tablo * tmp = malloc(sizeof(struct tablo));
  tmp->size = size;
  tmp->tab = malloc(size*sizeof(int));
  return tmp;
}

/*
 * PREFIX
 */

void montee_prefix(struct tablo * source, struct tablo * destination) {
	for(int i = 0; i < source->size; i++){
		destination->tab[source->size + i] = source->tab[i];
	}
   
	for(int l = log2(source->size) - 1 ; l >= 0; l--){
		//printf("l = %d\n", l);
	#pragma omp parralel for
		for(int i = (int) pow(2, l) - 1; i <= ((int) pow(2, l+1)) - 1; i++){
			destination->tab[i] = destination->tab[2 * i] + destination->tab[2 * i+1];
		}
	}
}

void descente_prefix(struct tablo * a, struct tablo * b) {

	b->tab[1] = 0;
	for(int k = 1; k <= log2(a->size) - 1; k++){
		for(int i = pow(2, k); i <=	pow(2, k+1) - 1; i++){
			if(i%2 == 0){
				b->tab[i] = b->tab[i/2];
			} else {
				b->tab[i] = b->tab[i/2] + a->tab[i-1];
			}
		}
	}
}

/*
 * SUFFIX
 */

void montee_suffix(struct tablo * source, struct tablo * destination) {
	for(int i = 0; i < source->size; i++){
		destination->tab[source->size + i] = source->tab[i];
	}
   
	for(int l = log2(source->size) - 1 ; l >= 0; l--){
		for(int i = (int) pow(2, l) - 1; i <= ((int) pow(2, l+1)) - 1; i++){
			destination->tab[i] = destination->tab[2 * i] + destination->tab[2 * i+1];
		}
	}
}

void descente_suffix(struct tablo * a, struct tablo * b) {

	b->tab[1] = 0;
	for(int k = 1; k <= log2(a->size) - 1; k++){
		for(int i = pow(2, k); i <=	pow(2, k+1) - 1; i++){
			if(i%2 == 0){
				b->tab[i] = b->tab[i/2];
			} else {
				b->tab[i] = b->tab[i/2] + a->tab[i-1];
			}
		}
	}
}

void inverser_tablo(struct tablo * a){
	int i = a->size - 1;
	int j = 0;
  	while(i > j) {
		int temp = a->tab[i];
	    a->tab[i] = a->tab[j];
	    a->tab[j] = temp;
    	i--;
	    j++;
  	}
}



void final(struct tablo * a, struct tablo *b) {

	int m = log2(b->size/2);
  	for(int i = pow(2, m - 1); i <= pow(2, m+1) - 1; i++){
		b->tab[i] = b->tab[i] + a->tab[i];
	}
}

void sum_prefix(struct tablo * source, struct tablo * destination){
	struct tablo * a = allocateTablo(source->size*2);
	montee_prefix(source, a);
	// printArray(a);

	struct tablo * b = allocateTablo(source->size*2);
	descente_prefix(a, b);
	// printArray(b);
   
	final(a,b);
	*destination = *b;
}

void sum_suffix(struct tablo * source, struct tablo * destination){

	// TODO: inverser tableau
	inverser_tablo(source);

	struct tablo * a = allocateTablo(source->size*2);
	montee_suffix(source, a);
	// printArray(a);

	struct tablo * b = allocateTablo(source->size*2);
	descente_suffix(a, b);
	// printArray(b);
   
	final(a,b);
	// reinverser tableau
	inverser_tablo(b);

	*destination = *b;
}

void max_suffix(struct tablo * source, struct tablo * destination){
	
}

void max_prefix(struct tablo * source, struct tablo * destination){
	
}



void generateArray(struct tablo * s) {
  //construction d'un tableau pour tester
  s->size=16;
  s->tab=malloc(s->size*sizeof(int));
  s->tab[0]=3;
  s->tab[1]=2;
  s->tab[2]=-7;
  s->tab[3]=11;
  s->tab[4]=10;
  s->tab[5]=-6;
  s->tab[6]=4;
  s->tab[7]=9;
  s->tab[8]=-6;
  s->tab[9]=1;
  s->tab[10]=-2;
  s->tab[11]=-3;
  s->tab[12]=4;
  s->tab[13]=-3;
  s->tab[14]=0;
  s->tab[15]=2;


}
/*
int main(int argc, char **argv) {
  struct tablo source;

  generateArray(&source);

  sum_prefix(&source);

  printArray(&source);
}*/
