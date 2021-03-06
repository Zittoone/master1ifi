#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

struct tablo {
  int * tab;
  int size;
};

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

void montee(struct tablo * source, struct tablo * destination) {
	for(int i = 0; i < source->size; i++){
		destination->tab[source->size + i] = source->tab[i];
	}
   
	for(int l = log2(source->size) - 1 ; l >= 0; l--){
		printf("l = %d\n", l);
		for(int i = (int) pow(2, l) - 1; i <= ((int) pow(2, l+1)) - 1; i++){
			destination->tab[i] = destination->tab[2 * i] + destination->tab[2 * i+1];
		}
	}
}

void descente(struct tablo * a, struct tablo * b) {

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

void final(struct tablo * a, struct tablo *b) {
  for(int i = pow(2, log2(b->size) - 1); i <= pow(2, log2(b->size)+1) - 1; i++){
		b->tab[i] = b->tab[i] + a->tab[i];
	}
}

void generateArray(struct tablo * s) {
  //construction d'un tableau pour tester
  s->size=8;
  s->tab=malloc(s->size*sizeof(int));
  s->tab[0]=3;
  s->tab[1]=1;
  s->tab[2]=7;
  s->tab[3]=0;
  s->tab[4]=4;
  s->tab[5]=1;
  s->tab[6]=6;
  s->tab[7]=3;

}

int main(int argc, char **argv) {
  struct tablo source;

  generateArray(&source);

  struct tablo * a = allocateTablo(source.size*2);
  montee(&source, a);
  printArray(a);

  struct tablo * b = allocateTablo(source.size*2);
  descente(a, b);
  printArray(b);
   
  final(a,b);
  printArray(b);
}
