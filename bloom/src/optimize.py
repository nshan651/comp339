#!/usr/bin/env python
# Optimize bits(m) and hashes(k)

import math

m = 1000000
n = 33765

prob_target = 0.000001

k_optim = (m / n) * math.log(2)
m_optim = (-n * math.log(prob_target)) / (math.log(2)**2)


# print(f'Optimal k: {k_optim}    Optimal m: {m_optim}')

min_m = float('inf')
min_k = 0.0
k = 1.0

while (k < 3.0):
    numerator = (-k * n)
    denominator = math.log(1.0 - (1/n)**(1.0/k))

    curr_m = numerator / denominator

    if curr_m < min_m:
        min_m = curr_m
        min_k = k

    k+=1.0

print(f'Optimal k: {min_k}    Optimal m: {min_m}')
