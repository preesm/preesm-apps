/*
	============================================================================
	Name        : energyMonitor.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CeCILL-C, IETR, INSA Rennes
	Description : Energy monitoring functionnalities for Odroid XU3
	============================================================================
*/

#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

typedef struct {
	float v;
	float a;
	float w;
} sensor_data;

typedef struct {
	sensor_data a15;
	sensor_data a7;
	sensor_data gpu;
	sensor_data mem;
} sensors;



void initEnergyMonitoring();

void getSensorsData(sensors *data);

void stopEnergyMonitoring();

#endif
