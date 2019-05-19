#!/usr/bin/env python3
S = input()

a, b = S[:2], S[2:]
a = int(a)
b = int(b)
if 0 < a and a <= 12 and 0 < b and b <= 12:
    print('AMBIGUOUS')
elif 0 < b and b <= 12:
    print('YYMM')
elif 0 < a and a <= 12:
    print('MMYY')
else:
    print('NA')
