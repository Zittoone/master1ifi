# TP3 (OpenMP et Préfixe Parallèle)

## Exercice 1 (Parallel regions) 

1. On remarque que lorsque l'on change le nombre de threads, une région parallèle est executée n fois (n étant le nombre de threads).

2. On remarque que le section parallèle ne prends pas en compte la boucle for suivante.

3. On remarque maintenant que cela s'applique à tout le bloc.
	```bash
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside2
	```

4. On remarque qu'avec l'ajout de `#pragma omp for` au dessus de la boucle for et on passe donc d'un parallélisme de contrôle à un parallélisme de données.
	```bash
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	Execution de la méthode parallelRegionForInside1
	Execution de la méthode parallelRegionForInside2
	```

## Exercice 2 (Portée lexicale et dynamique)

1. La valeur globale en sortie est aléatoire, l'accès concurrent à la même valeur par plusieurs threads pose cette erreur.

2. Le fait de déclarer la variable comme étant privée dans le bloc n'affectera pas la vraie variable globale pour toutes modifications éffectuées.

3. La portée du private est une portée lexicale, elle ne va pas en profondeur dans les fonctions (la variable globale est bien modifiée par la méthode `void privateScope2_sub(void)` appelée dans `void privateScope2(void)`.

## Exercice 3 (Parallel prefix)
