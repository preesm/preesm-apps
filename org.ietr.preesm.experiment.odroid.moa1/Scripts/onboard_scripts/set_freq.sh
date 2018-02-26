#!/bin/bash
# desc : This script set a frequency for a cluster
# arg1 : cluster A7 or A15
# arg2 : frequency

[ $# -ne 2 ] && echo "Error: requires 2 arguments" && exit 1
[ "$(whoami)" != "root" ] && echo "Error: must be run as root" && exit 2

CLUSTER_NAME=$(echo $1 | awk '{print toupper($0)}')
TARGET_FREQ=$2

case ${CLUSTER_NAME} in
  A7)
    CPU_ID=0
    ;;
  A15)
    CPU_ID=4
    ;;
  *)
    echo "Invalid cluster name";
    exit 3
    ;;
esac

GOVERNOR_PATH="/sys/devices/system/cpu/cpu${CPU_ID}/cpufreq/scaling_governor"
FREQ_PATH="/sys/devices/system/cpu/cpu${CPU_ID}/cpufreq/scaling_setspeed"
CURRENT_GOVERNOR=$(cat "${GOVERNOR_PATH}")
TARGET_GOVERNOR="userspace"

#1) Set scaling_governor
if [ "${CURRENT_GOVERNOR}" != "${TARGET_GOVERNOR}" ]; then
	echo "${TARGET_GOVERNOR}" > "${GOVERNOR_PATH}"
	echo "Scaling_governor of the cluster ${CLUSTER_NAME} is set to '${TARGET_GOVERNOR}'"
fi

#2) Set frequency
echo "${TARGET_FREQ}" > "${FREQ_PATH}"

#3) Verification
CUR_FREQ=$(cat "${FREQ_PATH}")
if [ "${CUR_FREQ}" != "${TARGET_FREQ}" ]; then
	echo "The cluster ${CLUSTER_NAME} frequency can't be set to ${TARGET_FREQ} Hz"
	echo "  => the current frequency of the cluster ${CLUSTER_NAME} is ${CUR_FREQ} Hz"
else
	echo "The frequency of the cluster ${CLUSTER_NAME} is set to ${CUR_FREQ} Hz"
fi



