#!/usr/bin/python3.4
"""
Planning different experimentations

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

    #os.system("./experiment1.py -s 64 -e 318 -i 0 -j 0")
    #os.system("./experiment1.py -s 606 -e 860 -i 0 -j 0")
    #os.system("./experiment1.py -s 861 -e 1115 -i 0 -j 0")
    #os.system("./experiment1.py -s 1116 -e 1370 -i 0 -j 0")

    #os.system("./experiment1.py -s 1224 -e 1370 -i 0 -j 0")

    #os.system("./experiment1.py -s 1371 -e 1625 -i 0 -j 0")
    os.system("./experiment1.py -s 1573 -e 1625 -i 0 -j 0")

    #os.system("./experiment1.py -s 1626 -e 1880 -i 0 -j 0")


# Main definition
if __name__ == "__main__":
    main()
