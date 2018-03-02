#!/bin/bash -eu

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm setup dir
#   $3 = Preesm project to test
#   $4 = Workflow file name under $2/Workflows/
#   $5 = Scenario file name under $2/Scenarios/
#   $6 = Binary name under $2/Code after build is done
# Optional arguments :
#   $7 = Command to build the application on the board (see below)
#        by default : 'make'
#   $8 = Number of measures (or 4 by default)
# Result: in folder ${APPDIR}/finalstats/
#   a list of measurements in .csv files
####################################################################

./measure1energy.sh \
  192.168.100.15 \
  /home/anmorvan/test/preesm-2.8.0-SNAPSHOT201803011401-linux.gtk.x86_64/ \
  /home/anmorvan/git/preesm-apps/org.ietr.preesm.experiment.odroid.moa1/ \
  Codegen.workflow \
  TestComPC_1.scenario \
  "./test_moa" \
  "make" \
  4
