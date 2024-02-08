#!/bin/bash

for ((i=0; i<=100; i++)); do
    ../executable/CRoverlapchi4.out -g -1 -i 100000 -t 100000 -n 4096 -v 0.018 -x $i
done