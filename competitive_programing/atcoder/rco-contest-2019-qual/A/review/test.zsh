#! /usr/bin/env zsh
g++ main.comp.cpp -O3
find ./test -name '*.out' -delete
find ./test -name 'input*' | parallel './a.out < {} > {}.out'
cd ..
sum=0
for f in review/test/*.out; do
    score=`java Judge ${f%*.out} $f`
    sum=`expr $score + $sum`
done
echo "point : $sum"
