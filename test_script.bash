make clean
make
time_results=()
weight_results=()
for graph_folder in bmst_tests/wg/size*
do
    folder_name=$(echo $graph_folder | cut --delimiter="/" --fields=3)
    vertex_count=${folder_name#"size"} 
    for sub_folder in $graph_folder/*
    do
        echo "Running on folder $sub_folder"
        g_num=$(echo $sub_folder | cut --delimiter="/" --fields=4)
        g_num=${g_num#"graph"}
        running_times3=()
        running_times4=()
        avg_edge_cnt=0
        avg_bmst_wt3=0
        avg_bmst_wt4=0
        avg_kruskal_time=0
        avg_kruskal_wt=0
        avg_prim_time=0
        avg_prim_wt=0
        avg_mst_wt=0
        for file in $sub_folder/*
        do
            echo "Running on graph $file"
            #a1=`date +%s.%N`
            output=($(./bmst $file))
            declare -p output #is now an array
            #a2=`date +%s.%N`
            avg_edge_cnt=$((avg_edge_cnt+output[4]))
            avg_bmst_wt3=$(echo "$avg_bmst_wt3 + ${output[1]}" | bc -l)
            avg_bmst_wt4=$(echo "$avg_bmst_wt4 + ${output[3]}" | bc -l)
            avg_kruskal_time=$(echo "$avg_kruskal_time + ${output[5]}" | bc -l)
            avg_kruskal_wt=$(echo "$avg_kruskal_wt + ${output[6]}" | bc -l)
            avg_prim_time=$(echo "$avg_kruskal_time + ${output[7]}" | bc -l)
            avg_prim_wt=$(echo "$avg_kruskal_wt + ${output[8]}" | bc -l)
            avg_mst_wt=$(echo "$avg_mst_wt + ${output[9]}" | bc -l)
            #time_taken=$(echo "${}" | bc -l)
            running_times3+=(${output[0]})
            running_times4+=(${output[2]})
            #validity=$(echo "$exec_string != -1" | bc -l)
            #echo $validity
            #if [[ $validity == 1 ]] 
            #then
                #time_taken=$(echo "$a2-$a1" | bc -l)
                #running_times+=($time_taken)
            #fi
        done
        avg_running_time3=0
        total_size=${#running_times3[*]}
        for x in ${running_times3[*]}
        do
            avg_running_time3=$(echo "$avg_running_time3 + $x" | bc -l)
        done
        std3=0
        for x in ${running_times3[*]}
        do
            std3=$(echo "$std3 + ($avg3-$x)*($avg3-$x)" | bc -l)
        done
        avg_running_time4=0
        for x in ${running_times4[*]}
        do
            avg_running_time4=$(echo "$avg_running_time4 + $x" | bc -l)
        done
        std4=0
        for x in ${running_times4[*]}
        do
            std4=$(echo "$std4 + ($avg4-$x)*($avg4-$x)" | bc -l)
        done
        avg_edge_cnt=$(echo "$avg_edge_cnt / $total_size" | bc -l)
        avg_running_time3=$(echo "$avg_running_time3 / $total_size" | bc -l)
        avg_running_time4=$(echo "$avg_running_time4 / $total_size" | bc -l)
        std3=$(echo "sqrt($std3 / $total_size)" | bc -l)
        std4=$(echo "sqrt($std4 / $total_size)" | bc -l)
        avg_bmst_wt3=$(echo "$avg_bmst_wt3 / $total_size" | bc -l)
        avg_bmst_wt4=$(echo "$avg_bmst_wt4 / $total_size" | bc -l)
        avg_kruskal_time=$(echo "$avg_kruskal_time / $total_size" | bc -l)
        avg_kruskal_wt=$(echo "$avg_kruskal_wt / $total_size" | bc -l)
        avg_prim_time=$(echo "$avg_prim_time / $total_size" | bc -l)
        avg_prim_wt=$(echo "$avg_prim_wt / $total_size" | bc -l)
        avg_mst_wt=$(echo "$avg_mst_wt / $total_size" | bc -l)
        time_result=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$avg_running_time3|$std3|$avg_running_time4|$std4|$avg_kruskal_time|$avg_prim_time|")
        wt_res=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$avg_bmst_wt3|$avg_bmst_wt4|$avg_kruskal_wt|$avg_prim_wt|$avg_mst_wt|")
        time_results+=($time_result)
        weight_results+=($wt_res)
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
for res in ${time_results[*]}
do
    echo $res
done

for res in ${weight_results[*]}
do
    echo $res
done