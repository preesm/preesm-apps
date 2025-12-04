#!/bin/bash -eu

PROJECTDIR=$(dirname $0)
ARCHIVEDIR=${PROJECTDIR}/archives/

mkdir -p ${ARCHIVEDIR}
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
cp ${PROJECTDIR}/Scenarios/1core_display.scenario ${ARCHIVEDIR}/org.ietr.preesm.sobel/Scenarios/1core.scenario
cp ${PROJECTDIR}/Workflows/Codegen.workflow ${ARCHIVEDIR}/org.ietr.preesm.sobel/Workflows/
cp ${PROJECTDIR}/.project ${PROJECTDIR}/Readme.md ${ARCHIVEDIR}/org.ietr.preesm.sobel/
cp ${PROJECTDIR}/Code/dat/ReadMe.md ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/dat/
cp ${PROJECTDIR}/Code/dat/CMakeLists.txt ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/dat/
cp -R ${PROJECTDIR}/Code/lib/cmake_modules ${PROJECTDIR}/Code/lib/ReadMe.md ${PROJECTDIR}/Code/lib/CMakeLists.txt ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/lib/
cp -R ${PROJECTDIR}/Code/include/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/
cp -R ${PROJECTDIR}/Code/src/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/
cp -R ${PROJECTDIR}/Code/CMake* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/

#remove/override step 0 files
rm ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/sobel.h ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/splitMerge.h
rm ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/sobel.c ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/splitMerge.c
cp -R ${PROJECTDIR}/Code/include_beforesobel/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/

#zip initial project
rm -f ${ARCHIVEDIR}/org.ietr.preesm.sobel.zip
(cd ${ARCHIVEDIR} && zip -r org.ietr.preesm.sobel.zip org.ietr.preesm.sobel)

#update to tutorial 1 result files
rm ${ARCHIVEDIR}/org.ietr.preesm.sobel/Algo/*
cp ${PROJECTDIR}/Algo/top_sobel.* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Algo/
cp ${PROJECTDIR}/Archi/4CoreX86.slam ${ARCHIVEDIR}/org.ietr.preesm.sobel/Archi/
cp ${PROJECTDIR}/Scenarios/1core_sobel.scenario ${ARCHIVEDIR}/org.ietr.preesm.sobel/Scenarios/1core.scenario
cp ${PROJECTDIR}/Scenarios/4core_sobel.scenario ${ARCHIVEDIR}/org.ietr.preesm.sobel/Scenarios/4core.scenario
cp -R ${PROJECTDIR}/Code/include/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/include/
cp -R ${PROJECTDIR}/Code/src/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/
cp -R ${PROJECTDIR}/Code/src_beforemem/* ${ARCHIVEDIR}/org.ietr.preesm.sobel/Code/src/

#zip result project
rm -f ${ARCHIVEDIR}/tutorial1_result.zip
(cd ${ARCHIVEDIR} && zip -r tutorial1_result.zip org.ietr.preesm.sobel)


#zip  sobel sources
rm -f ${ARCHIVEDIR}/sobel_sources.zip
zip -j ${ARCHIVEDIR}/sobel_sources.zip \
	${PROJECTDIR}/Code/include/sobel.h \
	${PROJECTDIR}/Code/src/sobel.c

#zip splitMerge sources
rm -f ${ARCHIVEDIR}/splitMerge_sources.zip
zip -j ${ARCHIVEDIR}/splitMerge_sources.zip \
	${PROJECTDIR}/Code/include/splitMerge.h \
	${PROJECTDIR}/Code/src_beforemem/splitMerge.c

#zip C6678 source
rm -f ${ARCHIVEDIR}/sobel_6678_sources.zip
zip ${ARCHIVEDIR}/sobel_6678_sources.zip \
	${PROJECTDIR}/CodeC6678/image_analyzer/* \
	${PROJECTDIR}/CodeC6678/include/* \
	${PROJECTDIR}/CodeC6678/src/* \
	${PROJECTDIR}/CodeC6678/modelPreesm.cfg


rm -rf ${ARCHIVEDIR}/org.ietr.preesm.sobel
