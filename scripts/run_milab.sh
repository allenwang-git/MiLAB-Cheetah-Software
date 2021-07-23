#!/bin/bash
# Author: Wang, Yinuo
# Date: 05/10/2021
# This script can run any controller and output terminal log.

# enable multicast and add route for lcm out the top
sudo ifconfig lo multicast
sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev lo

if [ -z $1 ]; then
  echo "[USAGE] ./run_milab.sh [mpc|jpos|spi] [f|l] [l| ]"
  echo "        mpc: milab_ctrl, jpos: jpos_ctrl, spi: spi_ctrl
        f: param from file, l: param form lcm
        l: create terminal log, empty: no log"
  exit 1
elif [ -z $2 ]; then
  echo "[USAGE] ./run_milab.sh [mpc|jpos|spi] [f|l] [l| ]"
  echo "        mpc: milab_ctrl, jpos: jpos_ctrl, spi: spi_ctrl
        f: param from file, l: param form lcm
        l: create terminal log, empty: no log"
  exit 1
else
  # select controller
  if [ "$1" = "mpc" ]; then
    ctrl=./milab_ctrl
  elif [ "$1" = "spi" ]; then
    ctrl=./spi_ctrl
  elif [ "$1" = "jpos" ]; then
    ctrl=./jpos_ctrl
  else
    echo "[ERROR] $1 is not a existed controller"
    echo "[USAGE] ./run_milab.sh [mpc|jpos|spi] [f|l] [l| ]"
    echo "        mpc: milab_ctrl, jpos: jpos_ctrl, spi: spi_ctrl
          f: param from file, l: param form lcm
          l: create terminal log, empty: no log"
    exit 1
  fi

  if [ "$2" != "f" -a "$2" != "l" ]; then
    echo "[ERROR] $2 is not a valid param option"
    echo "[USAGE] ./run_milab.sh [mpc|jpos|spi] [f|l] [l| ]"
    echo "        mpc: milab_ctrl, jpos: jpos_ctrl, spi: spi_ctrl
          f: param from file, l: param form lcm
          l: create terminal log, empty: no log"
    exit 1
  fi
  # configure libraries
  sudo LD_LIBRARY_PATH=. ldconfig
  # run controller
  if [ -z $3 ]; then
      sudo LD_LIBRARY_PATH=. $ctrl i r $2
  elif [ "$3" = "l" ]; then
      Date=$(date +%Y%m%d-%H%M%S)
      sudo LD_LIBRARY_PATH=. $ctrl i r $2 | tee ../log/$ctrl-$Date.log
  else
      echo "[ERROR] $3 is not a valid log option"
      echo "[USAGE] ./run_milab.sh [mpc|jpos|spi] [f|l] [l| ]"
      echo "        mpc: milab_ctrl, jpos: jpos_ctrl, spi: spi_ctrl
            f: param from file, l: param form lcm
            l: create terminal log, empty: no log"
      exit 1
  fi
fi

