set ylabel "Temps en nanoseconde"
set xlabel "Taille des donnees en Kilo octet"
set title "Evaluation du temps d'acces aux donnees sur un seul processeur"
set xtics 0,128,1536
set yrange [14:15]
plot "micro-benchmark-sequentiel-single-processor.dat" using 2:1 smooth unique