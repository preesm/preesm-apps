#!/bin/sh

chown -R odroid Code
chgrp -R odroid Code
cd ~/Code/Stereo
rm -r bin
./CMakeGCC.sh
cd ~/Code/Stereo/bin/make
make
cd ~/Code/Stereo/generated
cp analysis_ref.csv analysis.csv

cd ~/Code/Stereo/bin/make
./stereo&

cd ../../../..


