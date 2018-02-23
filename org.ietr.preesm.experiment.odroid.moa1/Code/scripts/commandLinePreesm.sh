#!/bin/bash

##
## Config
##



## the path to the Preesm binary directory
PREESMDIR=${1}

## the folder containing the application to run (where the .project is)
APPDIR=${2}

## workflow and scenario to run (must be respectively under Workflows and Scenarios folder within the project)
WORKFLOW=${3}
SCENARIO=${4}



APPDIR="/home/anmorvan/test/max_droid/preesm-2.8.0-linux.gtk.x86_64/workspace/org.ietr.preesm.experiment.odroid.moa1/"
APPDIR="/home/anmorvan/test/max_droid/org.ietr.preesm.experiment.odroid.moa1/"
#PREESMDIR='/home/payvar/preesm-2.8.0-linux.gtk.x86_64'
PREESMDIR="/home/anmorvan/test/preesm-2.8.0-linux.gtk.x86_64/"
 # Experiment ID corresponding to the scenario
EXPERIMENT_ID="1"
WORKFLOW="Codegen.workflow"
SCENARIO="TestComPC_${EXPERIMENT_ID}.scenario"




[ ! -x ${PREESMDIR}/eclipse ] && echo "Error: \$PREESMDIR does not contain a Preesm distro." && exit 1
[ ! -e ${APPDIR}/.project ] && echo "Error: '${APPDIR}' is not an Eclipse project" && exit 1
[ ! -e ${APPDIR}/Workflows/${WORKFLOW} ] && echo "Error: Could not locate workflow" && exit 1
[ ! -e ${APPDIR}/Scenarios/${SCENARIO} ] && echo "Error: Could not locate scenario" && exit 1

##
## RUN
##

PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)

echo ""
echo "***START*** $(date -R)"
echo ""
echo ""
echo "Init workspace and import project"
echo ""

${PREESMDIR}/eclipse -nosplash -consolelog -data ${WORKSPACE} -application org.eclipse.cdt.managedbuilder.core.headlessbuild -importAll ${APPDIR}

echo ""
echo "Run workflow from project $PROJECT"
echo ""

${PREESMDIR}/eclipse -nosplash -consolelog -data ${WORKSPACE} -application org.ietr.preesm.cli.workflowCli ${PROJECT} -w ${WORKFLOW} -s ${SCENARIO}

echo ""
echo "***END*** $(date -R)"
echo ""

rm -rf ${WORKSPACE}

exit 0
