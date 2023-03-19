#!/bin/sh
# Calculate the optimal bits (m) and hashes (k) to use

MAX_K=4
# MAX_M=1000000
MAX_M=150100
MIN_M=150000

OPTIM_M="$MAX_M"
OPTIM_K="$MAX_K"

for k in $(seq 1 "$MAX_K")
do
    echo "k is $k"
    for m in $(seq "$MIN_M" "$MAX_M")
    do
        # ./bin/bloom -m "$m" -k "$k"
        # Run bloom and capture the output
        output=$(./bin/bloom -m "$m" -k "$k")
        first_line=$(echo "$output" | head -n 1)
        second_line=$(echo "$output" | head -n 2 | tail -n 1)
        third_line=$(echo "$output" | tail -n 1)
        if [ "$first_line" = "Not in Bloom Filter" ] && [ "$second_line" = "Not in Bloom Filter" ] && [ "$third_line" = "Not in Bloom Filter" ]; then
            echo "None in filter"
            if [ "$k" -le "$OPTIM_K" ] && [ "$m" -le "$OPTIM_M" ]; then
                OPTIM_K=$k
                OPTIM_M=$m
                echo "New m and k found!"
            fi
            echo "k = $k  m = $m."
            break
        fi
    done
done
echo "Done."
echo "Optimal m: $OPTIM_M Optimal k: $OPTIM_K" > optimal.txt
