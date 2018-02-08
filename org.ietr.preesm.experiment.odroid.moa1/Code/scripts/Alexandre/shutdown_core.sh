#!/bin/bash
# desc : This script switch ON or OFF a core
# arg1 : core ID
# arg2 : ON or OFF

#If you want to switch on a core and it's offline
if [ $2 == "ON" ];then
	if [ `cat /sys/devices/system/cpu/cpu$1/online` == 0 ]; then
		sudo bash -c "echo 1 > /sys/devices/system/cpu/cpu$1/online";
		echo "Cpu $1 is ON."
	fi
#Else if you want to switch off a core and it's online 
elif [ $2 == "OFF" ];then
	if [ `cat /sys/devices/system/cpu/cpu$1/online` == 1 ]; then
		sudo bash -c "echo 0 > /sys/devices/system/cpu/cpu$1/online";
		echo "Cpu $1 is OFF."
	fi
#Else it's a invalide argument 
else
	echo "Invalide argument";
	exit
fi
