#!/usr/bin/env python
sum = 0
for _ in range(int(input())):
    x, u = input().split()
    sum += float(x) if u == "JPY" else 380000.0 * float(x)
print(sum)
