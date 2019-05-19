#!/usr/bin/env python3
import math
N, K = map(int, input().split())
ans = 0
pows = []
for n in range(1, N + 1):
    p = n
    seq = 0
    while p < K:
        seq += 1
        p *= 2
    pows.append(seq)

s = sum(pows)
c = 0
for p in pows:
    c += pow(2, s - p)
print(c / (pow(2, s) * N))
