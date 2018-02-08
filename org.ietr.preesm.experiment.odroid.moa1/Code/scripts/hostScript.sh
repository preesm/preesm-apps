#!/bin/sh

rm -r bin
./CMakeGCC.sh
cd bin/make
make
./test
cd ..
