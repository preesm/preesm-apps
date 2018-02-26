#!/bin/bash

[ "$(whoami)" != "root" ] && echo "Error: must be run as root" && exit 1

# desc : This script enable the sensors and restart all cores at the maximum frequency
# WARNING : If you turn off the EnergyMonitor, that disable the sensors  

INA_DRV_BASEPATH="/sys/bus/i2c/drivers/INA231/"
INA_DRV_ID=$(ls ${INA_DRV_BASEPATH} | grep ".-0045" | cut -d'-' -f1)

#1) Enable sensors
echo 1 > ${INA_DRV_BASEPATH}/${INA_DRV_ID}-0045/enable
echo 1 > ${INA_DRV_BASEPATH}/${INA_DRV_ID}-0040/enable
echo 1 > ${INA_DRV_BASEPATH}/${INA_DRV_ID}-0041/enable

# settle two seconds to the sensors get fully enabled and have the first reading
sleep 2

#2) Restart all cores 
for CORENUMBER in `seq 0 7`; do
	./shutdown_core.sh ${CORENUMBER} ON
done

#3) Set all cores at the maximum frequency
MAX_FREQ_A7=`cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq`
MAX_FREQ_A15=`cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq`
./set_freq.sh A7 ${MAX_FREQ_A7}
./set_freq.sh A15 ${MAX_FREQ_A15}
