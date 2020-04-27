#!/bin/bash -eu

PROJECTDIR=$(dirname $0)
ARCHIVEDIR=${PROJECTDIR}/archives/

mkdir -p ${ARCHIVEDIR}
rm -rf ${ARCHIVEDIR}/tutorial_spider_files


#zip Spider tuto files

rm -f ${ARCHIVEDIR}/tutorial_spider_files.zip
zip -j ${ARCHIVEDIR}/tutorial_spider_files.zip \
		${PROJECTDIR}/Code/include/nbSliceSetter.h \
		${PROJECTDIR}/Code/lib/cmake_modules/FindSpider.cmake \
		${PROJECTDIR}/Code/src/nbSliceSetter.cpp \
		${PROJECTDIR}/Code/dat/sobel_spider.exe.manifest