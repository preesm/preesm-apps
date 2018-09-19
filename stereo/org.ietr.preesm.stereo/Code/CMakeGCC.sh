#!/bin/sh

rm -rf bin
mkdir bin
(cd bin &&  cmake .. && make)
