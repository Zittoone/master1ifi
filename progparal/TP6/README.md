# TP6 (Broadcast et produit Matriciel)

## Broadcast

Merci [Stackoverflow](https://stackoverflow.com/questions/7864075/using-mpi-bcast-for-mpi-communication).

Tout le monde appelle la méthode de broadcast, les données sont reçu du rang 0 dans leur buffer.

Exemple avec 666 comme donnée attribuée dans le processus 0 :
```
$ mpirun -n 4 ./broadcast
[3]: Before Bcast, buf is 32765
[1]: Before Bcast, buf is 32767
[2]: Before Bcast, buf is 32766
[0]: Before Bcast, buf is 666
[0]: After Bcast, buf is 666
[1]: After Bcast, buf is 666
[3]: After Bcast, buf is 666
[2]: After Bcast, buf is 666
```

## All-to-All

Exemple avec 4 processus :
```
$ mpirun -n 4 ./all-to-all
Tableau du processus 0 :
data[0] = 0
data[1] = 1
data[2] = 2
data[3] = 3
Tableau du processus 1 :
data[0] = 0
data[1] = 1
data[2] = 2
data[3] = 3
Tableau du processus 2 :
data[0] = 0
data[1] = 1
data[2] = 2
data[3] = 3
Tableau du processus 3 :
data[0] = 0
data[1] = 1
data[2] = 2
data[3] = 3
```
Remarque : *avec trop de processus, l'output se mélange, mais cela fonctionne bien.*

## Produit Matrice-Matrice
