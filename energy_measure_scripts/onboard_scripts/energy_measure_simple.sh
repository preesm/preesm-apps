#!/bin/bash -eu
# desc : This script measure the power consumption of a program.
# arg1 :program name

BINARY=$1

SCRIPT_DIR=$(cd $(dirname ${0}) && pwd)

# clean previous run
rm -rf ${SCRIPT_DIR}/Results/
mkdir -p ${SCRIPT_DIR}/Results/

# run energy recorder async. and keep PID 
# need sudo to access lower nice priority
nice -n 20 /usr/local/bin/EnergyRecorder > ${SCRIPT_DIR}/Results/records &

# run program
# need sudo to access lower nice priority
sudo nice -n -19 ${BINARY}

#kill energy monitor when binary is finished
# need sudo to kill program run as sudo ...
sudo killall EnergyRecorder


