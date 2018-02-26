#!/bin/bash
# desc : This script stress a cluster with the program "stress" and profile it.
# 		 To be sure that you stress the cores that you want, you have to use the cmd "taskset" to set a afinity of the program stress with select cores 
# arg1 : cluster : A7 or A15
# arg2 : number of core
# arg3 : other core OFF or ON


# WARNING : If you turn off the EnergyMonitor, that disable the sensors ! So DON'T do that during your profiling !
# WARNING : The core 0 (of the A7 cluster) can't be switch off !
# WARNING : For the cluster A7, when you set the maximum frequency (1,4GHz) after shutdown cores, all cores are automatically switch on ! (That can occur in toher situations)


#1) Run configure.sh to enable the sensor and restart all cores
sudo bash configure.sh;

#2) Get the table of frequencies for a cluster  
if [ "$1" == "A7" ];then
	#-------------------------------> TODO <------------------------------------
	CLUSTER_FREQ=`cat ???`;
elif [ "$1" == "A15" ];then
	#-------------------------------> TODO <------------------------------------
	CLUSTER_FREQ=`cat ???`;
else
	echo "Invalide argument";
	exit
fi

#3) Switch off the cores not use if OFF is select
if [ "$3" == "OFF" ];then
	for j in `seq -s " " 3 -1 $2`;do
		if [ "$1" == "A7" ];then
			sudo bash shutdown_core.sh $j OFF;
		elif [ "$1" == "A15" ];then
			sudo bash shutdown_core.sh $((j+4)) OFF;
		fi
	done
fi

#4) Main loop of profiling
#4.1) Iterate the profiling for all frequencies of the cluster
for i in $CLUSTER_FREQ; do
	
	#4.2) Set the frequency of the cluster	
	sudo bash set_freq.sh $1 $i;	

	#4.3) Iterate the profiling on the number of core select in arg 2
	for j in `seq -s " " $(($2-1)) -1 0`; do
		
		#4.4) Compute the cpu target for the cmd taskset
		if [ "$1" == "A7" ];then
			CPU_TARGET=`seq -s "," 0 $(($j))`
		elif [ "$1" == "A15" ];then
			CPU_TARGET=`seq -s "," 4 $(($j+4))`
		fi	

		#4.5) To be sure that the cores are correctly shutdwon for the cluster A7 (cf warning)
		if [ "$1" == A7 -a "$3" == "OFF" ];then
			for j in `seq -s " " 3 -1 $(($j+1))`;do
					sudo bash shutdown_core.sh $j OFF;
			done
		fi	

		#4.6) Run the program stress in the select cores and the script energy_measure on the program stress		
		sudo taskset -c $CPU_TARGET stress -c $(($j+1)) --timeout 30s & sudo bash energy_measure.sh $1 stress;
		
		#4.7) Switch off a cores if OFF is select
		if [ "$3" == "OFF" -a $j != 0 ];then
			if [ "$1" == "A7" ];then
				sudo bash shutdown_core.sh $j OFF;
			elif [ "$1" == "A15" ];then
				sudo bash shutdown_core.sh $((j+4)) OFF;
			fi
		fi 
	done
	
	#4.8) Switch on cores if it's necessary
	if [ "$3" == "OFF" ];then
		for j in `seq -s " " $(($2-1)) -1 1`;do
			if [ "$1" == "A7" ];then
				sudo bash shutdown_core.sh $j ON;
			elif [ "$1" == "A15" ];then
				sudo bash shutdown_core.sh $((j+4)) ON;
			fi
		done
	fi
done

#5) Reset the maximum frequency
MAX_FREQ_A7=`cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq`;
MAX_FREQ_A15=`cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq`;
sudo bash set_freq.sh A7 $MAX_FREQ_A7;	
sudo bash set_freq.sh A15 $MAX_FREQ_A15;
