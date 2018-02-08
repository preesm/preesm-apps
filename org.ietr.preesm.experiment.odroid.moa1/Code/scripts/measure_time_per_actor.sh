#!/bin/sh

####################################################################
# Testing the time consumed per actor
####################################################################

echo "Starting sequence of time measurements"

APPLI=~/Projets/preesm-private/org.ietr.preesm.experiment.odroid.moa1
FINALSTAT=$PROJECT/finalstats/mat/activity
IP=192.168.0.2 # Odroid IP

# Removing previous code version on target
ssh odroid@$IP 'sudo rm -R ~/Code'

# Testing whether the directory has effectively been deleted
while [ -d ~/Temp/odroid/home/odroid/Code ]
do
    sleep 1
done

mv $APPLI/Code/Stereo/generated/analysis.csv $APPLI/Code/Stereo/generated/analysis_ref.csv

# Copying the code to the Odroid target. The code is in the workspace copy of the project.
cp -Rf $APPLI/Code ~/Temp/odroid/home/odroid

# Repeating N times the launch
for execit in 0 1 2 3 4 5 6 7 8 9
do
    # Executing a script to measure time
    ssh odroid@$IP 'sudo bash -s' < targetScriptMeasureTimeStereo.sh

    # Retrieving time analysis
    mv -f ~/Temp/odroid/home/odroid/Code/Stereo/generated/analysis.csv $APPLI/finalstats/analysis/analysis$execit.csv
done
