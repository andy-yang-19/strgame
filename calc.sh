#!/bin/bash

awk '{sum+=$4} END {printf "c1s1 %d\n", sum/NR}' c1s1
awk '{sum+=$4} END {printf "c2s1 %d\n", sum/NR}' c2s1
awk '{sum+=$2} END {printf "c1s2 %d\n", sum/NR}' c1s2
awk '{sum+=$2} END {printf "c2s2 %d\n", sum/NR}' c2s2

