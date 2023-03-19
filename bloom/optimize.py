#!/usr/bin/env python3
# Script to optimize bits (m) and hashes (k)

import math
import sys
import typing
from tqdm import tqdm

min_m: int = sys.maxsize
min_k: int = 0
#TODO: Derive this from the size of the words read from file
n: int = 120000

for k in tqdm(range(1, 5)):
    for m in tqdm(range(150000, 1000000)):
        prob: float = (1.0 - ((1.0 - 1.0/m)**(k*n))) ** k
        print(k)

