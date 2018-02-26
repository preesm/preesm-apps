#!/bin/bash
# desc : This script measure the power, intensity, voltage and temperature (of the cluster A15 only) of a program.
#		 For each case A7, A15 or All, the main loop is duplicated and adaptated to reduce the overhead.
#        For each case the main loop is iterate while the PID of the program is alive.
# arg1 : cluster => A7, A15 or All
# arg2 : program name

total=0.0
measurement_number=0


INA_DRV_ID=$(ls /sys/bus/i2c/drivers/INA231/ | grep ".-0045" | cut -d'-' -f1)

if [ $1 == "A7" ]; then
	while [ ! -z "$(pidof $2)" ]; do

		#Get the values of the sensors
		CPU_W_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_W`
		CPU_A_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_A`
		CPU_V_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_V`

		#Write there values in tables
		tab_W[$measurement_number]=`echo "$CPU_W_A7"`
		tab_A[$measurement_number]=`echo "$CPU_A_A7"`
		tab_V[$measurement_number]=`echo "$CPU_V_A7"`

		#Incerment the index table
		measurement_number=$((measurement_number+1))

		# 10 Hz measurements
		#sleep 0.1s
	done


elif [ $1 == "A15" ];then
	while [ ! -z "$(pidof $2)" ]; do
	
		#Get the values of the sensors
		CPU_W_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_W`
		CPU_A_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_A`
		CPU_V_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_V`

		CPU5_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 1 {print $3}'`
		CPU6_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 2 {print $3}'`
		CPU7_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 3 {print $3}'`
		CPU8_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 4 {print $3}'`

		#Write there values in tables
		tab_W[$measurement_number]=`echo "$CPU_W_A15"`
		tab_A[$measurement_number]=`echo "$CPU_A_A15"`
		tab_V[$measurement_number]=`echo "$CPU_V_A15"`

		tab_T_5[$measurement_number]=`echo "$CPU5_TEMP"`
		tab_T_6[$measurement_number]=`echo "$CPU6_TEMP"`
		tab_T_7[$measurement_number]=`echo "$CPU7_TEMP"`
		tab_T_8[$measurement_number]=`echo "$CPU8_TEMP"`

		#Incerment the index table
		measurement_number=$((measurement_number+1))

		# 10 Hz measurements
		#sleep 0.1s
	done


elif [ $1 == "All" ];then
	while [ ! -z "$(pidof $2)" ]; do
	
		#Get the values of the sensors
		CPU_W_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_W`
		CPU_W_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_W`
		CPU_W_ME=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0041/sensor_W`
	
		CPU_A_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_A`
		CPU_A_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_A`
		CPU_A_ME=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0041/sensor_A`

		CPU_V_A7=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0045/sensor_V`
		CPU_V_A15=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0040/sensor_V`
		CPU_V_ME=`cat /sys/bus/i2c/drivers/INA231/${INA_DRV_ID}-0041/sensor_V`

		CPU5_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 1 {print $3}'`
		CPU6_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 2 {print $3}'`
		CPU7_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 3 {print $3}'`
		CPU8_TEMP=`cat /sys/devices/10060000.tmu/temp | awk 'FNR == 4 {print $3}'`

		#Write there values in tables
		tab_W[$measurement_number]=`echo "$CPU_W_A7 $CPU_W_A15 $CPU_W_ME ; "`
		tab_A[$measurement_number]=`echo "$CPU_A_A7 $CPU_A_A15 $CPU_A_ME ; "`
		tab_V[$measurement_number]=`echo "$CPU_V_A7 $CPU_V_A15 $CPU_V_ME ; "`

		tab_T_5[$measurement_number]=`echo "$CPU5_TEMP"`
		tab_T_6[$measurement_number]=`echo "$CPU6_TEMP"`
		tab_T_7[$measurement_number]=`echo "$CPU7_TEMP"`
		tab_T_8[$measurement_number]=`echo "$CPU8_TEMP"`

		#Incerment the index table
		measurement_number=$((measurement_number+1))

		# 10 Hz measurements
		#sleep 0.1s
	done
else
	echo "Invalide argument";
	exit
fi

mkdir -p Results
#Write the values in files
echo "${tab_W[@]}" >> Results/power.csv;
echo "${tab_A[@]}" >> Results/intensity.csv;
echo "${tab_V[@]}" >> Results/tension.csv;

if [ $1 == "A15" -o $1 == "All" ];then
	echo "${tab_T_5[@]}" >> Results/temp_core_5.csv;
	echo "${tab_T_6[@]}" >> Results/temp_core_6.csv;
	echo "${tab_T_7[@]}" >> Results/temp_core_7.csv;
	echo "${tab_T_8[@]}" >> Results/temp_core_8.csv;
fi


