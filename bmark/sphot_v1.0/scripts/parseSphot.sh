#!/bin/bash


find . -name 'sweep.dat*' -print | sort -n > tmp
cat tmp | xargs grep CPU | cut -d ":" -f 3 | sed -n '1~2p'|sed 's/[ \t]*//g' > .time

#*******************************
#Uncomment the following if using papi 
#If you look at SweepCL.sh you will see that a
#dir name dir-papi is created as a subdirectory in the
#run directory. PAPI numbers are stored in dir-papi
#*******************************
#find . -name "dir-papi*" -print | sort -n > .fio

#curr=`pwd`;

#for d in `cat .fio`; do
#	cd /home/patki1/sweep/sweep3d-2.2b
#	cd $d
#	d1=`ls | grep fio1 | head -n 1`
#	cd $d1
#	echo `pwd`
#	
#	cat process_summary.txt | grep TCA | sed -n '0~3p'|cut -c 53-63 | sed 's/[ \t]*//g' >> /home/patki1/sweep/sweep3d-2.2b/.tca
#	cat process_summary.txt | grep TCM | sed -n '0~3p' |cut -c 53-63 | sed 's/[ \t]*//g'  >>/home/patki1/sweep/sweep3d-2.2b/.tcm
#done

#cd /home/patki1/sweep/sweep3d-2.2b

#*******************************

find . -name 'info*' -print | sort -n > tmp2
cat tmp2 | xargs grep cores | cut -d ":" -f 3 | sed 's/[ \t]*//g' > .cores
cat tmp2 | xargs grep nodes | cut -d ":" -f 3 |sed 's/[ \t]*//g'  > .nodes
cat tmp2 | xargs grep MHz | sed -n '0~16p' | cut -d ":" -f 3 | sed 's/[ \t]*//g'> .freq

#*******************************
#Uncomment the following if using papi and comment out the other table generation command
#*******************************
#paste -d ' ' .freq  .nodes .cores .time .tca .tcm > .table
#sed '1 i freq nodes cores time l2tca l2tcm' .table > table.out
#*******************************

paste -d ' ' .freq  .nodes .cores .time > .table
sed '1 i freq nodes cores time' .table > table.out

rm tmp
rm tmp2
#rm .tca .tcm
rm .freq .cores .nodes .time .table

