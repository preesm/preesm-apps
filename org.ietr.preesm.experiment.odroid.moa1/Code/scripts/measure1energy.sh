#!/bin/sh

####################################################################
# Generating an application with Preesm and measuring its execution
# energy consumption on an Odroid XU3 board.
# Usage: $1 = experiment number (and scenario number)
####################################################################

echo "Starting new measurement"
# Whole process from Preesm mapping decision to execution on board and energy retrieval

IP=192.168.0.2 # Odroid IP
APPLI='/home/mpelcat/Projets/preesm-private/org.ietr.preesm.experiment.odroid.moa1'
WORKSPACE='/home/mpelcat/Projets/Eclipse/Mars-Test/workspace'
ECLIPSE='/home/mpelcat/Projets/Eclipse/Mars-Test/eclipse'
PROJECT=org.ietr.preesm.experiment.odroid.moa1
 # Experiment ID corresponding to the scenario
EXPERIMENT_ID=$1

if [ -z $1 ]
then # if no parameter
  echo "usage: $0 EXPERIMENT_ID"
else

    # Removing previous code version on target
    ssh odroid@$IP 'sudo rm -R ~/Code'

    # Testing whether the directory has effectively been deleted
    while [ -d ~/Temp/odroid/home/odroid/Code ]
    do
	sleep 1
    done

    ssh odroid@$IP 'mkdir ~/Code'

    # Initializing Preesm in command line on the project
    # This copies the project into the workspace before Preesm works on it


    # Running code on the Odroid target
    if [ "$1" -ge "3411" ]
    then
        # Scenarios over 3411 are IBSDF applications
        ./PREESM_cli_init.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT CodegenIBSDF.workflow TestComPC_$1.scenario
    else
        # Scenarios between 0 and 3410 are PiMM applications
        ./PREESM_cli_init.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT Codegen.workflow TestComPC_$1.scenario
    fi

    # Launching Preesm in command line on the project
    # If init is repeated, mapping is deterministic
    if [ "$1" -ge "3411" ]
    then
        # Scenarios over 3411 are IBSDF applications
        ./PREESM_cli_launch.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT CodegenIBSDF.workflow TestComPC_$1.scenario
    else
        # Scenarios between 0 and 3410 are PiMM applications
        ./PREESM_cli_launch.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT Codegen.workflow TestComPC_$1.scenario
    fi

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
