#!/bin/bash

#Get rid of the time from here because the library reports the 'elapsed' time

#find . -name 'out.dat*' -print | sort -n > tmp
#cat tmp | xargs grep seconds | cut -d "=" -f 2 | sed 's/[ \t]*//g' > .time



find . -name 'info*' -print | sort -n > tmp2
cat tmp2 | xargs grep cores | cut -d ":" -f 3 | sed 's/[ \t]*//g' > .cores
cat tmp2 | xargs grep nodes | cut -d ":" -f 3 |sed 's/[ \t]*//g'  > .nodes
cat tmp2 | xargs grep MHz | sed -n '1~16p' | cut -d ":" -f 3 > .freq

paste -d ' ' .freq .nodes .cores > .info

#Now go to each directory and run the genData and parse_rapl scripts locally

for d in `ls | grep 2012`
do
	cd $d
	sh ../parsePowerData.sh
	#node_data.R should now exist
	../parse_rapl.sh node_data.R
	#row.out should now exist
	cd ..
done;



find . -name 'row.out*' -print > tmp3
cat tmp3 |xargs sed 's/$//g' >> .power-table

find . -name 'clamp_data*' -print > tmp4
cat tmp4 |xargs cat >> .clamp-table


paste -d ' ' .info .clamp-table .power-table > .final-table

sed '1 i freq nodes cores pkg-clamp-0 pkg-clamp-1 dram-clamp-0 dram-clamp-1 avg-time avg-pkg-0 avg-pp0-0 avg-dram-0 avg-pkg-1 avg-pp0-1 avg-dram-1 tot-pkg-0 tot-pp0-0 tot-dram-0 tot-pkg-1 tot-pp0-1 tot-dram-1' .final-table > table.out

rm tmp2 tmp3 tmp4
rm .freq .cores .nodes .power-table .final-table .clamp-table

