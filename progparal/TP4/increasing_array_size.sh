#!/bin/bash

nbthread=0

if [ ! -z "$2" ]
  then
    nbthread=$2
fi

> increasing_array_size_$1.dat

for i in {10000..100000..10000}
	do
		echo "Processing with array's size : $i ..."
		OUTPUT="$(./$1 $nbthread $i)"
        echo "$OUTPUT"
		echo "$OUTPUT" >> increasing_array_size_$1.dat
done

gnuplot --persist -c draw_gnuplot.gp increasing_array_size_$1.dat