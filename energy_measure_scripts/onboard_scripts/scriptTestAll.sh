#!/bin/bash

NBCORES=4

for CLUSTER in A7 A15; do
  for OTHER_ACTIVITY in ON OFF; do
    rm -rf Results
    ./script_stress_conso.sh ${CLUSTER} ${NBCORES} ${OTHER_ACTIVITY}
    mv Results Results_${CLUSTER}_${NBCORES}_${OTHER_ACTIVITY}
  done
done

exit
