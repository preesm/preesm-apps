#!/bin/bash -eu

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm project to test
#   $3 = Workflow file name under $2/Workflows/
#   $4 = Scenario file name under $2/Scenarios/
#   $5 = Binary name under $2/Code after build is done
# Optional arguments :
#   $6 = Command to build the application on the board (see below)
#        by default : 'cd Code/ && make'
#   $7 = Number of measures (or 4 by default)
# Result: in folder ${APPDIR}/finalstats/
#   a list of measurements in .csv files
####################################################################

###################################
## Config
###################################

IP=192.168.100.15 # Odroid IP
USR=odroid # Odroid user login
PSD=odroid # Odroid user password

###################################
## Check
###################################

case $# in
  5)
    BUILD_CMD=$6
    NBREPEAT=4
    ;;
  6)
    BUILD_CMD=$6
    NBREPEAT=4
    ;;
  7)
    BUILD_CMD=$6
    NBREPEAT=$7
    ;;
  *)
    cat << "EOF"
# Usage:
#   $1 = Preesm setup dir
#   $2 = Preesm project to test
#   $3 = Workflow file name under $2/Workflows/
#   $4 = Scenario file name under $2/Scenarios/
#   $5 = Binary name under $2/Code after build is done
# Optional arguments :
#   $6 = Command to build the application on the board (see below)
#        by default : 'cd Code/ && make'
#   $7 = Number of measures (or 4 by default)
EOF
    exit 1
    ;;
esac

PREESMDIR=$1
APPDIR=$2
WORKFLOW=$3
SCENARIO=$4
BIN_NAME=$5

###################################
## Generated / Constant Config
###################################

# parse project name from .project file
PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
# use temporary directory as workspace
WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)

SCRIPT_DIR=$(cd $(dirname ${0}) && pwd)

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

odroid_init_board

echo "Compile code"

# clean generated Code from previous phases
rm -rf ${APPDIR}/Code/generated ${APPDIR}/Code/bin ${APPDIR}/Code/stats ${APPDIR}/Code/finalstats
# Launching Preesm in command line on the project
./commandLinePreesm.sh ${PREESMDIR} ${APPDIR} ${WORKFLOW} ${SCENARIO}

echo "Starting new measurement"
# Whole process from Preesm mapping decision to execution on board and energy retrieval


# Clean previous code version on target
odroid_sudo_exec 'rm -rf ~/Code'

# transfer Code on odroid board
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/Code/* ${USR}@${IP}:/home/${USR}/Code
rsync -e "ssh -i ${SSHKEYFILE}" -au ${SCRIPT_DIR}/onboard_scripts/* ${USR}@${IP}:/home/${USR}/Code/Scripts/

# prepare board for energy measurement
odroid_exec "mkdir -p ~/Code/stats"
odroid_sudo_exec "~/Code/Scripts/configure.sh"
mkdir -p ${APPDIR}/Code/finalstats

# Compile Code
echo "Compile code"
odroid_exec "cd /home/${USR}/Code && ${BUILD_CMD}"

for execit in $(seq 1 $NBREPEAT); do
  echo "execution $execit / $NBREPEAT"
  
  odroid_exec "/home/${USR}/Code/Scripts/energy_measure_simple.sh /home/${USR}/Code/${BIN_NAME}"

  # Copying back the data on local FS
  odroid_exec "mv ~/Code/Scripts/Results ~/Code/Scripts/measure_${execit}" 
  rsync -e "ssh -i ${SSHKEYFILE}" -au ${USR}@${IP}:/home/${USR}/Code/Scripts/measure_${execit} ${APPDIR}/Code/finalstats/
done;

echo ""
echo "Execution done"
echo "  measures in '${APPDIR}/Code/finalstats/'"
echo ""

for execit in $(seq 1 $NBREPEAT); do
  # Computing the energy
  ENERGY=$(${SCRIPT_DIR}/energy_computer_v2.sh ${APPDIR}/Code/finalstats/measure_${execit})
  echo "Energy computation for measurement #${execit}: ${ENERGY}"
  echo "${ENERGY}" > ${APPDIR}/Code/finalstats/measure_${execit}/energy_computed.csv
done

echo ""
echo "Copying quantas and tokens"
mv -f ${APPDIR}/stats/mat/activity/tokens.csv ${APPDIR}/Code/finalstats/
mv -f ${APPDIR}/stats/mat/activity/quanta.csv ${APPDIR}/Code/finalstats/
mv -f ${APPDIR}/stats/mat/activity/custom_quanta.csv ${APPDIR}/Code/finalstats/
echo ""

###################################
## Cleanup
###################################

echo "Done. Cleaning up."
echo " => measures and results in "
echo "    '${APPDIR}/Code/finalstats/'"
echo ""
rm -rf ${WORKSPACE}
exit
