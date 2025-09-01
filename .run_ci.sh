#!/bin/bash -eu

set -o pipefail

function usage() {
	echo "Script usage:"
	echo "	-p <path>: Path to the Preesm binary directory"
	echo "	-a <path>: Path to the folder containing the application to run (where the .project is)"
	echo "	-s <path>: Scenario to run (must be under Scenarios folder within the project)"
	echo "	-w <path>: Workflow to run (must be under Workflows folder within the project)"
	echo "	-i <num> : Number of graph iteration to execute"
	echo "	-m	 : Mute mode, no output displayed"
	echo "	-h	 : Display this message"
}


while getopts "hp:a:s:w:i:m" opt "$@" ; do
    case "$opt" in
		h) usage; exit 0;;
		p) PREESMDIR="${OPTARG:-}";;
		a) APPDIR="${OPTARG:-}";;
		s) SCENARIO="${OPTARG:-}";;
		w) WORKFLOW="${OPTARG:-}";;
		i) RUN_ITERATION="${OPTARG:-}";;
		m) MUTE=1;;
		\?) usage >&2; exit 1;;
	esac
done

# Run preesm workflow

if [[ "$OSTYPE" == "darwin"* ]]; then
	PREESMDIR=${PREESMDIR}/Eclipse.app/Contents/MacOS/
	APPDIR=`pwd`/${APPDIR}
fi

[ ! -x ${PREESMDIR}/eclipse ] && echo "Error: \$PREESMDIR does not contain a Preesm distro." && exit 1
[ ! -e ${APPDIR}/.project ] && echo "Error: '${APPDIR}' is not an Eclipse project" && exit 1
[ ! -e ${APPDIR}/Workflows/${WORKFLOW} ] && echo "Error: Could not locate workflow" && exit 1
[ ! -e ${APPDIR}/Scenarios/${SCENARIO} ] && echo "Error: Could not locate scenario" && exit 1

[ ! -z $MUTE ] && exec 1>/dev/null 2>/dev/null

if [ -z ${RUN_ITERATION} ]; then
	ITERATION_MACRO=
else
	ITERATION_MACRO=-DPREESM_LOOP_SIZE=${RUN_ITERATION}
fi

##
## RUN
##

# PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
PROJECT=$(cat $APPDIR/.project  | tr -d [:blank:] | awk -F "</?name>" '/<name>/{print $2}')
# WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)
WORKSPACE=$(mktemp -d -t preesm-workspace.XXX)
# EXECUTABLE=$(cat $APPDIR/Code/CMakeLists.txt | grep -oPm1 "(?<=add_executable\()[^)$]+" | tr -d [:blank:])
EXECUTABLE=$(cat $APPDIR/Code/CMakeLists.txt | awk -F '[[:blank:]]*\\([[:blank:]]*' 'tolower($0) ~ /add_executable[[:blank:]]*\([[:blank:]]*/{print $2}' | awk -F " " '//{print $1}' | head -n 1)

echo ""
echo "***START*** $(date -R)"
echo ""
echo ""
echo "Init workspace and import project"
echo ""

${PREESMDIR}/eclipse -nosplash -consolelog -data ${WORKSPACE} -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import ${APPDIR}

echo ""
echo "Run workflow from project $PROJECT"
echo ""

${PREESMDIR}/eclipse -nosplash -consolelog -data ${WORKSPACE} -application org.preesm.cli.workflowCli ${PROJECT} -w ${WORKFLOW} -s ${SCENARIO}

echo ""
echo "***END*** $(date -R)"
echo ""

rm -rf ${WORKSPACE}

# Compile program

# cd ${APPDIR}
# (cd ${APPDIR} && mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_LOOP_SIZE=${RUN_ITERATION}" .. && make -j4 VERBOSE=1)
(cd ${APPDIR} && mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_FLAGS="-DPREESM_VERBOSE $ITERATION_MACRO" .. && make -j4 VERBOSE=1)

# Run program

EXEC_RESULT=$((cd ${APPDIR}/Code/bin/Release && ./${EXECUTABLE}) | grep -o 'preesm_md5_\w\+\s:\s[a-fA-F0-9]\{32\}' | sort)
echo "$EXEC_RESULT"
# Check output

(echo "$EXEC_RESULT" | cmp ${APPDIR}/.validation.hash -) || exit 1

# Everything went right


# bash .run_ci.sh -p ../preesm21/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/ -a org.ietr.preesm.stabilization -w Codegen.workflow -s 4coreX86.scenario -i 375
# bash .run_ci.sh -p ../preesm21/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/ -a SIFT -w Codegen.workflow -s HextractSIFT4Corex86_64.scenario -i 1
# bash .run_ci.sh -p ../preesm21/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/ -a org.ietr.preesm.sobel-morpho -w Codegen.workflow -s 4core.scenario -i 300 -m
# bash .run_ci.sh -p ../preesm21/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/ -a stereo/org.ietr.preesm.stereo -w NEWSynthesisAPI_legacy.workflow -s 4core.scenario -i 1

