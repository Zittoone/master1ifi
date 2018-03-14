# PROJET SI4/IFI
## Sous-séquence Maximale

## Compilation

`gcc -o couvreur -Wall -std=c99 couvreur.c -lm -fopenmp`

## TODO:

1. Calculer les sum-prefix de Q et les mettre dans un tableau PSUM
2. Calculer le sum-suffix de Q et les mettre dans un tableau SSUM
3. Calculer le max-suffix de PSUM et le mettre dans SMAX
4. Calculer le max-prefix de SSUM et le mettre dans PMAX
5. pour  1 <= i <= n faire en parallel
  1. Ms[i] = PMAX[i] - SSUM[i] + Q[i]
  2. Mp[i] = SMAX[i] - PSUM[i] + Q[i]
  3. M[i] = Ms[i] + Mp[i] - Q[i]
6. Trouver la valeur maximal dans M 
