#! /usr/bin/env zsh
g++ main.comp.cpp -O3
find test -name *.out -delete
find test -name 'input*' | parallel './a.out < {} > {}.out'
cd ..
for f in review/test/*.out; do
    java Judge ${f%*.out} $f
done
