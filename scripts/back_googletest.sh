#!/bin/bash
# Author: Wang, Yinuo
# Date: 06/15/2021
# This script is used to back up googletest-build and googletest-download directories after the first succesful make for later use.

projpath=~/MiLAB-Cheetah-Software/
buildpath=~/MiLAB-Cheetah-Software/build/googletest-build/
mcbuildpath=~/MiLAB-Cheetah-Software/mc-build/googletest-build/

if [ -e $buildpath ] ; then
    sudo rm -rf $projpath/googletest/googletest-*
    cp -r ../build/googletest-build $projpath/googletest
    cp -r ../build/googletest-download $projpath/googletest
    echo Finshed back up build/googletest-* dir.
else
    echo Failed to back up build/googletest-* dir, please run make command first.
    exit 1
fi

if [ -e $mcbuildpath ] ; then
    sudo rm -rf $projpath/googletest/googletest-mc/googletest-*
    cp -r ../mc-build/googletest-build $projpath/googletest/googletest-mc
    cp -r ../mc-build/googletest-download $projpath/googletest/googletest-mc
    echo Finished back up mc-build/googletest-* dir.
else
    echo Failed to back up mc-build/googletest-* dir, please run make command first.
    exit 1
fi

exit 0
