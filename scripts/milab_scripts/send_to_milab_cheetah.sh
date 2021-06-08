#!/bin/bash
# Author: Wang, Yinuo
# Date: 05/06/2021
# This shell script is modified based on MIT corresponding script to send software to real robot.
# Unlike MIT, we can select milab_cheetah's ip address and controller by options.
# wifi ip is the default address and the milab_ctrl is the default controller if don't specify it.

## Set robot's ip
wifiip=10.61.6.124
wireip=10.0.0.21
name=robot

## Create a prepare dir robot-software
set -e
DIR="$(pwd)"
cd ${DIR}/../../mc-build/
sudo rm -rf robot-software
mkdir robot-software
mkdir robot-software/build robot-software/log

## Select controller
if [ -z "$1" -o "$1" = "mpc" ]
then
  echo "[INFO] Copying dafault controller: milab_ctrl..."
  cp ../mc-build/user/MiLAB_Controller/milab_ctrl robot-software/build
else
  if [ "$1" = "jpos" ]; then
    echo "[INFO] Copying jpos_ctrl ..."
    cp ../mc-build/user/MiLAB_JPos_Controller/jpos_ctrl robot-software/build
  elif [ "$1" = "spi" ]; then
    echo "[INFO] Copying spi_ctrl..."
    cp ../mc-build/user/MiLAB_Spi_Controller/spi_ctrl robot-software/build
  else
    echo "[ERROR] $1 is not a existed controller"
    echo "[USAGE] sh send_to_milab_cheetah.sh [mpc|spi|jpd| ] [ |wifi|wire]"
    echo "[EXAMPLE] sh send_to_milab_cheetah.sh spi wifi"
    exit 1
  fi
fi

## Copy files

find . -name \*.so* -exec cp {} ./robot-software/build \;
cp ../scripts/run_milab* ./robot-software/build
#cp ../scripts/*test*sh ./robot-software/build
#cp ../scripts/setup_network_mc.py ./robot-software/build
#cp ../scripts/config_network_lcm.sh ./robot-software
#cp -r ../robot robot-software
cp -r ../config robot-software
#cp common/test-common ./robot-software/build
#cp rc_test/rc_test ./robot-software/build
chmod +x ./robot-software/build/*

## Send dir to real robot's computer
if [ -n "$2" ]
then
  if [ "$2" = "wifi" ]
  then
    echo "[INFO] Using Wifi connection ip address."
    echo "[INFO] Sending ... (It may take few minutes)."
    scp -rq robot-software $name@$wifiip:~/
  elif [ "$2" = "wire" ]; then
    echo "[INFO] Using wire connection ip address.  "
    echo "[INFO] Sending ... (It may take few minutes)."
    scp -rq robot-software $name@$wireip:~/
  else
    echo "[ERROR] $2 is not a supported connection type"
    echo "[USAGE] sh send_to_milab_cheetah.sh [mpc|spi|jpd| ] [ |wifi|wire]"
    echo "[EXAMPLE] sh send_to_milab_cheetah.sh spi wifi"
    exit 1
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
  exit 0
else
  echo "[ERROR] Something wrong, sending failed."
  exit 1
fi
