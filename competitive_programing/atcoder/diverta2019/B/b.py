#!/usr/bin/env python3
R, G, B, N = map(int, input().split())

cnt = 0
for r in range(N // R + 1):
    for g in range((N - r * R) // G + 1):
        b = N - r * R - G * g
        if b >= 0 and b % B == 0:
            cnt += 1
print(cnt)
