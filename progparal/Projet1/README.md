# PROJET SI4/IFI

## Sous-séquence Maximale

## Compilation

`gcc -Wall -std=c99 couvreur.c -o couvreur -lm -fopenmp`

## Méthodes

* *lecture du fichier* __non parallelisée__
* *`void generateArray(struct tablo *, char*)`* __non parallelisée__
* *`void sum(struct tablo *, struct tablo *, int mode)`*
  * *`void montee_sum(struct tablo *, struct tablo *)`* __parallelisée__
  * *`void descente_sum(struct tablo *, struct tablo *)`* __parallelisée__
  * *`void final_sum(struct tablo *, struct tablo *)`* __parallelisée__
* *`void maximum(struct tablo *, struct tablo *, int mode)`*
  * *`void montee_max(struct tablo *, struct tablo *)`* __parallelisée__
  * *`void descente_max(struct tablo *, struct tablo *)`* __parallelisée__
  * *`void final_max(struct tablo *, struct tablo *)`* __parallelisée__
* *trouver la valeur max* __parallelisée avec réduction__
* *création du tableau M* __parallelisée__
* *`void printArray(struct tablo *)`* __non parallelisée__
* *`struct tablo *allocateTablo(int)`* __non parallelisée__