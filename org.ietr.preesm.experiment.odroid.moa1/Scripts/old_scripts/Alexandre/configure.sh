#!/bin/bash

# desc : This script enable the sensors and restart all cores at the maximum frequency
# WARNING : If you turn off the EnergyMonitor, that disable the sensors  

#1) Enable sensors
sudo bash -c "echo 1 > /sys/bus/i2c/drivers/INA231/2-0045/enable"
sudo bash -c "echo 1 > /sys/bus/i2c/drivers/INA231/2-0040/enable"
sudo bash -c "echo 1 > /sys/bus/i2c/drivers/INA231/2-0041/enable"
# settle two seconds to the sensors get fully enabled and have the first reading
sleep 2

#2) Restart all cores 
for x in `seq 0 7`; do
	sudo bash shutdown_core.sh $x ON;
done

#3) Set all cores at the maximum frequency
MAX_FREQ_A7=`cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq`;
MAX_FREQ_A15=`cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq`;
sudo bash set_freq.sh A7 $MAX_FREQ_A7;	
sudo bash set_freq.sh A15 $MAX_FREQ_A15;
