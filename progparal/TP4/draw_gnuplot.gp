#!/usr/bin/gnuplot -persist
set title "Quicksort duration" font ",14" textcolor rgbcolor "royalblue"
set pointsize 1
set autoscale
set xlabel "Data size"
set ylabel "Duration in seconds"
plot ARG1 using 2:1 with linespoint
pause -1
#TODO modifier le pause -1 dégueulasse ...............