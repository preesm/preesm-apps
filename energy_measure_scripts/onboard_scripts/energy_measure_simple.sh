#!/bin/bash -eu
# desc : This script measure the power consumption of a program.
# arg1 :program name

BINARY=$1

# clean previous run
rm -rf Results/
mkdir -p Results/


##########################
# TODO! play with nice
##########################

# run energy recorder async. and keep PID 
/usr/local/bin/EnergyRecorder > Results/records &
PID=$!

# run program
${BINARY}

#kill energy monitor when binary is finished

while [ ps -p ${PID} ]
do
  kill -2 ${PID};
done


