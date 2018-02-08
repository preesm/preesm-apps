#!/bin/sh

####################################################################
# Generating an application with Preesm and simulating its execution
# energy consumption on an Odroid XU3 board.
# Usage: $1 = experiment number (and scenario number)
# Usage: $2 = workspace number
####################################################################

echo "Starting new simulation"
# Whole process from Preesm mapping decision to execution on board and energy retrieval

IP=192.168.0.2 # Odroid IP
APPLI='/home/mpelcat/Projets/preesm-private/org.ietr.preesm.experiment.odroid.moa1'
WORKSPACENR=$2
WORKSPACE='/home/mpelcat/Projets/Eclipse/Mars-Test/workspace'$WORKSPACENR
ECLIPSE='/home/mpelcat/Projets/Eclipse/Mars-Test/eclipse'
PROJECT=org.ietr.preesm.experiment.odroid.moa1
 # Experiment ID corresponding to the scenario
EXPERIMENT_ID=$1

if [ -z $1 ]
then # if no parameter
  echo "usage: $0 EXPERIMENT_ID WORKSPACENR"
else

    # Initializing Preesm in command line on the project
    # This copies the project into the workspace before Preesm works on it
    ./PREESM_cli_init.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT Codegen.workflow TestComPC_$1.scenario

    # Launching Preesm in command line on the project
    # If init is repeated, mapping is deterministic
    ./PREESM_cli_launch.sh $APPLI $WORKSPACE $ECLIPSE $PROJECT Codegen.workflow TestComPC_$1.scenario

    # Copying back the activity from the temporary workspace
    mv -f $WORKSPACE/$PROJECT/stats/mat/activity/tokens.csv $APPLI/finalstats/mat/activity/I0_tokens_$EXPERIMENT_ID.csv
    mv -f $WORKSPACE/$PROJECT/stats/mat/activity/quanta.csv $APPLI/finalstats/mat/activity/I0_quanta_$EXPERIMENT_ID.csv
    mv -f $WORKSPACE/$PROJECT/stats/mat/activity/custom_quanta.csv $APPLI/finalstats/mat/activity/I0_custom_quanta_$EXPERIMENT_ID.csv
fi
