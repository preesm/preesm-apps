#!/usr/bin/python3.5
"""
Modifying a scenario to add diversity

@author mpelcat 
"""
from os.path import basename
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

# Modifying scenario constraints
# receiving the XML constraints element tree
# All the operators in the list are given
# the constraints of the first non empty constraint group
# in the input file
def modify_constraints(constraints_et,operator_list):
    
    # Looking for the 1st non empty constraint group
    for child in constraints_et.findall('constraintGroup'):
        if(len(child.findall("task")) > 0):
            first_constraint = child
            break
    
    # Removing all constraint groups
    new_constraint = copy.deepcopy(first_constraint)
    if first_constraint is not None:
        for child in constraints_et.findall('constraintGroup'):
            constraints_et.remove(child)
    else:
        print(bcolors.FAIL + 'No non-empty constrain to duplicate' + bcolors.ENDC)
    
    # Copying the constraint for different cores
    for operator in operator_list:
        if operator:
            cur_constraint = copy.deepcopy(new_constraint)
            cur_constraint.find('operator').attrib['name'] = operator
            constraints_et.append(cur_constraint)
        
# Modifying special vertex operators
# All the operators in the list are specified
# as special vertex operators
def modify_spo(spo_et,operator_list):
    for child in spo_et.findall('specialVertexOperator'):
        spo_et.remove(child)

    for operator in operator_list:
        if operator:
            new_spo = ET.SubElement(spo_et, 'specialVertexOperator')
            new_spo.attrib['path'] = operator
        
# Modifying scenario parameters
# All existing parameters are removed
# And new ones specified in parameter_list are added
def modify_parameters(params_et,parameter_list,graph_name):
    for child in params_et.findall('parameter'):
        params_et.remove(child)

    for pm in parameter_list:
        if pm:
            pm = pm.split('=')
            new_param = ET.SubElement(params_et, 'parameter')
            new_param.attrib['name'] = pm[0]
            new_param.attrib['value'] = pm[1]
            new_param.attrib['type'] = 'INDEPENDENT'
            new_param.attrib['parent'] = graph_name
        

# Modifying one scenario file
def modify_scenario(file_name,operator_list,parameter_list,new_file_name):

    # Open original file
    et = ET.parse(file_name)

    # Append new tag
    # new_tag = ET.SubElement(et.getroot(), 'a')
    # new_tag.text = 'body text'
    # new_tag.attrib['x'] = '1' # must be str; cannot be an int
    # new_tag.attrib['y'] = 'abc'

    root = et.getroot()

    # Getting graph name
    files = root.find('files')
    algo = files.find('algorithm')
    algo = algo.get('url')
    algo = basename(algo)
    algo = algo.split('.')
    graph_name = algo[0]

    # Modifying constraints
    constraints = root.find('constraints')
    if constraints is None:
        print(bcolors.FAIL + 
              'No constraints section in the scenario' + 
              bcolors.ENDC)
    else:
        modify_constraints(constraints,operator_list)

    # Modifying simulation parameters
    if root.find('simuParams') is None:
        print(bcolors.FAIL + 
              'No simuParams section in the scenario' + 
              bcolors.ENDC)
    else:
        spo = root.find('simuParams').find('specialVertexOperators')
        if spo is None:
            print(bcolors.FAIL + 
                  'No specialVertexOperators section in the scenario' + 
                  bcolors.ENDC)
        else:
            modify_spo(spo,operator_list)

    # Modifying parameter values
    if root.find('parameterValues') is None:
        print(bcolors.FAIL + 
              'No parameterValues section in the scenario' + 
              bcolors.ENDC)
    else:
        pv = root.find('parameterValues')
        modify_parameters(pv,parameter_list,graph_name)

    # Write back to file
    et.write(new_file_name)
    print(bcolors.OKGREEN + 
          'Written file: ' + new_file_name + bcolors.ENDC)

########################################################
# Main
# Getting command line option and launching modification
def main():
    file = '' # source xml scenario file
    # list of operators that should be allowed to execute all actors
    operator_list = ''
    new_file = '' # sink xml scenario file
    parameter_list = '' # list of comma separated parameter assignments

    # Managing command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:],"f:o:p:n:h",
                        ["file=","operator_list=","parameter_list=","new_file=","help"])
    except getopt.GetoptError:
        print('usage: experiment1.py -f <file> -o <operator_list> -n <new_file>')
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            script = os.path.basename(__file__)
            print(script + ' -f <file> -o op,list -p param=0,list=1 -n <new_file>')
            sys.exit()
        elif opt in ("-f", "--file="):
            file = scenario_dir + arg
            print(bcolors.OKBLUE + 'Source scenario: ' + file + bcolors.ENDC)
        elif opt in ("-o", "--operator_list="):
            operator_list = arg
            print(bcolors.OKBLUE + 'Operator list: ' + operator_list + bcolors.ENDC)
        elif opt in ("-p", "--parameter_list="):
            parameter_list = arg
            print(bcolors.OKBLUE + 'Parameter list: ' + parameter_list + bcolors.ENDC)
        elif opt in ("-n", "--new_file="):
            new_file = scenario_dir + arg
            print(bcolors.OKBLUE + 'Modified scenario: ' + new_file + bcolors.ENDC)

    # Modifying the scenario in place
    modify_scenario(file,operator_list.split(','),parameter_list.split(','),new_file)


# Main definition
if __name__ == "__main__":
    main()
