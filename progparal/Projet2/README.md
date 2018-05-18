# Projet 2 : Produit Matriciel Distribué

## Compilation & éxecution

Parce que j'oublie tout le temps comment compiler et éxucter ce truc.

* __Compilation__ : `mpicc -g -Wall couvreur.c -o couvreur -lm -fopenmp`
* __Execution__ : `mpirun ./couvreur data/A data/B`

## Good links

* [MPI Scatter and Gather](http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)

* [Hybrid MPI and OpenMP](https://www.cct.lsu.edu/~estrabd/intro-hybrid-mpi-openmp.pdf)

## Important things

* Un fichier nom.c où nom doit être remplacé par votre nom et un fichier nom.txt qui indique quelles fonctionnalités vous avez implémenté.

* Un fichier nom.txt qui décrira brièvement l'implémentation (structures, linéarisation des matrices, communications...) ainsi que la liste des fonctionnalités implémentées (voir à la fin).

* Ce programme devra utiliser MPI pour le calcul distribué (circulation sur anneau), et openMP pour la parallélisation des calculs

* Il devra prendre comme paramètre deux fichiers bien formés au format texte contenant la matrice A pour le premier, et la matrice B pour le second (valeurs séparées par des espaces, une ligne du fichier par ligne de matrice).

* Il affichera la matrice résultante

* Chaque valeur dans la matrice de sortie sera séparé du suivant par un unique espace, pas d'alignement de données n'est demandé

* Le processus seront organisés en anneau et le programme doit pouvoir traiter le cas où la matrice a plus de lignes/colonnes qu'il n'y a de machines disponibles

## Implémentation

### Objectifs

- [x] Calcul du produit matriciel avec N multiple de P
- [x] Gestion des matrices très grandes (testé avec 2000x2000)
- [x] Gestion du déséquilibre dans le calcul, i.e N non multiple de P

### Structures

Une structure *Matrix* composée du nombre de lignes, de colonnes et d'un tableau à une dimension représentant la matrice.

### Linéarisation des matrices

Les matrices sont donc linéarisées, chaques lignes sont à la suite les unes des autres. Donc contigües dans la mémoire.

### Communications

1. Un premier broadcast est effectué pour donner la taille N des matrices.
2. On scatter la matrice du fichier 1 par lignes, puis la matrice du fichier B par ligne (je transpose la matrice pour pouvoir utiliser la primitive scatter et la re-transpose une fois reçu).
3. Par la suite les calculs sont effectués en faisant circuler les colonnes en anneau.
4. Et enfin on gather les résultats.

### Parallélisation des calculs

* Produit matriciel : __oui__ chaque processus aura un nombre équivalant de lignes à traiter en parallèle.
* Produit matriciel partiel : __oui__ identique que précédement en ajustant les calcul sur la matrice partiel des colonnes.
* Transposition de matrice : __oui__  simple parallélisation d'une boucle for, comme je copie d'une matrice A vers une matrice B je n'ai pas à avoir peur que \[j][i] soit modifié avant \[i][j].
* Lecture fichier : __non__ mon disque dur ne possède qu'un seul bras.

### N non multiple de P

Deux cas :

1. N est inférieur à P et donc :
    * certains P n'auront pas de travail ;
    * la circulation de l'anneau devra être revue ;
    * nécissité d'utiliser un anneau ? autant faire tout sur root et basta ?
2. N est supérieur à P et donc :
    * déséquilibre au niveau du découpage (le reste de N/P doit être réparti)
    * comment scatter et gather les extra ?
    * faire simple : root s'en occupe et prend ce qu'il reste

### Différents benchmarks

Au préalable : `set OMP_NUM_THREADS 4`. OMP ne met qu'un thread par process, donc il vaut mieux changer ce paramètre.

* Avec N = 5600 soit 31 360 000 éléments :
    1. avec `-n 1`
        * real  16m36,511s
        * user  64m37,896s
        * sys   0m5,481s
    2. avec `-n 4`
        * real  17m18,370s
        * user  67m35,635s
        * sys   0m26,430s
    3. sans arguments (n = 2)
        * real  17m56,094s
        * user  69m38,305s
        * sys   0m7,417s

Les résultats ne sont vraiment pas satisfaisants même si on voit l'accélération dûe au parallélisme, je ne sais pas s'il s'agit des specs de mon PC (2 Core i7) parceque l'application est designé pour du calcul distribué ou alors qu'il y a des optimisations à faire que je ne connais pas.