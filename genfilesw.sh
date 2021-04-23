#!/usr/bin/env bash
g++ wgpert.cpp -o wgpert
mkdir $4
p=$(echo "1.0 / sqrt($2)" | bc -l)
for ((i = 0; i < $1; i++)); do
    mkdir $4/graph$i
    cp wgpert $4/graph$i
    cd $4/graph$i
    ./wgpert $2 $p graph$i $3
    rm wgpert
    cd ../..
done
rm wgpert