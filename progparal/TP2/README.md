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
Il y a 4 threads qui sont créés sur la machine linux de l'université (4 coeurs detectés).

