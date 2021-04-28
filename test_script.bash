make clean
make

for graph_folder in $(pwd)/wtd/*
do
    echo "Running on folder $graph_folder"
    for file in $graph_folder/*
    do
        echo "Running on graph $file"
        ./bmst  $file
    done
done
