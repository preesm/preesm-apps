#!/bin/sh

####################################################################
# Testing the energy consumed per actor
####################################################################

echo "Starting sequence of measurements"

GENERATED=~/Projets/preesm-private/org.ietr.preesm.experiment.odroid.moa1/Code/Stereo/generated
FINALSTAT=~/Projets/preesm-private/org.ietr.preesm.experiment.odroid.moa1/finalstats/mat/activity

# Measuring the energy for repetitions of different actors and retrieving results in a text file

for INDEX in original writeppm compute compute2 aggregate construction census rgb2gray disparity median read; do

    date
    echo $INDEX
    cp $GENERATED/A7_Core1.c.$INDEX $GENERATED/A7_Core1.c

    ./measure1energy.sh 64

    date >> measures.txt
    echo $INDEX >> measures.txt
    cat $FINALSTAT/I?_energy_64.csv >> measures.txt
    cat $FINALSTAT/I?_time_64.csv >> measures.txt

done
