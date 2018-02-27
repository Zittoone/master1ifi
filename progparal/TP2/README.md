# TP2 (introduction à OpenMP)

## Exercice 1 (parallélisme de boucle for)

* Sans OpenMP
```bash
./exercice1 45000000  0,52s user 0,02s system 99% cpu 0,541 total
```

* Avec OpenMP
```bash
./exercice1_omp 45000000  9,49s user 8,79s system 360% cpu 5,073 total
```

  OpenMP ralentit considérablement l'éxecution du programme, et passe la plupart du temps à faire des appls systèmes.
1. Fait
2. Fait
3. Fait
4. Il y a 4 threads qui sont créés sur la machine linux de l'université (4 coeurs detectés).
5. Script bash faisant une génération avec 1 à 20 threads
6. __TODO__
7. On peut modifier la variable d'environnement OMP_NUM_THREADS (cf. [intel's website](https://software.intel.com/en-us/mkl-windows-developer-guide-setting-the-number-of-threads-using-an-openmp-environment-variable) )

## Exercice 2 (Variables partagées et privées)

1. Sur trois executions la valeur de 'total' est différentes :
  ```
  ca404826@jonquille ~/Documents/master1ifi/progparal/TP2> ./exercice1_omp 10000000
  TOTAL: 8175771910529360827
  10000000 1 42861.000000

  ca404826@jonquille ~/Documents/master1ifi/progparal/TP2> ./exercice1_omp 10000000
  TOTAL: -6059170246412056670
  10000000 1 42977.000000

  ca404826@jonquille ~/Documents/master1ifi/progparal/TP2> ./exercice1_omp 10000000
  TOTAL: 3633055549633902488
  10000000 1 42474.000000
  ```
Ceci est pour cause d'accès concurrents modifiant une variable partagée.
2. Une variable privée est une variable déclarée dans la zone parallélisée par omp. On utilise ici la clause private(nomDeVariable). Cela ne fonctionne pas car cela fonctionne comme un read only, toutes les modifications effectuées ne sont donc pas prises en compte sur la vraie variable total.

3. Le temps de calcul est beaucoup plus élevé :

  __Sans section critique__
  ```
  alexis@debian:/media/sf_master1ifi/progparal/TP2$ ./exercice2_omp
  10000 4 178.000000 (ns)
  ```

  __Avec section critique__
  ```
  alexis@debian:/media/sf_master1ifi/progparal/TP2$ ./exercice2_omp
  10000 4 3126.000000 (ns)
```

4. Définition simple trouvée sur internet [Ref. p.24](https://haydn2005.u-bourgogne.fr/dsi-ccub/IMG/pdf/openMP_Fortran_C.pdf).
  > Cette clause est utilisée pour calculer une somme, un produit, un maximum... etc. de variables dont la valeur change avec les indices d’une boucle (par exemple) et chaque nouvelle
  valeur dépend de la valeur précédente.

5. Le résultat est correct avec l'utilisation de l'opération de réduction, de plus on atteint les mêmes performances qu'au départ, __c'est donc préférable à l'usage d'une section critique__ !

  ```
  alexis@debian:/media/sf_master1ifi/progparal/TP2$ ./exercice2_omp 10000
  TOTAL: 333283335000
  10000 4 110.000000
  ```

## Exercice 3

- [x] Écrivez un programme parallèle de calcul du produit de 2 matrices.

## Exercice 4 (Blocs parallèles)
