#!/usr/bin/env sh
for f in test/in/*;
do
    ./a.out < $f > /dev/null
done
