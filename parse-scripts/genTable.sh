#!/bin/bash

#Get rid of the time from here because the library reports the 'elapsed' time

#find . -name 'out.dat*' -print | sort -n > tmp
#cat tmp | xargs grep seconds | cut -d "=" -f 2 | sed 's/[ \t]*//g' > .time

if [ -z "$1" ] ; then 
    echo "Usage: $0 <result directory>"
    exit 1
fi

execDir=`dirname $0`

find $1 -type d | egrep -o '([[:digit:]]+_){6}[[:digit:]]+' | sort > .id

cat .id | xargs -I{} grep cores $1/{}/info | cut -d ":" -f 2 | sed 's/[ \t]*//g' > .cores
cat .id | xargs -I{} grep nodes $1/{}/info | cut -d ":" -f 2 |sed 's/[ \t]*//g'  > .nodes
cat .id | xargs -I{} grep MHz $1/{}/info | sed -n '1~16p' | cut -d ":" -f 2 > .freq

paste -d ' ' .id .freq .nodes .cores > .info

#Now go to each directory and run the genData and parse_rapl scripts locally

rm -f clamp_data node_data.R.*
i=0
for d in `cat .id | xargs -I{} echo $1/{}`
do
    i=`expr $i + 1`
	sh $execDir/parsePowerData.sh $d `printf "%04u" $i`
	#node_data.R.$i should now exist
done;
$execDir/parse_rapl.sh `ls node_data.R.*|sort -g` > row.out
#row.out should now exist

paste -d ' ' .info clamp_data row.out  > .final-table

sed '1 i id freq nodes cores pkg-clamp-0 pkg-clamp-1 dram-clamp-0 dram-clamp-1 avg-time avg-pkg-0 avg-pp0-0 avg-dram-0 avg-pkg-1 avg-pp0-1 avg-dram-1 tot-pkg-0 tot-pp0-0 tot-dram-0 tot-pkg-1 tot-pp0-1 tot-dram-1' .final-table > table.out

rm -f .id .freq .cores .nodes .final-table node_data.R.*
