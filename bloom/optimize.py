#!/usr/bin/env python3
# Script to optimize bits (m) and hashes (k)

import math, sys
import subprocess as sp
import typing
# from tqdm import tqdm

min_m: int = sys.maxsize
min_k: int = 0
#TODO: Derive this from the size of the words read from file
n: int = 120000
f_pos = []
target_fpos = 0.05

for k in range(2, 3):
    for m in range(1000050, 0, -1):
        prob: float = (1.0 - ((1.0 - 1.0/m)**(k*n))) ** k
        output = sp.check_output(
            f"./bin/bloom -m {m} -k {k} -s 'Hello,No Way,ge'", 
            shell=True
        )
        f_pos = output.decode().rstrip().split(" ")
        for fp in f_pos:
            if float(fp) >= target_fpos:
                print(f"m: {m} k: {k} false_pos: {fp}")
                sys.exit(0) 
        # print(k)

print(f_pos)
