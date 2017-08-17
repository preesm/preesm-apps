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

# Remove unwanted content from main
log "Remove unwanted content from main for tutorial."
cp Code/src/main.cpp $ARCHIVEDIR/main.cpp
sed -i -e "s/generated\/top_display.h/generated\/<topgraph_name_in_preesm>.h/" $ARCHIVEDIR/main.cpp 
sed -i -e "s/free_top_display/free_<topgraph_name_in_preesm>/" $ARCHIVEDIR/main.cpp 
sed -i -e "s/N_FCT_TOP_DISPLAY/N_FCT_<TOPGRAPH_NAME_IN_PREESM>/" $ARCHIVEDIR/main.cpp 
sed -i -e "s/top_display_fcts;/<topgraph_name_in_preesm>_fcts;/" $ARCHIVEDIR/main.cpp 
sed -i -e "s/init_top_display/init_<topgraph_name_in_preesm>/" $ARCHIVEDIR/main.cpp
sed -i -e "/#include \"nbSliceSetter.h\"/d" $ARCHIVEDIR/main.cpp 
sed -i -e "/#include \"yuvRead.h\"/d" $ARCHIVEDIR/main.cpp 
sed -i -e "/#include \"yuvDisplay.h\"/d" $ARCHIVEDIR/main.cpp 
sed -i -e "/yuvDisplayInit(0, DISPLAY_W, DISPLAY_H)/d" $ARCHIVEDIR/main.cpp 
sed -i -e "/initReadYUV(DISPLAY_W, DISPLAY_H);/d" $ARCHIVEDIR/main.cpp 
sed -i -e "/initNbSliceSetter(DISPLAY_H);/d" $ARCHIVEDIR/main.cpp 
	
# Create the original archive for the tutorial
log "Create the original archive for the tutorial"
pushd .
cd $PROJECTDIR
zip -j Archives/tutorial_spider_files.zip \
		Code/include/nbSliceSetter.h \
		Code/lib/cmake_modules/FindSpider.cmake \
		Code/src/nbSliceSetter.cpp \
		Code/src/main.cpp \
		Code/dat/sobel_spider.exe.manifest
popd

# Cleanup
log "Cleanup"
rm $ARCHIVEDIR/main.cpp