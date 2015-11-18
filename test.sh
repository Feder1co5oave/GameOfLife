#!/bin/bash
SUM=0
MAX=0
MIN=0
for i in {1..20}
do
  #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
  T=`\time --format="%e" ./main.out --step 10 --height 10 --width 10 --thread 16 2>&1`
  SUM=$(perl -e "print $SUM+$T")

  if (( T > MAX));then
    MAX=$T
  fi

  if [[ "$T" -lt "$MIN" ]];then
    MIN=$T
  fi

  echo $T
done

echo "min $MIN max $MAX"
echo $SUM/20
