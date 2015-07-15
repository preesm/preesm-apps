#!/bin/bash

function log() {
	echo "$(date +%X) $1"
}

# Do some initialization
cd "$( dirname "${BASH_SOURCE[0]}" )"

STEPBYSTEPDIR=$PWD
ARCHIVEDIR=$PWD/archives
COMMITID=$(git log -1 --pretty="%h")
log "Original state is commit $COMMITID"

# Empty the achives directory
log "Empty the achives directory $ARCHIVEDIR"
rm -r -f $ARCHIVEDIR/*

# Test preesm workflow
log "Test Preesm workflow before 1st tutorial"
$RUNSCRIPTS/preesm_run_workflow.sh $GITDIR/preesm-apps/tutorials $RUNTIMEWORKSPACE $ECLIPSERUN org.ietr.preesm.sobel Codegen.workflow 1core.scenario

# Create the original archive for the tutorial
log "Create the original archive for the tutorial"
cd .. 
zip $ARCHIVEDIR/base.zip \
	Algo/* \
	Archi/* \
	Code/* \
		Code/include/* \
		Code/lib/cmake_modules/* \
		Code/lib/ReadMe.txt Code/src/* \
	Scenarios/* \
	Workflows/* .\
	.project \
	Readme.txt
	
# Apply changes from 1st tutorial
log "Apply first tutorial"
git am --signoff -k $STEPBYSTEPDIR/tuto1.patch

# Test preesm workflow
log "Test Preesm workflow after 1st tutorial"
$RUNSCRIPTS/preesm_execute_workflow.sh $RUNTIMEWORKSPACE $ECLIPSERUN org.ietr.preesm.sobel Codegen.workflow 4core.scenario
