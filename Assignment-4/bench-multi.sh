#!/bin/bash

echo $(date)
echo "starting matrix multiply"

mkdir -p data/bench-multi-$2

for i in $(eval echo {1..${1}})
do
    /usr/bin/time -f "CPU: %P\n" -o data/bench-multi-$2/mm-${i}-cpu.out ./bench $2 $2 $2 0 > data/bench-multi-$2/mm-${i}.out& 
    pids[${i}]=$!
    echo $(date)
done

echo "waiting for multiplies"
# wait for all pids
for pid in ${pids[*]}; do
    wait $pid
done
echo $(date)

echo $(ps)

#kill $monitor
