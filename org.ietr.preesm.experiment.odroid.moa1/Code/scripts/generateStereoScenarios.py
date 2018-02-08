#!/usr/bin/python3.5
"""
Modifying a scenario to add diversity

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


scenario_dir = "../../Scenarios/"

# Based on a binary 8-bit number, assigning the 8 cores
def coreString(id):
    val = ""
    c0 = "A7_Core0,"
    c1 = "A7_Core1,"
    c2 = "A7_Core2,"
    c3 = "A7_Core3,"
    
    c4 = "A15_Core4,"
    c5 = "A15_Core5,"
    c6 = "A15_Core6,"
    c7 = "A15_Core7,"

    if(id & 1):
        val += c0

    if(id & 2):
        val += c1

    if(id & 4):
        val += c2

    if(id & 8):
        val += c3

    if(id & 16):
        val += c4

    if(id & 32):
        val += c5

    if(id & 64):
        val += c6

    if(id & 128):
        val += c7

    return val

# Generating scenarios with default parameters and all mappings
def generate65to318():

    scenario_index = 65 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_64.scenario -o \""+coreString(map_index)+"\" -p \"\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with forced parameters and monocore mappings
def generate319to326():
    
    scenario_index = 319 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 8):
        os.system("./modifyScenario.py -f TestComPC_64.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=2,maxDisparity=2\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index * 2 # to the next operator

# Generating scenarios with forced parameters and monocore mappings
def generate327to334():
    
    scenario_index = 327 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 8):
        os.system("./modifyScenario.py -f TestComPC_64.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=3,maxDisparity=15\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index * 2 # to the next operator

# Generating scenarios with forced parameters and monocore mappings
def generate335to342():
    
    scenario_index = 335 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 8):
        os.system("./modifyScenario.py -f TestComPC_64.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index * 2 # to the next operator

# Generating scenarios with forced parameters and monocore mappings
def generate344to350():
    
    scenario_index = 344 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(1, 8):
        os.system("./modifyScenario.py -f TestComPC_343.scenario -o \""+coreString(map_index)+"\" -p \"width=90,height=75,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index * 2 # to the next operator

# Generating scenarios with forced parameters and monocore mappings
def generate352to358():
    
    scenario_index = 352 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(1, 8):
        os.system("./modifyScenario.py -f TestComPC_351.scenario -o \""+coreString(map_index)+"\" -p \"width=270,height=225,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index * 2 # to the next operator

# Generating scenarios with forced parameters and monocore mappings
def generate359to():
    
    scenario_index = 359 # First index to modify
    map_index = 3 # this value is seen as a binary where each bin is a core

    for index in range(3, 250):
        os.system("./modifyScenario.py -f TestComPC_358.scenario -o \""+coreString(map_index)+"\" -p \"width=270,height=225,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index +1 # to the next operator
        if (map_index==4) or (map_index==8) or (map_index==16) or (map_index==32) or (map_index==64) or (map_index==128):
            map_index = map_index +1 # single cores already tested

# Generating scenarios with default parameters and all mappings
def generate606to860():

    scenario_index = 606 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 255):
        os.system("./modifyScenario.py -f TestComPC_319.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=2,maxDisparity=2\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index + 1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate861to1115():

    scenario_index = 861 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 255):
        os.system("./modifyScenario.py -f TestComPC_327.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=3,maxDisparity=15\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index + 1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate1116to1370():

    scenario_index = 1116 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 255):
        os.system("./modifyScenario.py -f TestComPC_335.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index + 1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate1371to1625():

    scenario_index = 1371 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 255):
        os.system("./modifyScenario.py -f TestComPC_343.scenario -o \""+coreString(map_index)+"\" -p \"width=90,height=75,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index + 1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate1626to1880():

    scenario_index = 1626 # First index to modify
    map_index = 1 # this value is seen as a binary where each bin is a core

    for index in range(0, 255):
        os.system("./modifyScenario.py -f TestComPC_351.scenario -o \""+coreString(map_index)+"\" -p \"width=270,height=225,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index + 1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate1882to2135():

    scenario_index = 1882 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_1881.scenario -o \""+coreString(map_index)+"\" -p \"\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate2137to2390():

    scenario_index = 2137 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_2136.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=2,maxDisparity=2\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate2392to2645():

    scenario_index = 2392 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_2391.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=3,maxDisparity=15\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate2647to2900():

    scenario_index = 2647 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_2646.scenario -o \""+coreString(map_index)+"\" -p \"nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate2902to3255():

    scenario_index = 2902 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_2901.scenario -o \""+coreString(map_index)+"\" -p \"width=90,height=75,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate3157to3410():

    scenario_index = 3157 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_3156.scenario -o \""+coreString(map_index)+"\" -p \"width=270,height=225,nbIterations=4,maxDisparity=60\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate3411to3665():

    scenario_index = 3412 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_3411.scenario -o \""+coreString(map_index)+"\" -p \"\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1

# Generating scenarios with default parameters and all mappings
def generate3666to3920():

    scenario_index = 3667 # First index to modify
    map_index = 2 # this value is seen as a binary where each bin is a core

    for index in range(0, 254):
        os.system("./modifyScenario.py -f TestComPC_3666.scenario -o \""+coreString(map_index)+"\" -p \"\" -n TestComPC_"+str(scenario_index)+".scenario")
        scenario_index = scenario_index +1
        map_index = map_index + 1


# Generating scenarios for stereo matching
def main():
    #generate65to318()
    #generate319to326()
    #generate327to334()
    #generate335to342()
    #generate344to350()
    #generate352to358()
    #generate359to()

    #generate606to860()
    #generate861to1115()
    #generate1116to1370()
    #generate1371to1625()
    #generate1626to1880()

    #generate1882to2135()
    #generate2137to2390()
    #generate2392to2645()
    #generate2647to2900()
    #generate2902to3155()
    #generate3157to3410()
    #generate3411to3665()
    generate3666to3920()

# Main definition
if __name__ == "__main__":
    main()
