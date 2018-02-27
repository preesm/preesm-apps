#!/bin/bash -eu

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm project to test
#   $3 = Workflow file name under $2/Workflows/
#   $4 = Scenario file name under $2/Scenarios/
# Optional arguments :
#   $5 = Command to build the application on the board (see below)
#        by default : 'cd Code/ && make'
#   $6 = Command to run the application on the board (see below)
#        by default : 'cd Code/ && make test'
#   $7 = Number of measures (or 4 by default)
# Result: in folder ${APPDIR}/finalstats/
#   a list of measurements in .csv files
####################################################################

###################################
## Check
###################################

case $# in
  4)
    BUILD_CMD="cd Code/ && make"
    RUN_CMD="cd Code/ && make test"
    NBREPEAT=4
    ;;
  5)
    BUILD_CMD=$5
    RUN_CMD="cd Code/ && make test"
    NBREPEAT=4
    ;;
  6)
    BUILD_CMD=$5
    RUN_CMD=$6
    NBREPEAT=4
    ;;
  7)
    BUILD_CMD=$5
    RUN_CMD=$6
    NBREPEAT=$7
    ;;
  *)
    cat << "EOF"
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm project to test
#   $3 = Workflow file name under $2/Workflows/
#   $4 = Scenario file name under $2/Scenarios/
# Optional arguments :
#   $5 = Command to build the application on the board (see below)
#        by default : 'cd Code/ && make'
#   $6 = Command to run the application on the board (see below)
#        by default : 'cd Code/ && make test'
#   $7 = Number of measures (or 4 by default)
EOF
    exit 1
    ;;
esac

PREESMDIR=$1
APPDIR=$2
WORKFLOW=$3
SCENARIO=$4

###################################
## Config
###################################

IP=192.168.0.2 # Odroid IP
USR=odroid # Odroid user
PSD=odroid # Odroid user password

###################################
## Generated / Constant Config
###################################

# parse project name from .project file
PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
# use temporary directory as workspace
WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)

# SSH key file name
SSHKEYFILE=.id_rsa_odroid

###################################
## Functions
###################################

function odroid_init_board() {
  echo "[ODROID - INIT]"
  echo "[ODROID - INIT] May ask for odroid password few times"
  
  # generate a ssh key to avoid interactive communications
  [ ! -e ${SSHKEYFILE} ] && ssh-keygen -f ${SSHKEYFILE} -t rsa -N ''
  ssh-copy-id -i ${SSHKEYFILE}.pub ${USR}@${IP}
  
  # make sudo skip asking password for user 
  set +e
  echo -e "${PSD}\n" | ssh -t -i ${SSHKEYFILE} ${USR}@${IP} /usr/bin/sudo -S "ls /etc/sudoers.d/odroid"
  RES=$?
  set -e
  if [ ${RES} -ne 0 ]; then
    echo "[ODROID - INIT] adding sudoers rule for odroid"
    echo -e "${PSD}\n${USR} ALL=NOPASSWD: ALL" | ssh -t -i ${SSHKEYFILE} ${USR}@${IP} /usr/bin/sudo -S "tee /etc/sudoers.d/odroid"
  else 
    echo "[ODROID - INIT] odroid rule already present"
  fi
  echo "[ODROID - INIT] Board init"
  echo "[ODROID - INIT]"
}

function odroid_sudo_exec() {
  # create tmp files on both sides
  LOCALTMP=$(mktemp)
  REMOTETMP=$(ssh -i ${SSHKEYFILE} ${USR}@${IP} /bin/bash -c "mktemp")
  
  # init local script then transfer it
  echo "$@" > ${LOCALTMP}
  scp -q -i ${SSHKEYFILE} ${LOCALTMP} ${USR}@${IP}:${REMOTETMP}
  ssh -i ${SSHKEYFILE} ${USR}@${IP} chmod 777 ${REMOTETMP}
  
  # exec script
  echo "[ODROID - START] sudo ${@}"
  set +e
  ssh -i ${SSHKEYFILE} ${USR}@${IP} /usr/bin/sudo ${REMOTETMP}
  RES=$?
  set -e
  echo "[ODROID - EXIT (${RES})] sudo ${@}"
  
  # cleanup
  ssh -i ${SSHKEYFILE} ${USR}@${IP} rm ${REMOTETMP}
  rm ${LOCALTMP}
  
  return ${RES}
}

function odroid_exec() {
  # create tmp files on both sides
  LOCALTMP=$(mktemp)
  REMOTETMP=$(ssh -i ${SSHKEYFILE} ${USR}@${IP} /bin/bash -c "mktemp")
  
  # init local script then transfer it
  echo "$@" > ${LOCALTMP}
  scp -q -i ${SSHKEYFILE} ${LOCALTMP} ${USR}@${IP}:${REMOTETMP}
  ssh -i ${SSHKEYFILE} ${USR}@${IP} chmod 777 ${REMOTETMP}
  
  # exec script
  echo "[ODROID - START] ${@}"
  set +e
  ssh -i ${SSHKEYFILE} ${USR}@${IP} /bin/bash -c ${REMOTETMP}
  RES=$?
  set -e
  echo "[ODROID - EXIT (${RES})] ${@}"
  
  # cleanup
  ssh -i ${SSHKEYFILE} ${USR}@${IP} rm ${REMOTETMP}
  rm ${LOCALTMP}
  
  return ${RES}
}
###################################
## Script Flow
###################################

echo "Starting new measurement"
# Whole process from Preesm mapping decision to execution on board and energy retrieval

odroid_init_board

# Clean previous code version on target
odroid_sudo_exec 'rm -rf ~/Code'

if [ ${EXPERIMENT_ID} -ge 64 ]; then
    APPPATH=Code/Stereo
    TARGETSCRIPT=targetScriptStereo.sh
    BINNAME=stereo
else
    APPPATH=Code
    TARGETSCRIPT=targetScriptTestCom.sh
    BINNAME=test_moa
fi

# clean generated Code from previous phases
rm -rf ${APPDIR}/${APPPATH}/generated ${APPDIR}/${APPPATH}/bin ${APPDIR}/${APPPATH}/stats ${APPDIR}/${APPPATH}/finalstats
# Launching Preesm in command line on the project
./commandLinePreesm.sh ${PREESMDIR} ${APPDIR} ${WORKFLOW} ${SCENARIO}

# transfer Code on odroid board
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/${APPPATH}/* ${USR}@${IP}:/home/${USR}/Code
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/Scripts/onboard_scripts/* ${USR}@${IP}:/home/${USR}/Code/Scripts/

# Compile Code
odroid_exec "cd ~/Code && ./CMakeGCC.sh"
odroid_exec "cd ~/Code/bin/make && make"

# prepare board for energy measurement
odroid_exec "mkdir -p ~/Code/stats"
odroid_sudo_exec "~/Code/Scripts/configure.sh"
mkdir -p ${APPDIR}/${APPPATH}/finalstats

for execit in $(seq 1 $NBREPEAT); do
  echo "execution $execit / $NBREPEAT"
  if [ ${EXPERIMENT_ID} -ge 64 ]; then
    odroid_exec "cd ~/Code/bin/make && ./${BINNAME}" &
  else
    odroid_exec "cd ~/Code/bin/make && echo -e \"\n\" | ./${BINNAME}" &
  fi
  odroid_exec "~/Code/Scripts/energy_measure.sh All ${BINNAME}" &

  wait # application execution, within the if
  wait # monitoring execution , after the if

  # Copying back the data on local FS
  odroid_exec "mv ~/Code/Scripts/Results ~/Code/Scripts/measure_${execit}" 
  rsync -e "ssh -i ${SSHKEYFILE}" -au ${USR}@${IP}:/home/${USR}/Code/Scripts/measure_${execit} ${APPDIR}/${APPPATH}/finalstats/
done;

echo ""
echo "Execution done"
echo ""

for execit in $(seq 1 $NBREPEAT); do
  # Computing the energy
  ENERGY=$(${APPDIR}/Scripts/energy_computer_v2.sh ${APPDIR}/${APPPATH}/finalstats/measure_${execit})
  echo "Energy computation for measurement #${execit}: ${ENERGY}"
  echo "${ENERGY}" > ${APPDIR}/${APPPATH}/finalstats/measure_${execit}/energy_computed.csv
done

echo ""
echo "Copying quantas and tokens"
mv -f ${APPDIR}/stats/mat/activity/tokens.csv ${APPDIR}/${APPPATH}/finalstats/
mv -f ${APPDIR}/stats/mat/activity/quanta.csv ${APPDIR}/${APPPATH}/finalstats/
mv -f ${APPDIR}/stats/mat/activity/custom_quanta.csv ${APPDIR}/${APPPATH}/finalstats/
echo ""

###################################
## Cleanup
###################################

echo "Done. Cleaning up."
echo " => measures and results in "
echo "    '${APPDIR}/${APPPATH}/finalstats/'"
echo ""
rm -rf ${WORKSPACE}
exit
