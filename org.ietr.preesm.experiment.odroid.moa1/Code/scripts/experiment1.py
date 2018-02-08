#!/usr/bin/python3.5
"""
Launching an experiment on MoA on several mappings

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
def copy_files(iteration_nr):
    today_dir = finalstat_dir + time.strftime("%d-%m-%Y")

    print ("Creating directory: " + today_dir)

    # Creating the day directory if not existing
    if not os.path.isdir(today_dir):
        os.mkdir(today_dir)

    # Copying experiment files and preindexing them with experiment number
    for file in glob.glob(finalstat_dir + "*.csv"):
        filename = ntpath.basename(file)
        shutil.move(file,today_dir + "/" + str(iteration_nr) + "_" + filename)

# Launching experiment
def main():
    start_index = -1 # Index of the first scenario applied
    end_index = -1 # Index of the last scenario applied
    iteration_start = -1 # ID of the 1st experiment
    iteration_end = -1 # ID of the last experiment

    # Managing command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:],"s:e:i:j:h",["start_index=","end_index=","iteration_start=","iteration_end=","help"])
    except getopt.GetoptError:
        print('usage: experiment1.py -s <start_index> -e <end_index> -i <start_iteration> -j <iteration_end>')
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print('experiment1.py  -s <start_index> -e <end_index> -i <start_iteration> -j <iteration_end>')
            sys.exit()
        elif opt in ("-i", "--iteration_start"):
            print(arg)
            iteration_start = arg  
        elif opt in ("-j", "--iteration_end"):
            iteration_end = arg  
        elif opt in ("-s", "--start_index"):
            start_index = arg  
        elif opt in ("-e", "--end_index"):
            end_index = arg  
    
    # experiment loop
    if int(start_index) >= 0 and int(end_index) >= 0 and int(end_index)-int(start_index) >= 0 and int(iteration_start) >= 0 and int(iteration_end) >= 0 and int(iteration_end)-int(iteration_start) >= 0:
        print('Required start index is ', start_index)
        print('Required end index is ', end_index)


        print('Start MoA Experiment')
        for i in range(int(iteration_start), int(iteration_end) + 1):
            for n in range(int(start_index), int(end_index) + 1):
                strn = str(n)
                p = subprocess.call(['./measure1energy.sh', strn])
                copy_files(i)

            print('Ended MoA Experiment')
    else:
        print('Wrong call format! usage: experiment1.py -s <start_index> -e <end_index> -i <iteration_start> -j <iteration_end>')


if __name__ == "__main__":
    main()
