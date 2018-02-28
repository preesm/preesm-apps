#!/bin/bash -eu

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm project to test
#   $3 = Workflow file name under $2/Workflows/
#   $4 = Scenario file name under $2/Scenarios/
# Optional arguments :
#   $5 = Command to build the application on the board (see below)
#        by default : 'cd Code/ && make'
#   $6 = Command to run the application on the board (see below)
#        by default : 'cd Code/ && make run'
#   $7 = Number of measures (or 4 by default)
# Result: in folder ${APPDIR}/finalstats/
#   a list of measurements in .csv files
####################################################################

./measure1energy.sh \
  /home/anmorvan/test/preesm-2.8.0-SNAPSHOT201802231522-linux.gtk.x86_64/ \
  /home/anmorvan/git/preesm-apps/org.ietr.preesm.experiment.odroid.moa1/ \
  Codegen.workflow \
  TestComPC_1.scenario \
  "./test_moa" \
  "make" \
  4
