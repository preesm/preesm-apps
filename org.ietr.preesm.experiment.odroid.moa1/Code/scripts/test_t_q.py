#!/usr/bin/python3.4
"""
Testing discrepancy between quanta and tokens

@author mpelcat 
"""

import subprocess, sys, getopt, time, os, shutil, glob, ntpath
from subprocess import Popen, PIPE

# Using colors when printing
"""class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
"""

finalstat_dir = "../../finalstats/mat/activity/"

def main():
   # Iterating on token info and checking consistency

    for orig_file in glob.glob(finalstat_dir + "16-06-2016/" + "0_tokens*.csv"):
        origfilename = ntpath.basename(orig_file)
        origfilepath = finalstat_dir + "16-06-2016/" + origfilename
        nameparts=origfilename.split('_')
        newfilename_g= '_' + nameparts[1] + '_' + nameparts[2]
        # checking differences between 0 and i
        for i in range(1,10):
            newfilename = str(i) + newfilename_g
            newfilepath = finalstat_dir + "16-06-2016/" + newfilename
            if os.path.isfile(newfilepath):
                new_file = open(newfilepath, 'r')
                #print(newfilename)
                #print(newfilepath + ' vs. ' + origfilepath)
                
                #result = subprocess.call(['diff', newfilepath, origfilepath], stdout=PIPE)

                p = Popen(['diff', newfilepath, origfilepath], stdin=PIPE, stdout=PIPE, stderr=PIPE)
                output, err = p.communicate(b'')
                rc = p.returncode
                if(output.strip()):
                    print(newfilename + ' ' + str(output))


if __name__ == "__main__":
    main()
