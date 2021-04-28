#!/usr/bin/env bash
g++ uwgpert.cpp -o uwgpert
mkdir $4
p=$(echo "1.0 / sqrt($2)" | bc -l)
for ((i = 0; i < $1; i++)); do
    mkdir $4/graph$i
    cp uwgpert $4/graph$i
    cd $4/graph$i
    ./uwgpert $2 $p graph$i $3
    rm uwgpert
    cd ../..
done
rm uwgpert