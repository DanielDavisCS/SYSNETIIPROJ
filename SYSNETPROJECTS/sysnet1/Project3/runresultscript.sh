#!/bin/sh
cd /home/ARGONET/dkd6/#####JUNK/Project3

for((j = 1; j <= 10; j++)) ;
do
for((i = 1; i <= 30; i++)) ;
do
./mt-prime 3000000 $i >>data.csv 2>>results.csv
done 
rm data.csv
done
