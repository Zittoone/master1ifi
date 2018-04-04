# TP6 (Broadcast et produit Matriciel)

## Broadcast

1. Écrivez un programme MPI qui permet à un processeur (par exemple 0) d'envoyer une valeur à tous les autres.

## All-to-All

On considère p processus possédant un tableau tab de taille p tel que *tab[rang]=rang* et *tab[i]=0 pour i!=rang*.

1. Écrire un programme MPI implementant une communication all-to-all (via l'intermédiaire de MPI_Bcast) telle qu'à la fin, tous les processus possèdent le même tableau.

## Produit Matrice-Vecteur

1. Implémentez le produit Matrice-Vecteur sur un anneau avec copie du vecteur.
2. Implémentez le produit Matrice-Vecteur sur un anneau avec circulation du vecteur.

## Produit Matrice-Matrice

1. Implémentez le produit Matrice-Matrice sur un anneau avec circulation des lignes.