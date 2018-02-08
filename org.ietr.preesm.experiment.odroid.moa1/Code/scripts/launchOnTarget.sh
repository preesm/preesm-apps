#!/bin/sh

cd ..
# Copying the code to the Odroid target
rm -R ~/Temp/odroid/home/odroid/Code
cp -R Code ~/Temp/odroid/home/odroid
cd Code
# Running code on the Odroid target
ssh odroid@192.168.0.2 'bash -s' < targetScript.sh

