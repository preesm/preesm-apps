#!/bin/bash -eu
# desc : This script switch ON or OFF a core
# arg1 : core ID
# arg2 : ON or OFF

[ $# -ne 2 ] && echo "Error: requires 2 arguments" && exit 1
[ "$(whoami)" != "root" ] && echo "Error: must be run as root" && exit 2

CORE_ID=$1
TARGET_MODE=$(echo $2 | awk '{print toupper($0)}')

case ${TARGET_MODE} in
  ON)
    TARGET_MODE_ID=1
    ;;
  OFF)
    TARGET_MODE_ID=0
    ;;
  *)
    echo "Invalid argument";
    exit 3
    ;;
esac

MODE_PATH="/sys/devices/system/cpu/cpu${CORE_ID}/online"
CURRENT_MODE_ID=$(cat "${MODE_PATH}")

[ "${CURRENT_MODE_ID}" == "${TARGET_MODE_ID}" ] && echo "CPU ${CORE_ID} already ${TARGET_MODE}" && exit 0

echo ${TARGET_MODE_ID} > ${MODE_PATH}

