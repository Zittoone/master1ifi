#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main (){

  const int L1_CACHE_LINE_SIZE = 64; //sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  const int L1_CACHE_SIZE_KB   = 32; //sysconf(_SC_LEVEL1_DCACHE_SIZE) / 1024;

  /*
    Redondant car cela serait très compliqué de maintenanir une architecture
    avec différentes tailles de ligne de cache
  */
  //const int L2_CACHE_LINE_SIZE = sysconf(_SC_LEVEL2_CACHE_LINESIZE);
  const int L2_CACHE_SIZE_KB   = 512; //sysconf(_SC_LEVEL2_CACHE_SIZE) / 1024;

  /*
    Redondant car cela serait très compliqué de maintenanir une architecture
    avec différentes tailles de ligne de cache (idem que pour L2)
  */
  //const int L3_CACHE_LINE_SIZE = sysconf(_SC_LEVEL3_CACHE_LINESIZE);
  const int L3_CACHE_SIZE_KB   = 0; // sysconf(_SC_LEVEL3_CACHE_SIZE) / 1024;

  //printf("L1 %dKb, L2 %dKb, L3 %dKb\n", L1_CACHE_SIZE_KB, L2_CACHE_SIZE_KB, L3_CACHE_SIZE_KB);

  /*
    /!\ IMPORTANT /!\

    On utilisera donc désormais L1_CACHE_LINE_SIZE comme référentiel de taille
    de ligne de cache peut importe le niveau de cache. Explication plus haut.

    /!\ IMPORTANT /!\
  */

  int MAX_TAILLE_DATA_KO = 0;

  /*
    Afin d’évaluer les temps d’accès moyens à tous les niveaux de caches intermédiaires (L2, L3, etc), le
    micro-benchmark doit être paramétré pour que les tailles des données accédées soient de plus en plus grandes.
    Précisément, il faut que la taille maximale (paramètre MAX_TAILLE_DATA_KO) des données accédées soit au
    minimum égale au double de la capacité du dernier niveau de cache de votre CPU (L2 ou L3, tout dépend du
    dernier niveau de cache de votre machine de test). Par exemple, si votre dernier niveau de cache est L2 avec
    une capacité de C, la valeur du paramètre MAX_TAILLE_DATA_KO doit dépasser 2C.
  */

  if(L3_CACHE_SIZE_KB != 0){
    MAX_TAILLE_DATA_KO = (L3_CACHE_SIZE_KB * 3);
  } else if(L2_CACHE_SIZE_KB != 0){
    MAX_TAILLE_DATA_KO = (L2_CACHE_SIZE_KB * 3);
  } else if(L1_CACHE_SIZE_KB != 0){
    MAX_TAILLE_DATA_KO = (L1_CACHE_SIZE_KB * 3);
  } else {
    return EXIT_FAILURE;
  }

  /*
    PROCEDURE DE TEST DE PERFORMANCE DE LA HIERARCHIE MEMOIRE

    Accéder à des données de plus en plus importante pour utiliser le cache L1, puis L2, etc.
    Mesurer le temps moyen pour chaque quantité de données et output "taille_data : temps_acces_moyen"
  */

  // Gestion du temps d'execution
  struct timespec start, stop;

  // Variables paramètres

  int tab[(MAX_TAILLE_DATA_KO * 1024) / sizeof (int)];	// tableau des données accédées

  int i;
  for(i = 0; i < (MAX_TAILLE_DATA_KO * 1024) / sizeof(int); i++){
    tab[i] = i;
  }

  int x,j; // Variable permettant de forcer l'affectation de valeur
  int taille_data,		// qui correspond à la taille totale des données accédées en octets
  nbdonnee, nbrepetition;			// = (taille_data * 1024) / sizeof(int)
  double temps_acces_moyen;	//en nanosecondes
  int pas = 1;
  int cls = L1_CACHE_LINE_SIZE;

  nbrepetition = 10;

  // Incrémentation en octets
  for (taille_data = cls; taille_data <= MAX_TAILLE_DATA_KO * 1024; taille_data = taille_data + cls) {

    nbdonnee = taille_data / sizeof(int);

    for (i = 0; i < nbdonnee; i += pas) {			//boucle simple qui précharge les données dans le cache
      x = x + tab[i];
    }

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);

    for (j=0; j < nbrepetition; j++){ // boucle de répétiton
      for (i = 0; i < nbdonnee; i += pas) {			// boucle qui accède aux lignes cache, avec un pas d’accès
        x = x + tab[i];
      }
    }

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &stop);

    // convertir le temps écoulé en microsecondes
    temps_acces_moyen = ((double)(stop.tv_sec - start.tv_sec) * 1.0e9 + (double)(stop.tv_nsec - start.tv_nsec)) / ((nbdonnee / pas) * nbrepetition);
    printf ("%f : %d\n", temps_acces_moyen, taille_data / 1024);

  }

  return EXIT_SUCCESS;
}
