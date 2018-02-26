#!/bin/bash -eu

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage: $1 = experiment number (and scenario number)
####################################################################

echo "Starting new measurement"
# Whole process from Preesm mapping decision to execution on board and energy retrieval

###################################
## Check
###################################

[ $# -ne 1 ] && echo "Error: wrong arguments" && echo "usage: $0 EXPERIMENT_ID" && exit 1

###################################
## Config
###################################

IP=192.168.100.15 # Odroid IP
USR=odroid # Odroid user
PSD=odroid # Odroid user password

#PREESMDIR='/home/payvar/preesm-2.8.0-linux.gtk.x86_64'
#PREESMDIR="/home/anmorvan/test/preesm-2.8.0-linux.gtk.x86_64/"
PREESMDIR="/home/anmorvan/test/preesm-2.8.0-SNAPSHOT201802231522-linux.gtk.x86_64/"
 # Experiment ID corresponding to the scenario
EXPERIMENT_ID=$1


###################################
## Generated / Constant Config
###################################

APPDIR=$(cd `dirname ${0}`/../ && pwd)
# parse project name from .project file
PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
# use temporary directory as workspace
WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)

WORKFLOW=Codegen.workflow
SCENARIO="TestComPC_${EXPERIMENT_ID}.scenario"

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

# Clean previous code version on target
odroid_sudo_exec 'rm -rf ~/Code'


if [ ${EXPERIMENT_ID} -ge 64 ]; then
    APPPATH=Code/Stereo
    TARGETSCRIPT=targetScriptStereo.sh
    BINNAME=stereo
else
    APPPATH=Code
    TARGETSCRIPT=targetScriptTestCom.sh
    BINNAME=test-moa
fi

# clean generated Code from previous phases
rm -rf ${APPDIR}/${APPPATH}/generated ${APPDIR}/${APPPATH}/bin ${APPDIR}/${APPPATH}/stats
# Launching Preesm in command line on the project
./commandLinePreesm.sh ${PREESMDIR} ${APPDIR} ${WORKFLOW} ${SCENARIO}

#####################
#####################
## todo : handle affinity in codegen
#rm -f ${APPDIR}/${APPPATH}/generated/main.c
#####################
#####################

# transfer Code on odroid board
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/${APPPATH}/* ${USR}@${IP}:/home/${USR}/Code
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/Scripts/onboard_scripts/* ${USR}@${IP}:/home/${USR}/Code/Scripts/

# Compile Code
odroid_exec "cd ~/Code && ./CMakeGCC.sh"
odroid_exec "cd ~/Code/bin/make && make"
odroid_exec "mkdir -p ~/Code/stats"

if [ ${EXPERIMENT_ID} -ge 64 ]; then
  odroid_exec "cd ~/Code/bin/make && ./stereo"
else
  odroid_exec "cd ~/Code/bin/make && echo -e \"\n\" | ./test_moa"
fi


###################################
## Cleanup
###################################

rm -rf ${WORKSPACE}
exit
    # Repeating N times the launch
    for execit in 0 1 2 3 4 5 6 7 8 9
    do
      # Scenarios between 64 and 3410 correspond to stereo application
      ssh odroid@$IP 'sudo bash -s' < targetScriptTestCom.sh

      # Copying back the power data on PC
      mkdir -p $APPLI/finalstats/mat/activity
      mv -f ~/Temp/odroid/home/odroid/Code/stats/power.csv $APPLI/finalstats/mat/activity/I${execit}_power_$EXPERIMENT_ID.csv

      # Computing the energy
      $APPLI/finalstats/energy_computer/energy_computer $APPLI/finalstats/mat/activity/I${execit}_power_$EXPERIMENT_ID.csv > $APPLI/finalstats/mat/activity/I${execit}_energy_$EXPERIMENT_ID.csv

      # Computing the time
      wc -l < $APPLI/finalstats/mat/activity/I${execit}_power_$EXPERIMENT_ID.csv > $APPLI/finalstats/mat/activity/I${execit}_time_$EXPERIMENT_ID.csv

      # Copying back the activity from the temporary workspace
      mv -f $WORKSPACE/$PROJECT/stats/mat/activity/tokens.csv $APPLI/finalstats/mat/activity/I${execit}_tokens_$EXPERIMENT_ID.csv
      mv -f $WORKSPACE/$PROJECT/stats/mat/activity/quanta.csv $APPLI/finalstats/mat/activity/I${execit}_quanta_$EXPERIMENT_ID.csv
      mv -f $WORKSPACE/$PROJECT/stats/mat/activity/custom_quanta.csv $APPLI/finalstats/mat/activity/I${execit}_custom_quanta_$EXPERIMENT_ID.csv
    done
fi
