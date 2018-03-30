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

## TODO

* Algo fonctionnel OK
* Lecture fichier -> si taille trop grande, chunker le fichier ?
* transformation int en long
* mieux opti héhé

## Valgrind

* Without free tmp tabs : 
    ```
    HEAP SUMMARY:
    ==2720==     in use at exit: 4,960 bytes in 38 blocks
    ==2720==   total heap usage: 77 allocs, 39 frees, 115,760 bytes allocated
    ==2720== 
    ==2720== LEAK SUMMARY:
    ==2720==    definitely lost: 304 bytes in 16 blocks
    ==2720==    indirectly lost: 1,472 bytes in 15 blocks
    ==2720==      possibly lost: 864 bytes in 3 blocks
    ==2720==    still reachable: 2,320 bytes in 4 blocks
    ==2720==         suppressed: 0 bytes in 0 blocks
    ```

* With free : 
    ```
    HEAP SUMMARY:
    ==2853==     in use at exit: 4,832 bytes in 30 blocks
    ==2853==   total heap usage: 77 allocs, 47 frees, 115,760 bytes allocated
    ==2853== 
    ==2853== LEAK SUMMARY:
    ==2853==    definitely lost: 1,200 bytes in 16 blocks
    ==2853==    indirectly lost: 448 bytes in 7 blocks
    ==2853==      possibly lost: 864 bytes in 3 blocks
    ==2853==    still reachable: 2,320 bytes in 4 blocks
    ==2853==         suppressed: 0 bytes in 0 blocks
    ```

    no real changes with free