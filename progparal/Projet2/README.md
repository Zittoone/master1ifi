# Projet 2 : Produit Matriciel Distribué

## Compilation & éxecution

Parce que j'oublie tout le temps comment compiler et éxucter ce truc.

* __Compilation__ : `mpicc couvreur.c -o couvreur -lm`
* __Execution__ : `mpirun ./couvreur`

## Good links

* [MPI Scatter and Gather](http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)

## Important things

* Un fichier nom.c où nom doit être remplacé par votre nom et un fichier nom.txt qui indique quelles fonctionnalités vous avez implémenté.

* Un fichier nom.txt qui décrira brièvement l'implémentation (structures, linéarisation des matrices, communications...) ainsi que la liste des fonctionnalités implémentées (voir à la fin).

* Ce programme devra utiliser MPI pour le calcul distribué (circulation sur anneau), et openMP pour la parallélisation des calculs

* Il devra prendre comme paramètre deux fichiers bien formés au format texte contenant la matrice A pour le premier, et la matrice B pour le second (valeurs séparées par des espaces, une ligne du fichier par ligne de matrice).

* Il affichera la matrice résultante

* Chaque valeur dans la matrice de sortie sera séparé du suivant par un unique espace, pas d'alignement de données n'est demandé

* Le processus seront organisés en anneau et le programme doit pouvoir traiter le cas où la matrice a plus de lignes/colonnes qu'il n'y a de machines disponibles

## Implémentation

### Structures

### Linéarisation des matrices

### Communications

## TODO

* File reading -> realloc on the pointer
* File reading -> handle empty lines