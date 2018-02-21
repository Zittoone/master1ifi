set ylabel "Temps en nanoseconde"
set xlabel "Taille des donnees en Kilo octet"
set title "Evaluation du temps d'acces aux donnees en memoire centrale"
set xtics 0,128,1536
set yrange [14:35]
plot "micro-benchmark-sequentiel-memoire.dat" using 2:1 smooth unique