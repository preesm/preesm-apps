#!/bin/bash -eu

# compute the energy given a folder of measures

[ $# -ne 1 ] && echo "Error: expecting folder" && exit 1

MEASURE_FOLDER=$1

POWERFILES=$(ls ${MEASURE_FOLDER}/*_W*.csv)
MEASURE_RATE=$(cat ${MEASURE_FOLDER}/measure_rate | cut -d' ' -f1)
TOTAL_POWER=0
for FILE in ${POWERFILES}; do
  for MEASURE in $(cat ${FILE}); do
    TOTAL_POWER=$(echo "$TOTAL_POWER + $MEASURE" | bc -l)
  done
done
#TOTAL_POWER=$((TOTAL_POWER / MEASURE_RATE))
TOTAL_POWER=$(echo "$TOTAL_POWER / $MEASURE_RATE" | bc -l)
echo $TOTAL_POWER
