#!/usr/bin/env python
rank = [0 for i in range(4)]
for _ in range(3):
    a, b = map(int, input().split())
    rank[a - 1] += 1
    rank[b - 1] += 1
print('YES' if sorted(rank) == [1, 1, 2, 2] else 'NO')
