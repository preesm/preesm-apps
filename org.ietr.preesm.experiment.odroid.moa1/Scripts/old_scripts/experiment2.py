#!/usr/bin/python3.4
"""
Launching an experiment on MoA on several mappings
No energy measurements, only Preesm simulation

@author mpelcat 
"""

import subprocess, sys, getopt, time, os, shutil, glob, ntpath

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

# Copying test files in a day directory
def copy_files():
    today_dir = finalstat_dir + time.strftime("%d-%m-%Y")

    print ("Creating directory: " + today_dir)

    # Creating the day directory if not existing
    if not os.path.isdir(today_dir):
        os.mkdir(today_dir)

    # Copying experiment files and preindexing them with experiment number
    for file in glob.glob(finalstat_dir + "*.csv"):
        filename = ntpath.basename(file)
        shutil.move(file,today_dir + "/0_" + filename)

# Launching experiment
def main():
    start_index = -1 # Index of the first scenario applied
    end_index = -1 # Index of the last scenario applied
    # Managing command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:],"s:e:i:j:h",["start_index=","end_index=","iteration_start=","iteration_end=","help"])

    except getopt.GetoptError:
        print('usage: experiment1.py -s <start_index> -e <end_index>')
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print('experiment1.py  -s <start_index> -e <end_index>')
            sys.exit()
        elif opt in ("-s", "--start_index"):
            start_index = arg  
        elif opt in ("-e", "--end_index"):
            end_index = arg  
    
    # experiment loop
    if int(start_index) >= 0 and int(end_index) >= 0 and int(end_index)-int(start_index) >= 0:
        print('Required start index is ', start_index)
        print('Required end index is ', end_index)


        print('Start MoA 2 Experiment')
        for n in range(int(start_index), int(end_index) + 1):
            strn = str(n)
            p = subprocess.call(['./simulate1energy.sh', strn,""])
            copy_files()

        print('Ended MoA 2 Experiment')
    else:
        print('Wrong call format! usage: experiment2.py -s <start_index> -e <end_index>')


if __name__ == "__main__":
    main()
