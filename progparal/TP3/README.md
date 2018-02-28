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

1. 
