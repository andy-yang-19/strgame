#!/bin/bash

ncpu=`nproc`

str1file=c${ncpu}s1
str2file=c${ncpu}s2

rm -f ${str1file} ${str2file}

for i in {1..1}
do
	./str1 10 >> ${str1file}
done

for i in {1..1}
do
	./str2 10 >> ${str2file}
done

