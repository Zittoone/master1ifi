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

