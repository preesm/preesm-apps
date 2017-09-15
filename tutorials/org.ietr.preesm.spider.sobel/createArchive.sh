#!/bin/bash

function log() {
	echo "$(date +%X) $1"
}

# Do some initialization
# cd "$( dirname "${BASH_SOURCE[0]}" )"

PROJECTDIR=$(dirname $0)
ARCHIVEDIR=$(dirname $0)/Archives
COMMITID=$(git log -1 --pretty="%h")
log "Original state is commit $COMMITID"

# Empty the achives directory
log "Empty the achives directory $ARCHIVEDIR"
rm -rf $ARCHIVEDIR
mkdir $ARCHIVEDIR
	
# Create the original archive for the tutorial
log "Create the original archive for the tutorial"
pushd .
cd $PROJECTDIR
zip -j Archives/tutorial_spider_files.zip \
		Code/include/nbSliceSetter.h \
		Code/lib/cmake_modules/FindSpider.cmake \
		Code/src/nbSliceSetter.cpp \
		Code/dat/sobel_spider.exe.manifest
popd
