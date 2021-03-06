#!/bin/bash -eu
# desc : This script measure the power, intensity, voltage and temperature (of the cluster A15 only) of a program.
#		 For each case A7, A15 or All, the main loop is duplicated and adaptated to reduce the overhead.
#        For each case the main loop is iterate while the PID of the program is alive.
# arg1 : cluster => A7, A15 or All
# arg2 : program name


[ $# -ne 2 ] && echo "Error: requires 2 arguments" && exit 1

SCRIPT_DIR=$(cd `dirname ${0}`/ && pwd)
CLUSTER_NAME=$(echo $1 | awk '{print toupper($0)}')
PROGRAM_NAME=$2

TEMPERATURES_PATH="/sys/devices/10060000.tmu/temp"
INA_DRV_BASEPATH="/sys/bus/i2c/drivers/INA231/"
INA_DRV_ID=$(ls ${INA_DRV_BASEPATH} | grep ".-0045" | cut -d'-' -f1)

A15_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0040/"
ME_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0041/"
A7_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0045/"
GPU_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0044/"

function print_sensor_value() {
  DEVICE=$1
  SENSOR=$2
  case ${DEVICE} in
    A7)
      DEV_INA_DRV_PATH="${A7_INA_DRV_PATH}"
      ;;
    A15)
      DEV_INA_DRV_PATH="${A15_INA_DRV_PATH}"
      ;;
    ME)
      DEV_INA_DRV_PATH="${ME_INA_DRV_PATH}"
      ;;
    GPU)
      DEV_INA_DRV_PATH="${GPU_INA_DRV_PATH}"
      ;;
    *)
      echo "Error: invalid device '${DEVICE}'"
      exit 1
      ;;
  esac
  case ${SENSOR} in
    W | A | V)
      cat "${DEV_INA_DRV_PATH}/sensor_${SENSOR}"
      ;;
    *)
      echo "Error: invalid device '${DEVICE}'"
      exit 1
      ;;
  esac
}

function print_cpu_temp() {
  CORE_ID=$1
  case ${CORE_ID} in
    0 | 1 | 2 | 3)
      echo "Error: cannot get temperature for cores 0 to 3."
      exit 1
      ;;
    4 | 5 | 6 | 7)
      TEMP_ID=$((CORE_ID - 3))
      ;;
    GPU)
      TEMP_ID=5
      ;;
    *)
      echo "Error: unsupported core id ${CORE_ID}."
      exit 1
      ;;
  esac
  cat ${TEMPERATURES_PATH} | awk "FNR == ${TEMP_ID} {print \$3}"
}

case ${CLUSTER_NAME} in
  A7)
    DEV_LIST="A7"
    ;;
  A15)
    DEV_LIST="A15"
    ;;
  ALL)
    DEV_LIST="A7 A15 ME GPU"
    ;;
  *)
    echo "Invalid cluster name (expect A7, A15 or All)";
    exit
    ;;
esac

declare -A measures

# init array. Necessary to avoid unbound variable error
for DEV in ${DEV_LIST}; do
  for SENSOR in W A V; do
    measures[${DEV},${SENSOR}]=""
  done
  if [ "${DEV}" == "A15" ]; then
    # also measure temperature for A15
    for CORE_ID in $(seq 4 7); do
      measures[${DEV},T${CORE_ID}]=""
    done
    if [ "${DEV}" == "GPU" ]; then
      VAL=$(print_cpu_temp GPU)
      measures[${DEV},T]=""
    fi
  fi
done

# Querry measures
start_ts=$(date '+%s%N')
while [ ! -z "$(pidof $2)" ]; do
  for DEV in ${DEV_LIST}; do
    for SENSOR in W A V; do
      VAL=$(print_sensor_value ${DEV} ${SENSOR})
      measures[${DEV},${SENSOR}]+=" ${VAL}"
    done
    if [ "${DEV}" == "A15" ]; then
      # also measure temperature for A15
      for CORE_ID in $(seq 4 7); do
        VAL=$(print_cpu_temp ${CORE_ID})
        measures[${DEV},T${CORE_ID}]+=" ${VAL}"
      done
    fi
    if [ "${DEV}" == "GPU" ]; then
      VAL=$(print_cpu_temp GPU)
      measures[${DEV},T]+=" ${VAL}"
    fi
  done
done
end_ts=$(date '+%s%N')
total_ts=$((end_ts - start_ts))

#Write the values in files
mkdir -p ${SCRIPT_DIR}/Results
for DEV in ${DEV_LIST}; do
  for SENSOR in W A V; do
    echo "${measures[${DEV},${SENSOR}]}" > ${SCRIPT_DIR}/Results/${DEV}_${SENSOR}.csv
  done
  if [ "${DEV}" == "A15" ]; then
    # also write temperature for A15
    for CORE_ID in $(seq 4 7); do
      echo "${measures[${DEV},T${CORE_ID}]}" > ${SCRIPT_DIR}/Results/CPU${CORE_ID}_T.csv
    done
  fi
  if [ "${DEV}" == "GPU" ]; then
    echo "${measures[${DEV},T]}" > ${SCRIPT_DIR}/Results/GPU_T.csv
  fi
done
echo "${total_ts} ns" > ${SCRIPT_DIR}/Results/measure_time.csv

exit 0
