#include <time.h>

#define N 100000

int main(void) {

    float x, y, z, t, perf;
    time_t t1, t2;
    int tempsexec, i;
    gettimeofday(&t1, NULL); // récupérer la valeur
    for(i = 0; i < N; i++) {
        x+y;
        x+t;
        x+z;
        t+y;
        y+x;
    }

    gettimeofday(&2, NULL);
    tempsexec = t2.tv_usec - t1.tv_usec;
}
gettimeofday(&t2, NULL); // récupérer la valeur de
tempexec= t2.tv_usec - t1.tv_usec; // attention, il
l’horloge juste avant la boucle de calculs
itération de boucle
l’horloge juste après la boucle de calculs
faut additionner les secondes écoulées et
// tout convertir en microsecondes
perf= (float) (N*5)/tempsexec; // N*5 est le nombre d’additions flottantes exécutées par la boucle
printf("Le nombre moyen d’additions flottantes par unité de temps (microsonde) est: \%f", perf);
