#!/bin/bash
# desc : This script measure the power, intensity, voltage and temperature (of the cluster A15 only) of a program.
#		 For each case A7, A15 or All, the main loop is duplicated and adaptated to reduce the overhead.
#        For each case the main loop is iterate while the PID of the program is alive.
# arg1 : cluster => A7, A15 or All
# arg2 : program name


[ $# -ne 2 ] && echo "Error: requires 2 arguments" && exit 1
[ "$(whoami)" != "root" ] && echo "Error: must be run as root" && exit 2

SCRIPT_DIR=$(cd `dirname ${0}`/ && pwd)
CLUSTER_NAME=$(echo $1 | awk '{print toupper($0)}')
PROGRAM_NAME=$2

TEMPERATURES_PATH="/sys/devices/10060000.tmu/temp"
INA_DRV_BASEPATH="/sys/bus/i2c/drivers/INA231/"
INA_DRV_ID=$(ls ${INA_DRV_BASEPATH} | grep ".-0045" | cut -d'-' -f1)

A15_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0040/"
ME_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0041/"
A7_INA_DRV_PATH="${INA_DRV_BASEPATH}/${INA_DRV_ID}-0045/"

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
    DEV_LIST="A7 A15 ME"
    ;;
  *)
    echo "Invalid cluster name (expect A7, A15 or All)";
    exit
    ;;
esac

total=0.0
measurement_number=0

while [ ! -z "$(pidof $2)" ]; do
  for DEV in ${DEV_LIST}; do
    tab_W[${measurement_number}]=$(print_sensor_value ${DEV} W)
    tab_A[${measurement_number}]=$(print_sensor_value ${DEV} A)
    tab_V[${measurement_number}]=$(print_sensor_value ${DEV} V)
    if [ "${DEV}" == "A15" ]; then
      # also measure temperature for A15
      tab_T_4[$measurement_number]=$(print_cpu_temp 4)
      tab_T_5[$measurement_number]=$(print_cpu_temp 5)
      tab_T_6[$measurement_number]=$(print_cpu_temp 6)
      tab_T_7[$measurement_number]=$(print_cpu_temp 7)
    fi
  done
  
  measurement_number=$((measurement_number+1))
  # 10 Hz measurements
  sleep 0.1s
done

mkdir -p ${SCRIPT_DIR}/Results
#Write the values in files
echo "${tab_W[@]}" >> ${SCRIPT_DIR}/Results/power.csv;
echo "${tab_A[@]}" >> ${SCRIPT_DIR}/Results/intensity.csv;
echo "${tab_V[@]}" >> ${SCRIPT_DIR}/Results/tension.csv;

case ${DEV_LIST} in
  *A15*)
    echo "${tab_T_4[@]}" >> ${SCRIPT_DIR}/Results/temp_core_4.csv;
    echo "${tab_T_5[@]}" >> ${SCRIPT_DIR}/Results/temp_core_5.csv;
    echo "${tab_T_6[@]}" >> ${SCRIPT_DIR}/Results/temp_core_6.csv;
    echo "${tab_T_7[@]}" >> ${SCRIPT_DIR}/Results/temp_core_7.csv;
    ;;
esac

exit 0
