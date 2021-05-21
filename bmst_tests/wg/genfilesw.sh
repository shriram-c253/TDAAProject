#!/usr/bin/env bash
g++ wgpert.cpp -o wgpert
for ((s = 100; s < 1100; s+=100)); do
	mkdir size$s
	for ((i = 0; i < $1; i++)); do
		p=$(echo "2.0 / sqrt(($i + 1) * $s)" | bc -l)
    	mkdir size$s/graph$i
    	cp wgpert size$s/graph$i
    	cd size$s/graph$i
    	./wgpert $s $p graph$i $3
    	rm wgpert
    	cd ../..
    done
done
rm wgpert