#!/bin/bash

> exercice1_3_graph.dat

for i in {1000000..30000000..1000000}
	do
		echo "Processing $i ..."
		OUTPUT="$(./exercice1_omp $i)"
		echo "$OUTPUT" >> exercice1_3_graph.dat
	done

#TODO: Faire génerer le gnuplot ici
