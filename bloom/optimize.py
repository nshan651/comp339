#!/usr/bin/env python3
# Script to optimize bits (m) and hashes (k)
import math, sys
import subprocess as sp
import typing
import matplotlib.pyplot as plt
from tqdm import tqdm

min_m: int = sys.maxsize
min_k: int = 0
n: int = 123985 
#TODO: Derive this from the size of the words read from file
n: int = 120000
trial = []
target_fpos = 0.05

bits = []
probs = []
for k in range(2, 3):
    for m in tqdm(range(1015150, n, -1500)):
        f_prob: float = (1.0 - ((1.0 - 1.0/m)**(k*n))) ** k
        output = sp.check_output(
            f"./bin/bloom -m {m} -k {k} -s 'Hello,No Way,ge'", 
            shell=True
        )
        trial = output.decode().rstrip().split(" ")

        not_in = 0
        for t in trial:
            if float(t) == -1.0:
                not_in+=1
        print(f"not in {not_in}") 
        probability = f_prob if not_in != len(trial) else 0

        probs.insert(0, probability)
        bits.insert(0, m)
        print(f"m: {m} k: {k} false_pos: {probability}")

print(probs)

### Line Plot

fig, ax = plt.subplots()
ax.plot(bits, probs)
ax.set(xlabel='bits (m)', ylabel='false probability (p)',
       title='Bloom Filter False Probabilities')
ax.grid()

# fig.savefig("test.png")
plt.show()
