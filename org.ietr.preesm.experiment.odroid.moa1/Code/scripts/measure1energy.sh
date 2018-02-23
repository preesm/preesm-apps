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

#APPDIR='/home/payvar/preesm-2.8.0-linux.gtk.x86_64/workspace/org.ietr.preesm.experiment.odroid.moa1'
APPDIR="/home/anmorvan/test/max_droid/org.ietr.preesm.experiment.odroid.moa1/"
#PREESMDIR='/home/payvar/preesm-2.8.0-linux.gtk.x86_64'
PREESMDIR="/home/anmorvan/test/preesm-2.8.0-linux.gtk.x86_64/"
 # Experiment ID corresponding to the scenario
EXPERIMENT_ID=$1


###################################
## Generated Config
###################################

# parse project name from .project file
PROJECT=$(cat $APPDIR/.project | grep -oPm1 "(?<=<name>)[^<]+")
# use temporary directory as workspace
WORKSPACE=$(mktemp -d --suffix=_preesm-workspace)


WORKFLOW="Codegen.workflow"
SCENARIO="TestComPC_${EXPERIMENT_ID}.scenario"

# SSH key file name
SSHKEYFILE=id_rsa_odroid

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

# clean generated Code from previous phases
rm -rf ${APPDIR}/Code/generated ${APPDIR}/Code/bin
# Launching Preesm in command line on the project
./commandLinePreesm.sh ${PREESMDIR} ${APPDIR} ${WORKFLOW} ${SCENARIO}

# transfer Code on odroid board
rsync -e "ssh -i ${SSHKEYFILE}" -au ${APPDIR}/Code ${USR}@${IP}:/home/${USR}/

# Compile Code
odroid_exec "cd ~/Code && ./CMakeGCC.sh"
odroid_exec "cd ~/Code/bin/make && make"


#cd ~/Code
#rm -r bin
#./CMakeGCC.sh
#cd bin/make
#make
#cd ~/Code
#mkdir stats


###################################
## Cleanup
###################################

rm -rf ${WORKSPACE}
exit

    # Copying the code to the Odroid target. The code is in the workspace copy of the project.
    cp -Rf $WORKSPACE/$PROJECT/Code ~/Temp/odroid/home/odroid

    # Repeating N times the launch
    for execit in 0 1 2 3 4 5 6 7 8 9
    do
      # Running code on the Odroid target
      if [ "$1" -ge "64" ]
      then
        
        # Running code on the Odroid target
        if [ "$1" -ge "3411" ]
        then
            # Scenarios over 3411 correspond to crypto application
            ssh odroid@$IP 'sudo bash -s' < targetScriptCrypto.sh
        else
            # Scenarios between 64 and 3410 correspond to stereo application
            ssh odroid@$IP 'sudo bash -s' < targetScriptTestCom.sh
        fi
      else
          # Scenarios under 64 correspond to testcom application
          ssh odroid@$IP 'sudo bash -s' < targetScriptTestCom.sh
      fi

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
