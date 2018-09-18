#!/bin/bash -eu

STEPBYSTEPDIR=$(dirname $0)
PROJECTDIR=${STEPBYSTEPDIR}/..
ARCHIVEDIR=${STEPBYSTEPDIR}/

rm -rf ${ARCHIVEDIR}/org.ietr.preesm.sobel

mkdir -p \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Algo/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Archi/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Scenarios/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Workflows/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/dat/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/lib/ \
	${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/

cp ${PROJECTDIR}/Algo/top_display* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Algo/
cp ${PROJECTDIR}/Archi/1CoreX86.slam ${ARCHIVEDIR}/org.ietr.preesm.sobel/Archi/
cp ${PROJECTDIR}/Scenarios/1core_display.scenario ${ARCHIVEDIR}/org.ietr.preesm.sobel/Scenarios/
cp ${PROJECTDIR}/Workflows/Codegen.workflow ${ARCHIVEDIR}/org.ietr.preesm.sobel/Workflows/
cp ${PROJECTDIR}/.project ${PROJECTDIR}/Readme.md ${ARCHIVEDIR}/org.ietr.preesm.sobel/
cp ${PROJECTDIR}/Code/dat/ReadMe.md ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/dat/
cp -R ${PROJECTDIR}/Code/lib/cmake_modules ${PROJECTDIR}/Code/lib/ReadMe.md ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/lib/
cp -R ${PROJECTDIR}/Code/include/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/
cp -R ${PROJECTDIR}/Code/src/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/
cp -R ${PROJECTDIR}/Code/CMake* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/

#remove/override step 0 files
rm ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/sobel.h ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/splitMerge.h
rm ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/sobel.c ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/splitMerge.c
cp -R ${PROJECTDIR}/Code/include_beforesobel/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/

rm -f ${ARCHIVEDIR}/org.ietr.preesm.sobel.zip
zip -r ${ARCHIVEDIR}/org.ietr.preesm.sobel.zip ${ARCHIVEDIR}/org.ietr.preesm.sobel



rm -rf ${ARCHIVEDIR}/org.ietr.preesm.sobel