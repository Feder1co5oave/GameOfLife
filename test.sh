#!/bin/bash

for i in {1..20}
do
  time ./main.xeon.out --step 1000 --height 1000 --width 1000 --thread 16
  echo "\n"
  sleep 1
done
