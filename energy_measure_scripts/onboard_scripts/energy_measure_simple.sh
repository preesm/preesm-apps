#!/bin/bash -eu
# desc : This script measure the power consumption of a program.
# arg1 :program name

BINARY=$1

SCRIPT_DIR=$(cd $(dirname ${0}) && pwd)

# clean previous run
rm -rf ${SCRIPT_DIR}/Results/
mkdir -p ${SCRIPT_DIR}/Results/


##########################
# TODO! play with nice
##########################

# run energy recorder async. and keep PID 
/usr/local/bin/EnergyRecorder > ${SCRIPT_DIR}/Results/records &
PID=$!

# run program
${BINARY}

#kill energy monitor when binary is finished

while ps -p ${PID} > /dev/null;
do
  kill -2 ${PID};
done


