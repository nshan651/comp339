#!/bin/sh
# Calculate the optimal bits (m) and hashes (k) to use

for k in $(seq 1 4)
do
    for m in $(seq 1 10)
    do
        echo "./bin/bloom -m $m -k $k"
        ./bin/bloom -m "$m" -k "$k"
    done
done
