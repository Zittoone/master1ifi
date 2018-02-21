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

4. Il y a 4 threads qui sont créés sur la machine linux de l'université (4 coeurs detectés).

5. Script bash faisant une génération avec 1 à 20 threads

6. 

7. On peut modifier la variable d'environnement OMP_NUM_THREADS (cf. https://software.intel.com/en-us/mkl-windows-developer-guide-setting-the-number-of-threads-using-an-openmp-environment-variable)

## Exercice 2 (Variables partagées et privées) 

1. Sur trois executions la valeur de 'total' est différentes : 
```bash
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

2. Une variable privée est une variable déclarée dans la zone parallélisée par omp. On utilise ici la clause private(nomDeVariable). Cela ne fonctionne pas car cela fonctionne comme un read only, toutes les modifications efectuées ne sont donc pas prises en compte sur la vraie variable total.

3. 

