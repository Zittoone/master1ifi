Compilation avec gprof :
gcc -pg calcul.c -o calcul

Ensuite on lance le programme, ce qui produit : gmon.out
Donc on execute : gprof calcul gmon.out

Voir exemple output : exempleOutputGprof.txt

gcc calcul.c -o calculBase
time gcc -O1 calcul.c -o calculOpti1	=> 0,07s user 0,02s system 82% cpu 0,109 total
time gcc -O2 calcul.c -o calculOpti2	=> 0,09s user 0,02s system 87% cpu 0,124 total
time gcc -O3 calcul.c -o calculOpti3	=> 0,14s user 0,03s system 90% cpu 0,184 total
time gcc -O4 calcul.c -o calculOpti4 	=> 0,14s user 0,03s system 91% cpu 0,183 total

./calculBase 
Le temps d’éxecution est de 27,034,186.000000 microsecondes.

./calculOpti1
Le temps d’éxecution est de 14,899,292.000000 microsecondes.

./calculOpti2
Le temps d’éxecution est de 11,755,972.000000 microsecondes.

./calculOpti3
Le temps d’éxecution est de 11,740,406.000000 microsecondes.

./calculOpti4
Le temps d’éxecution est de 11,755,629.000000 microsecondes.

Meilleur rapport est O2.


#Utilisation ICC

time icc calcul.c -o calculBaseICC	=> 0,21s user 0,08s system 53% cpu 0,543 total
time icc -O1 calcul.c -o calculOpti1ICC => 0,11s user 0,07s system 50% cpu 0,343 total
time icc -O2 calcul.c -o calculOpti2ICC => 0,21s user 0,08s system 67% cpu 0,418 total
time icc -O3 calcul.c -o calculOpti3ICC => 0,21s user 0,08s system 60% cpu 0,476 total

./calculBaseICC 
Le temps d’éxecution est de 2,190,182.000000 microsecondes.

./calculOpti1ICC 
Le temps d’éxecution est de 11,670,861.000000 microsecondes.

./calculOpti2ICC
Le temps d’éxecution est de 2,186,761.000000 microsecondes.

./calculOpti3ICC
Le temps d’éxecution est de 1,911,844.000000 microsecondes.


#Utilisation profiler gcc

gcc -fprofile-generate calcul.c -o calculProfile => génère un fichier calcul.gcda à l'éxecution
./calculProfile 
Le temps d’éxecution est de 27173388.000000 microsecondes.

gcc -fprofile-use calcul.c -o calculProfile	=> utilise le fichier calcul.gcda
./calculProfile                            
Le temps d’éxecution est de 26690514.000000 microsecondes.

