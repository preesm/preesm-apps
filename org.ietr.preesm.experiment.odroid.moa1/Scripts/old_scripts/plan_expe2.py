#!/usr/bin/python3.4
"""
Planning experimentation 2 - Preesm alone w/o energy measurement 

@author mpelcat 
"""

import subprocess, sys, getopt, time, os, shutil, glob, ntpath, xml.etree.ElementTree as ET, copy

# Using colors when printing
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


# Generating scenarios for stereo matching
def main():

# No more need to repeat operation, already repeated internally w/o relaunching Preesm

    #os.system("./experiment2.py -s 1881 -e 3410 -i 0 -j 0")
    os.system("./experiment2.py -s 3084 -e 3410 -i 0 -j 0")


# Main definition
if __name__ == "__main__":
    main()
