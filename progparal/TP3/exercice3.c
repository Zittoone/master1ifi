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
  for (i = 0; i < size; ++i) {
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
  //TODO : remplissage du tableau destination de taille 2*n en
  // copiant les données du tableau source dans destination, 
  // à la bonne position
  // on suppose que le malloc de destination a été fait avant
   
         
  // TODO: Boucle de calcul pour la montée dans l'arbre/tableau
}

void descente(struct tablo * a, struct tablo * b) {
  // TODO : implementation de la phase de descente
}

void final(struct tablo * a, struct tablo *b) {
  // TODO : phase finale
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
