#!/usr/bin/env bash
g++ uwgpert.cpp -o uwgpert
for ((s = 100; s < 1100; s+=100)); do
	mkdir size$s
	for ((i = 0; i < $1; i++)); do
		p=$(echo "1.0 / sqrt(($i + 1) * $s)" | bc -l)
		mkdir size$s/graph$i
    	cp uwgpert size$s/graph$i
    	cd size$s/graph$i
    	./uwgpert $s $p graph$i $3
    	rm uwgpert
    	cd ../..
	done
done
rm uwgpert