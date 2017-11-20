#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//
// Le temps d’accès moyen est de 0.002173 microsecondes lorsque la taille totale des données accédées est de 1988032 KO

#define MAX_TAILLE_DATA_KO 4096	// =4 Mo
#define CACHE_LINE_SIZE 32	// remplacez ici par la taille de votre ligne cache
int tab[(MAX_TAILLE_DATA_KO * 1024) / sizeof (int)];	// tableau des données accédées
int i;				// un compteur de boucle simple
int j;				// compteur pour repeter une expérience
int x;
int taille_data,		// qui correspond à la taille totale des données accédées en Ko
nbdonnee;			// = (taille_data * 1024) / sizeof(int)
struct timeval t1, t2;		// variables utilisées pour mesurer le temps d’exécution
int pas = CACHE_LINE_SIZE / sizeof (int);	// nombre de données de type int dans une ligne cache
float temps_acces_moyen;	//en microsecondes
void main ()
{
  int cls = CACHE_LINE_SIZE;
  for (taille_data = cls; taille_data <= MAX_TAILLE_DATA_KO * 1024;
    taille_data = taille_data + cls)
    {
      nbdonnee = (taille_data) / sizeof (int);
      for (i = 0; i < nbdonnee; i = i + pas)
      {			// boucle simple qui pré-charge les données dans le cache L1
        x = x + tab[i];
      }		// end for i
      gettimeofday (&t1, NULL);	// récupérer ici la valeur de l’horloge juste avant la boucle
      for (i = 0; i < nbdonnee; i = i + pas)
      {			// boucle qui accède aux lignes cache, avec un pas d’accès
        x = x + tab[i];
      }		// end for i
      gettimeofday (&t2, NULL);	// récupérer la valeur de l’horloge à la fin de la boucle
      // convertir le temps écoulé en microsecondes
      temps_acces_moyen =
      (float) ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec -
      t1.tv_usec) / (nbdonnee / pas);
      printf ("Le temps d’accès moyen est de %f microsecondes lorsque la taille totale des données accédées est de %d KO\n", temps_acces_moyen,
      taille_data);
    }				// endfor taille_data
  }				// end main
