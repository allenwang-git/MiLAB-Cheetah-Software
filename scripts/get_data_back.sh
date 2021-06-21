#!/bin/bash
# Author: Wang, Yinuo
# Date: 06/21/2021
# This file is used to copy joint data log to host pc's MiLAB-Cheetah-Software directory.
# After running this script, you can plot leg data by running leg_controller_plot.py .

host_name=allen
ip=10.0.0.3
data_path=/robot-software/log/leg_controller_data.txt
target_path=~/MiLAB-Cheetah-Software/debug_tools/

cd
if [ -e $data_path ] ;
then
  scp $data_path $host_name@$ip:target_path
else
  echo "[Warning] The data file does not existed."
  exit 1
fi

  exit 0
