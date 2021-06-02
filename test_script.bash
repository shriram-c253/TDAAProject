# make clean
# make
avg_time_results=()
abs_std_time_results=()
std_time_results=()
weight_results=()
for graph_folder in bmst_tests/wg/size*; do
    folder_name=$(echo $graph_folder | cut --delimiter="/" --fields=3)
    vertex_count=${folder_name#"size"}
    for sub_folder in $graph_folder/*; do
        echo "Running on folder $sub_folder"
        g_num=$(echo $sub_folder | cut --delimiter="/" --fields=4)
        g_num=${g_num#"graph"}
        running_times3=()
        running_times4=()
        running_times_k=()
        running_times_p=()
        avg_edge_cnt=0
        avg_bmst_wt3=0
        avg_bmst_wt4=0
        avg_kruskal_time=0
        avg_kruskal_wt=0
        avg_prim_time=0
        avg_prim_wt=0
        avg_mst_wt=0
        for file in $sub_folder/*; do
            echo "Running on graph $file"
            #a1=`date +%s.%N`
            output=($(./bmst $file))
            declare -p output #is now an array
            #a2=`date +%s.%N`
            avg_edge_cnt=$((avg_edge_cnt + output[4]))
            avg_bmst_wt3=$(echo "$avg_bmst_wt3 + ${output[1]}" | bc -l)
            avg_bmst_wt4=$(echo "$avg_bmst_wt4 + ${output[3]}" | bc -l)
            avg_kruskal_wt=$(echo "$avg_kruskal_wt + ${output[6]}" | bc -l)
            avg_prim_wt=$(echo "$avg_prim_wt + ${output[8]}" | bc -l)
            avg_mst_wt=$(echo "$avg_mst_wt + ${output[9]}" | bc -l)
            #time_taken=$(echo "${}" | bc -l)
            running_times3+=(${output[0]})
            running_times4+=(${output[2]})
            running_times_k+=(${output[5]})
            running_times_p+=(${output[7]})
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
        for x in ${running_times3[*]}; do
            avg_running_time3=$(echo "$avg_running_time3 + $x" | bc -l)
        done
        avg_running_time3=$(echo "$avg_running_time3 / $total_size" | bc -l)
        std3=0
        for x in ${running_times3[*]}
        do
            std3=$(echo "$std3 + ($avg_running_time3-$x)*($avg_running_time3-$x)" | bc -l)
        done
        avg_running_time4=0
        for x in ${running_times4[*]}; do
            avg_running_time4=$(echo "$avg_running_time4 + $x" | bc -l)
        done
        avg_running_time4=$(echo "$avg_running_time4 / $total_size" | bc -l)
        std4=0
        for x in ${running_times4[*]}
        do
            std4=$(echo "$std4 + ($avg_running_time4-$x)*($avg_running_time4-$x)" | bc -l)
        done
        avg_kruskal_time=0
        for x in ${running_times_k[*]}
        do
            avg_kruskal_time=$(echo "$avg_kruskal_time + $x" | bc -l)
        done
        avg_kruskal_time=$(echo "$avg_kruskal_time / $total_size" | bc -l)
        stdk=0
        for x in ${running_times_k[*]}
        do
            stdk=$(echo "$stdk + ($avg_kruskal_time-$x)*($avg_kruskal_time-$x)" | bc -l)
        done
        avg_prim_time=0
        for x in ${running_times_p[*]}
        do
            avg_prim_time=$(echo "$avg_prim_time + $x" | bc -l)
        done
        avg_prim_time=$(echo "$avg_prim_time / $total_size" | bc -l)
        stdp=0
        for x in ${running_times_p[*]}
        do
            stdp=$(echo "$stdp + (($avg_prim_time-$x)*($avg_prim_time-$x))" | bc -l)
        done
        avg_edge_cnt=$(echo "$avg_edge_cnt / $total_size" | bc -l)
        std3=$(echo "sqrt($std3 / $total_size)" | bc -l)
        std4=$(echo "sqrt($std4 / $total_size)" | bc -l)
        avg_bmst_wt3=$(echo "$avg_bmst_wt3 / $total_size" | bc -l)
        avg_bmst_wt4=$(echo "$avg_bmst_wt4 / $total_size" | bc -l)
        stdk=$(echo "sqrt($stdk / $total_size)" | bc -l)
        avg_kruskal_wt=$(echo "$avg_kruskal_wt / $total_size" | bc -l)
        stdp=$(echo "sqrt($stdp / $total_size)" | bc -l)
        avg_prim_wt=$(echo "$avg_prim_wt / $total_size" | bc -l)
        avg_mst_wt=$(echo "$avg_mst_wt / $total_size" | bc -l)
        avg_time_result=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$avg_running_time3|$avg_running_time4|$avg_kruskal_time|$avg_prim_time|")
        abs_std_time_result=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$std3|$std4|$stdk|$stdp|")
        std_time_result=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$(echo "($std3/$avg_running_time3)" | bc -l)|$(echo "($std4/$avg_running_time4)" | bc -l)|$(echo "($stdk/$avg_kruskal_time)" | bc -l)|$(echo "($stdp/$avg_prim_time)" | bc -l)|")
        wt_res=$(echo "|$vertex_count|$g_num|$avg_edge_cnt|$avg_bmst_wt3|$avg_bmst_wt4|$avg_kruskal_wt|$avg_prim_wt|$avg_mst_wt|")
        avg_time_results+=($avg_time_result)
        std_time_results+=($std_time_result)
        abs_std_time_results+=($abs_std_time_result)
        weight_results+=($wt_res)
        echo $avg_time_result
        echo $std_time_result
        echo $wt_res
    done
done
echo 
echo
for res in ${avg_time_results[*]}
do
    echo $res
done
echo
echo
for res in ${std_time_results[*]}
do
    echo $res
done
echo
echo
for res in ${abs_std_time_results[*]}
do
    echo $res
done
echo
echo
for res in ${weight_results[*]}
do
    echo $res
done
