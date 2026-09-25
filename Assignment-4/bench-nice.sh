#!/bin/bash

set -u

echo "$(date)"
echo "starting matrix multiply"

mkdir -p data/bench-nice

run_id=0



for i in $(eval echo {1..10})
do
    nice_value=0
    if [ $((run_id % 2)) -eq 1 ]; then
        nice_value=10
        echo "run ${run_id} will be nice ${nice_value}"
    fi

    nice -n "$nice_value" /usr/bin/time -f "CPU: %P\n" -o "data/bench-nice/mm-${run_id}-cpu.out" ./bench "500" "500" "500" 0 > "data/bench-nice/mm-${run_id}.out" &
    pids[${i}]=$!
    echo "started run ${run_id}: nice ${nice_value}"
    run_id=$((run_id + 1))
done

echo "waiting for multiplies"
for pid in "${pids[@]}"; do
    wait $pid
done
echo "$(date)"

echo "all multiplies complete"
