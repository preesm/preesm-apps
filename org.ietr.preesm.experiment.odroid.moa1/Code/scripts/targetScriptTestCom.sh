#!/bin/sh

chown -R odroid Code
chgrp -R odroid Code
cd ~/Code
rm -r bin
./CMakeGCC.sh
cd bin/make
make
cd ~/Code
mkdir stats

## Configuring the sensors to retrieve energy
cd scripts/Alexandre
./configure.sh
cd ../..

bin/make/test_moa&

scripts/Alexandre/energy_measure.sh All test_moa
