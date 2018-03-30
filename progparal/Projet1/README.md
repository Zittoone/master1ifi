# PROJET SI4/IFI

## Sous-séquence Maximale

## Compilation

`gcc -o couvreur -Wall -std=c99 couvreur.c -lm -fopenmp`

## TODO:

1. Calculer les sum-prefix de Q et les mettre dans un tableau PSUM
2. Calculer le sum-suffix de Q et les mettre dans un tableau SSUM
3. Calculer le max-suffix de PSUM et le mettre dans SMAX
4. Calculer le max-prefix de SSUM et le mettre dans PMAX
5. pour  1 <= i <= n faire en parallel
    1. Ms[i] = PMAX[i] - SSUM[i] + Q[i]
    2. Mp[i] = SMAX[i] - PSUM[i] + Q[i]
    3. M[i] = Ms[i] + Mp[i] - Q[i]
6. Trouver la valeur maximal dans M

use valgrind

## Tips

* Chunk reading files
* ~~fscanf pour éviter la conversion~~ utiliser atoi() apparemment
* rendre générique les fonctions de calcul prefixe et suffixe (choisir le sens de lecture)
* sum_prefix ou sum_suffix à partir d'int peut produire un overflow, ne pas oublier de chnger ceux-ci en long int

## Goals

* Algo fonctionnel
* Optimisation temps d'exec