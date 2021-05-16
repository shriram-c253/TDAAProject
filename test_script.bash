make clean
make
result_array=()
for graph_folder in euwtd/*
do
    folder_name=$(echo $graph_folder | cut --delimiter="/" --fields=2)
    count=${folder_name#"graph"}
    vertex_count=0
    avg_edge_cnt=0
    running_times=()
    max_d=0 #maximum degree. Take maximum here.
    num_pert=0 
    echo "Running on folder $graph_folder"
    for file in $graph_folder/*
    do
        if [[ $vertex_count == 0 ]] 
        then
            vertex_count=$(head -1 $file)
        fi
        echo "Running on graph $file"
        num_pert=$((num_pert+1))
        a1=`date +%s.%N`
        output=($(./bmst $file))
        declare -p output #is now an array
        a2=`date +%s.%N`
        max_d=$(echo $((output[0]>max_d?output[0]:max_d)))
        avg_edge_cnt=$((avg_edge_cnt+output[1]))
        time_taken=$(echo "$a2-$a1" | bc -l)
        running_times+=($time_taken)
        #validity=$(echo "$exec_string != -1" | bc -l)
        #echo $validity
        #if [[ $validity == 1 ]] 
        #then
            #time_taken=$(echo "$a2-$a1" | bc -l)
            #running_times+=($time_taken)
        #fi
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
        avg_edge_cnt=$(echo "$avg_edge_cnt / $num_pert" | bc -l)
        result=$(echo "|$count|$vertex_count|$avg_edge_cnt|$max_d|$avg|$std|")
        result_array+=($result)
    else
        result=$(echo "|$count||0|0|26|")
        result_array+=($result)
    fi
done
for res in ${result_array[*]}
do
    echo $res
done
