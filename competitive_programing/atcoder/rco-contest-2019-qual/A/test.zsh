#! /usr/bin/env zsh
g++ main.comp.cpp -O3
find test -name output* -delete
for f in test/input*; do
    time ./a.out < $f > ${f/input/output}
    java Judge $f ${f/input/output};
done
