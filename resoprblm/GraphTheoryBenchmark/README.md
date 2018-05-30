# Graph Theory Benchmark

## Gabow

* Implémentation compréhensible, assez rapide à implémenter

## Kosaraju

* Implémentation très simple, algo très élégant

## Tarjan

* Implémentation très rapide, pas très évident à comprendre au début

## Benchmarks
Temps en ms avec 10 000 000 de sommets et ajout à chaque itération (10) de 1 000 000 d'arcs avec respectivement Tarjan, Kosaraju et Gabow

* Take 1 :
```
[
    [6923, 5565, 5242, 4410, 3523, 3613, 4652, 4610, 3400, 3902],
    [10612, 6320, 11986, 12576, 14795, 18790, 16943, 21020, 20026, 22321],
    [3019, 703, 865, 829, 833, 2909, 3023, 770, 820, 3082]
]
```

* Take 2 :
```
[
    [7477, 4508, 4086, 3369, 4428, 3297, 4471, 4481, 3255, 3777],
    [15169, 11123, 12446, 11356, 16374, 18721, 16227, 20413, 19377, 23402],
    [704, 925, 766, 693, 712, 2782, 2843, 783, 819, 833]
]
```