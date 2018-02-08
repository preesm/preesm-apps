#!/bin/sh

chown -R odroid Code
chgrp -R odroid Code
rm -R ~/Code/stats
cd ~/Code/Crypto/Code
rm -r bin/make
./CMakeGCC.sh
cd bin/make
make
cd ~/Code
mkdir stats

## Configuring the sensors to retrieve energy
cd scripts/Alexandre
./configure.sh
cd ../..

cd Crypto/Code/bin/make
./stereo&

cd ../../../..
scripts/Alexandre/energy_measure.sh All stereo


