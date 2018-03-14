#!/bin/bash -eu

# compute the energy given a folder of measures

[ $# -ne 1 ] && echo "Error: expecting folder" && exit 1

MEASURE_FOLDER=$1

POWERFILES=$(ls ${MEASURE_FOLDER}/*_W*.csv)
MEASURE_TIME=$(cat ${MEASURE_FOLDER}/time_ns.csv | cut -d' ' -f1)
TOTAL_POWER=0
for FILE in ${POWERFILES}; do
  TOTAL_MEASURES=0
  for MEASURE in $(cat ${FILE}); do
    TOTAL_POWER=$(echo "$TOTAL_POWER + $MEASURE" | bc -l)
    TOTAL_MEASURES=$((TOTAL_MEASURES + 1))
  done
done
MEASURE_RATE=
#Time is in nanoseconds, so divide by 10^9
TOTAL_POWER=$(echo "$TOTAL_POWER / ($TOTAL_MEASURES / ($MEASURE_TIME / 1000000000.0))" | bc -l)
echo $TOTAL_POWER
