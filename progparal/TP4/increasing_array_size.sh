#!/bin/bash

> increasing_array_size.dat

for i in {10000..100000..10000}
	do
		echo "Processing with array's size : $i ..."
		OUTPUT="$(./quicksort 0 $i)"
        echo "$OUTPUT"
		echo "$OUTPUT" >> increasing_array_size.dat
done

"$(gnuplot -c draw_gnuplot.gp increasing_array_size.dat")