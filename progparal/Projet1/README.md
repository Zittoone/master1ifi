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
* *`void printArray(struct tablo *)`* __non parallelisée__
* *`struct tablo *allocateTablo(int)`* __non parallelisée__
* *`void inverser_tablo(struct tablo *)`* __non parallelisée__

## TODO

* supprimer l'inversion de tableau (très couteuse)
* faire une étude sur la lecture de fichier par chunk et paralléliser la conversion en long puis mise en mémoire
* optimiser la recherche des bornes de la sous séquence max

## Résultats avec un fichier de 2^24 nombres (sur VM peut être cause problème ?)

* Avec openmp
  ```
  real	0m2.166s
  user	0m3.508s
  sys	0m0.948s
  ```

* Sans openmp

  ```
  real	0m3.325s
  user	0m2.608s
  sys	0m0.572s
  ```

### Remarques

* fichier de 3.6 Go -> problèmes de mémoire
* Avec ou sans openmp, pas trop de différences ... il faut paralléliser l'inversion de tableau ...