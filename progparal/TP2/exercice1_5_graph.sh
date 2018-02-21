#!/bin/bash

> exercice1_5_graph.dat

for i in {1..20}
	do
		echo "Processing with $i threads ..."
		OUTPUT="$(./exercice1_omp 85000000 $i)"
		echo "$OUTPUT" >> exercice1_5_graph.dat
	done

#TODO: Faire génerer le gnuplot ici
