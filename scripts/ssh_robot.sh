#!/bin/bash
# Author: Wang, Yinuo
# Date: 06/15/2021

## Set robot's ip
wifiip=10.61.6.124
wireip=10.0.0.21
name=robot
fail=0

## Try to connect robot
echo "Trying to connect **$name@$wireip** 10 times ..."
for i in `seq 1 10`
do
  sleep 2
  ssh $name@$wireip 2>/dev/null
  if [ $? -eq 255 ]; then
    fail=$(($fail+1))
  else
    break
  fi
done

if [ $fail -eq 10 ];
then
  echo "All connect attempts failed, try again."
  exit 1
fi

exit 0
