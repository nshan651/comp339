#!/usr/bin/env python3
# Script to optimize bits (m) and hashes (k)

import math
import sys, subprocess as sp
import typing
from tqdm import tqdm

min_m: int = sys.maxsize
min_k: int = 0
#TODO: Derive this from the size of the words read from file
n: int = 120000
f_pos = []

for k in range(1, 2):
    for m in range(1000050, 1000000, -50):
        prob: float = (1.0 - ((1.0 - 1.0/m)**(k*n))) ** k
        output = sp.check_output(
            f"./bin/bloom -m {m} -k {k} -s 'Hello,No Way,ge'", 
            shell=True
        )
        f_pos = output.decode().strip().split(" ")
        # print(k)

print(f_pos)
