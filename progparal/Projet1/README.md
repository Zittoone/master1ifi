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

  ```Bash
  real	0m2.166s /!\
  user	0m3.508s
  sys	0m0.948s
  ```

* Sans openmp

  ```Bash
  real	0m3.325s /!\
  user	0m2.608s
  sys	0m0.572s
  ```

  * Avec l'ajout des sections parallèles on a, pas trop de différences, peut être le fichier est trop petit pour le voir

  ```Bash
  real	0m2.340s
  user	0m2.808s
  sys	0m0.780s
  ```

### Remarques

* fichier de 3.6 Go -> problèmes de mémoire
* Avec openmp, on a un gain d'une seconde ... il faut paralléliser l'inversion de tableau ...

> Algorithm: Maximum Subarray Sum
>
> Input: Array A[1::n; 1::n] of numbers (positive and negative).
>
> Output: Maximum Subarray Sum of A.
>
> Begin Algorithm
> 1. Replace each row of A by its prex sums.
> 2. Add a column of zeroes as the zeroth column of A.
> 3. For all *1 <= g <= h <= n* __do in parallel__
> Compute the sequence Cgh :
>  For all 1  i  n do in parallel
> Cgh[i] := A[i][h]
> A[i][g - 1]
> (b) Compute the maximum subsequence sum of Cgh into Mgh.
> 4. Find the maximum of all Mgh *1 <= g <= h <= n* into MSA.
> 5. Output M SA.
> End Algorith