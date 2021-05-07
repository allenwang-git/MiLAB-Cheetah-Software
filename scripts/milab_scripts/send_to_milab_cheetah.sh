#!/bin/bash
# Author: Wang, Yinuo
# Date: 05/06/2021
# This shell script is modified based on MIT corresponding script to send software to real robot.
# Unlike MIT, we can select milab_cheetah's ip address and controller by options.
# wifi ip is the default address and the milab_ctrl is the default controller if don't specify it.

echo "[USAGE] sh send_to_milab_cheetah.sh [Controller_path/executable] [wifi|wire]"
echo "[EXAMPLE] sh send_to_milab_cheetah.sh MiLAB_Controller/milab_ctrl wifi"
## Set robot's ip
wifiip=10.61.6.124
wireip=10.0.0.21
name=robot

## Create a prepare dir robot-software
set -e
#DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DIR="$(pwd)"
cd ${DIR}/../../mc-build/
rm -rf robot-software
mkdir robot-software
mkdir robot-software/build
#cp common/test-common robot-software/build
if [ -z $1 ]
then
  cp ../mc-build/user/MiLAB_Controller/milab_ctrl robot-software/build
else
  cp ../mc-build/user/$1 robot-software/build
fi
find . -name \*.so* -exec cp {} ./robot-software/build \;
cp ../scripts/run* ./robot-software/build
cp ../scripts/setup_network_mc.py ./robot-software/build
cp ../scripts/run_mc_debug.sh ./robot-software/build
cp ../scripts/config_network_lcm.sh ./robot-software
cp -r ../robot robot-software
cp -r ../config robot-software

## Send dir to real robot's computer
if [ -n "$2" ]
then
  if [ "$2" = "wifi" ]
  then
    echo "[INFO] Using Wifi connection ip address."
    echo "[INFO] Sending ... (It may take few minutes)."
    scp -rq robot-software $name@$wifiip:~/
  else
    echo "[INFO] Using wire connection ip address.  "
    echo "[INFO] Sending ... (It may take few minutes)."
    scp -rq robot-software $name@$wireip:~/
  fi
else
    echo "[INFO] No connection type specified, using wifi connection as default."
    echo "[INFO] Sending ... (It may take few minutes)."
    scp -rq robot-software $name@$wifiip:~/
fi

## Check result
if [ $? -eq 0 ]
then
  echo "[INFO] Finish software sending successfully."
else
  echo "[ERROR] Something wrong, sending failed."
fi
