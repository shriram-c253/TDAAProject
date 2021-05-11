make clean
make
result_array=()
for graph_folder in wtd/*
do
    folder_name=$(echo $graph_folder | cut --delimiter="/" --fields=2)
    count=${folder_name#"graph"}
    running_times=()
    echo "Running on folder $graph_folder"
    for file in $graph_folder/*
    do
        echo "Running on graph $file"
        a1=`date +%s.%N`
        exec_string=$(./bmst $file)
        a2=`date +%s.%N`
        validity=$(echo "$exec_string != -1" | bc -l)
        #echo $validity
        if [[ $validity == 1 ]] 
        then
            time_taken=$(echo "$a2-$a1" | bc -l)
            running_times+=($time_taken)
        fi
    done
    avg=0
    total_size=${#running_times[*]}
    for x in ${running_times[*]}
    do
        avg=$(echo "$avg + $x" | bc -l)
    done
    if [[ $total_size != 0 ]] 
    then
        avg=$(echo "$avg/$total_size" | bc -l)
        std=0
        for x in ${running_times[*]}
        do
            std=$(echo "$std + ($avg-$x)*($avg-$x)" | bc -l)
        done
        std=$(echo "$std / $total_size" | bc -l)
        result=$(echo "|$count|$avg|$std|$total_size|")
        result_array+=($result)
    else
        result=$(echo "|$count|0|0|26|")
        result_array+=($result)
    fi
done
for res in ${result_array[*]}
do
    echo $res
done
