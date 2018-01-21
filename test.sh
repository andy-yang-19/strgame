#!/bin/bash

ncpu=`nproc`

str1file=c${ncpu}s1
str2file=c${ncpu}s2

rm ${str1file} ${str2file}

for i in {1..10}
do
	./str1 10 >> ${str1file}
done

for i in {1..10}
do
	./str2 10 >> ${str2file}
done

