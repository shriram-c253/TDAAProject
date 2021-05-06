  
#!/usr/bin/env bash
g++ ./DisjointSetUnion.hpp ./Kruskals.hpp -o head
g++ ./main2.cpp ./DisjointSetUnion.cpp ./Kruskals.cpp -o main

for ((i = 2; i <= 7; i++)); do
    main $i
done