  
#!/usr/bin/env bash
g++ ./Prims.hpp -o head
g++ ./main2.cpp ./Prims.cpp -o main

for ((i = 1; i <= 7; i++)); do
    main $i
done
rm head
rm main