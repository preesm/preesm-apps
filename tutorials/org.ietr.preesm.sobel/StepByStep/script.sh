#!/bin/bash

function log() {
	echo "$(date +%X) $1"
}

# Do some initialization
# cd "$( dirname "${BASH_SOURCE[0]}" )"

STEPBYSTEPDIR=$(dirname $0)
PROJECTDIR=$(dirname $0)/..
ARCHIVEDIR=$(dirname $0)/archives
COMMITID=$(git log -1 --pretty="%h")
log "Original state is commit $COMMITID"

# Empty the achives directory
log "Empty the achives directory $ARCHIVEDIR"
rm -rf $ARCHIVEDIR
mkdir $ARCHIVEDIR

# Test preesm workflow
log "Test Preesm workflow before 1st tutorial"
$CISCRIPTS/maven_execution/run_workflow.sh tutorials org.ietr.preesm.sobel Codegen.workflow 1core.scenario

# Create the original archive for the tutorial
log "Create the original archive for the tutorial"
pushd .
cd $PROJECTDIR
zip StepByStep/archives/org.ietr.preesm.sobel.zip \
	Algo/* \
	Archi/* \
	Code/* \
		Code/include/* \
		Code/dat/* \
		Code/lib/cmake_modules/* \
		Code/lib/ReadMe.md \
		Code/src/* \
	Scenarios/* \
	Workflows/* \
	.project \
	Readme.md
popd
	
# Apply changes from 1st tutorial
log "Apply first tutorial"
git am --signoff -k $STEPBYSTEPDIR/tuto1.patch

# Test preesm workflow
log "Test Preesm workflow after 1st tutorial"
$CISCRIPTS/maven_execution/run_workflow.sh tutorials org.ietr.preesm.sobel Codegen.workflow 4core.scenario

# Create the archive for the tutorial 1 result
log "Create the archive for the tutorial 1 result"
pushd .
cd $PROJECTDIR
zip StepByStep/archives/tutorial1_result.zip \
	Algo/* \
	Archi/* \
	Code/* \
		Code/include/* \
		Code/dat/* \
		Code/lib/cmake_modules/* \
		Code/lib/ReadMe.md \
		Code/src/* \
	Scenarios/* \
	Workflows/* .\
	.project \
	Readme.md
popd

# Create the archive containing sobel sources
log "Create the archive containing sobel sources"
pushd .
cd $PROJECTDIR
zip -j StepByStep/archives/sobel_sources.zip \
	Code/include/sobel.h \
	Code/src/sobel.c
popd
	
# Create the archive containing split/merge sources
log "Create the archive containing split/merge sources"
pushd .
cd $PROJECTDIR
zip -j StepByStep/archives/splitMerge_sources.zip \
	Code/include/splitMerge.h \
	Code/src/splitMerge.c
popd

# Apply changes from DSP tutorial
log "Apply DSP tutorial"
git am --signoff -k $STEPBYSTEPDIR/tutoDSP.patch

# Test preesm workflow
log "Test Preesm workflow after DSP tutorial"
$CISCRIPTS/maven_execution/run_workflow.sh tutorials org.ietr.preesm.sobel Codegen.workflow 8coreC6678.scenario

# Create the archive containing c6678 sources
log "Create the archive containing c6678 sources"
pushd .
cd $PROJECTDIR
zip StepByStep/archives/sobel_6678_sources.zip \
	CodeC6678/image_analyzer/* \
	CodeC6678/include/* \
	CodeC6678/src/* \
	CodeC6678/yuv2dat/* \
		CodeC6678/yuv2dat/include/* \
		CodeC6678/yuv2dat/src/* \
	CodeC6678/modelPreesm.cfg
popd

# Apply changes from Memory tutorials
log "Apply Memory tutorials (basic and advanced)"
git am --signoff -k $STEPBYSTEPDIR/tutoMemory.patch

# Test preesm workflow
log "Test Preesm workflow after Memory tutorials"
$CISCRIPTS/maven_execution/run_workflow.sh tutorials org.ietr.preesm.sobel Codegen.workflow 4core.scenario

# Apply Instrumented Codegen tutorials
log "Apply Instrumented Codegen tutorials"
git am --signoff -k $STEPBYSTEPDIR/tutoInstruCodegen.patch

# Test preesm workflow
log "Test Preesm workflow after Instrumented Codegen tutorial"
$CISCRIPTS/maven_execution/run_workflow.sh tutorials org.ietr.preesm.sobel InstrumentedCodegen.workflow 1core.scenario
