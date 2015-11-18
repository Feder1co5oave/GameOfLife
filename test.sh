#!/bin/bash

for i in {1..20}
do
  \time --format="%E" ./main.xeon.out --step 1000 --height 1000 --width 1000 --thread 16
  echo
  sleep 1
done
