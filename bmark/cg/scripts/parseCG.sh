#!/bin/bash


find . -name 'out.dat*' -print | sort -n > tmp
cat tmp | xargs grep seconds | cut -d "=" -f 2 | sed 's/[ \t]*//g' > .time

find . -name 'info*' -print | sort -n > tmp2
cat tmp2 | xargs grep cores | cut -d ":" -f 3 | sed 's/[ \t]*//g' > .cores
cat tmp2 | xargs grep nodes | cut -d ":" -f 3 |sed 's/[ \t]*//g'  > .nodes
cat tmp2 | xargs grep MHz | sed -n '1~16p' | cut -d ":" -f 3 > .freq

paste -d ' ' .freq .nodes .cores .time > .table
sed '1 i freq nodes cores time' .table > table.out

rm tmp
rm tmp2
rm .freq .cores .nodes .time .table

