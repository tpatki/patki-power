#!/bin/bash

#Get rid of the time from here because the library reports the 'elapsed' time

#find . -name 'out.dat*' -print | sort -n > tmp
#cat tmp | xargs grep seconds | cut -d "=" -f 2 | sed 's/[ \t]*//g' > .time

if [ -z "$1" ] ; then 
    echo "Usage: $0 <result directory>"
    exit 1
fi

execDir=`dirname $0`

find $1 -name 'info*' -print | sort -n > tmp2
cat tmp2 | xargs grep cores | cut -d ":" -f 3 | sed 's/[ \t]*//g' > .cores
cat tmp2 | xargs grep nodes | cut -d ":" -f 3 |sed 's/[ \t]*//g'  > .nodes
cat tmp2 | xargs grep MHz | sed -n '1~16p' | cut -d ":" -f 3 > .freq

paste -d ' ' .freq .nodes .cores > .info

#Now go to each directory and run the genData and parse_rapl scripts locally

rm -f clamp_data node_data.R.*
i=0
for d in `find $1 -name '2012*'`
do
    i=`expr $i + 1`
	sh $execDir/parsePowerData.sh $d `printf "%04u" $i`
	#node_data.R.$i should now exist
done;
$execDir/parse_rapl.sh `ls node_data.R.*|sort -g` > row.out
#row.out should now exist

paste -d ' ' .info clamp_data row.out  > .final-table

sed '1 i freq nodes cores pkg-clamp-0 pkg-clamp-1 dram-clamp-0 dram-clamp-1 avg-time avg-pkg-0 avg-pp0-0 avg-dram-0 avg-pkg-1 avg-pp0-1 avg-dram-1 tot-pkg-0 tot-pp0-0 tot-dram-0 tot-pkg-1 tot-pp0-1 tot-dram-1' .final-table > table.out

rm tmp2 tmp3 tmp4
rm .freq .cores .nodes .final-table node_data.R.*

