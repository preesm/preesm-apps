#!/bin/bash
# desc : This script set a frequency for a cluster
# arg1 : cluster A7 or A15
# arg2 : frequency

FREQ=$2

if [ $1 == "A7" ];then
	CPU_ID=0
elif [ $1 == "A15" ];then
	CPU_ID=4
else
	echo "Invalide argument";
	exit
fi

#1) Set scaling_governor
if [ `cat /sys/devices/system/cpu/cpu"$CPU_ID"/cpufreq/scaling_governor` != "QUEL_GOUVERNEUR?" ]; then
	echo userspace > /sys/devices/system/cpu/cpu"$CPU_ID"/cpufreq/scaling_governor
	echo "Scaling_governor of the cluster of cpu $1 is set to XXXX:"
fi

#2) Set frequency
sudo bash -c "echo $FREQ >/sys/devices/system/cpu/cpu"$CPU_ID"/cpufreq/scaling_setspeed"

#3) Verification
CUR_FREQ=`cat /sys/devices/system/cpu/cpu"$CPU_ID"/cpufreq/scaling_setspeed`
if [ $CUR_FREQ != $FREQ ]; then
	echo "The cluster $1 can't be set at $FREQ Hz"
	echo "  => the current frequency of the cluster $1 is $CUR_FREQ Hz"
else
	echo "The frequency of the cluster $1 is set at $CUR_FREQ Hz"
fi



