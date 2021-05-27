make clean
make
result_array=()
for graph_folder in bmst_tests/wg/size*
do
    folder_name=$(echo $graph_folder | cut --delimiter="/" --fields=3)
    vertex_count=${folder_name#"size"} 
    for sub_folder in $graph_folder/*
    do
        echo "Running on folder $sub_folder"
        g_num=$(echo $sub_folder | cut --delimiter="/" --fields=4)
        g_num=${g_num#"graph"}
        running_times=()
        max_d=0 #maximum degree. Take maximum here.
        avg_edge_cnt=0
        avg_kruskal_time=0
        avg_prim_time=0
        avg_edge_wt=0
        avg_prim_edge_wt=0
        for file in $sub_folder/*
        do
            echo "Running on graph $file"
            #a1=`date +%s.%N`
            output=($(./bmst $file))
            declare -p output #is now an array
            #a2=`date +%s.%N`
            max_d=$(echo $((output[1]>max_d?output[1]:max_d)))
            avg_edge_cnt=$((avg_edge_cnt+output[2]))
            avg_edge_wt=$(echo "$avg_edge_wt + ${output[3]}" | bc -l)
            avg_prim_edge_wt=$(echo "$avg_prim_edge_wt + ${output[6]}" | bc -l)
            avg_kruskal_time=$(echo "$avg_kruskal_time + ${output[4]}" | bc -l)
            avg_prim_time=$(echo "$avg_prim_time + ${output[5]}" | bc -l)
            #time_taken=$(echo "${}" | bc -l)
            running_times+=(${output[0]})
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
        std=0
        for x in ${running_times[*]}
        do
            std=$(echo "$std + ($avg-$x)*($avg-$x)" | bc -l)
        done
        std=$(echo "sqrt($std / $total_size)" | bc -l)
        avg_prim_edge_wt=$(echo "$avg_prim_edge_wt / $total_size" | bc -l)
        avg_prim_time=$(echo "$avg_prim_time / $total_size" | bc -l)
        avg_kruskal_time=$(echo "$avg_kruskal_time / $total_size" | bc -l)
        avg_edge_wt=$(echo "$avg_edge_wt / $total_size" | bc -l)
        avg_edge_cnt=$(echo "$avg_edge_cnt / $total_size" | bc -l)
        result=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$max_d|$avg|$avg_kruskal_time|$avg_prim_time|$avg|$avg_edge_wt|$avg_prim_edge_wt|")
        
    done
    # if [[ $total_size != 0 ]] 
    # then
    #     avg=$(echo "$avg/$total_size" | bc -l)
    #     std=0
    #     for x in ${running_times[*]}
    #     do
    #         std=$(echo "$std + ($avg-$x)*($avg-$x)" | bc -l)
    #     done
    #     std=$(echo "$std / $total_size" | bc -l)
    #     avg_edge_cnt=$(echo "$avg_edge_cnt / $num_pert" | bc -l)
    #     result=$(echo "|$count|$vertex_count|$avg_edge_cnt|$max_d|$avg|$std|")
    #     result_array+=($result)
    # else
    #     result=$(echo "|$count||0|0|26|")
    #     result_array+=($result)
    # fi
done
for res in ${result_array[*]}
do
    echo $res
done
