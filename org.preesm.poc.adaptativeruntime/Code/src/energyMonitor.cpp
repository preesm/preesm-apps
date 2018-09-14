/*
 ============================================================================
 Name        : energyMonitor.cpp
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C, IETR, INSA Rennes
 Description : Energy monitoring functionnalities for Odroid XU3
 ============================================================================
 */

#include "energyMonitor/getnode.h"
#include "energyMonitor.h"
#include <stdio.h>

static GetNode *getNode;

void initEnergyMonitoring() {
	getNode = new GetNode();
	getNode->OpenINA231();
}

void getSensorsData(sensors *data){
	getNode->GetINA231();

	data->a15.a = getNode->armuA;
	data->a15.v = getNode->armuV;
	data->a15.w = getNode->armuW;

	data->a7.a = getNode->kfcuA;
	data->a7.v = getNode->kfcuV;
	data->a7.w = getNode->kfcuW;

	data->mem.a = getNode->memuA;
	data->mem.v = getNode->memuV;
	data->mem.w = getNode->memuW;

	data->gpu.a = getNode->g3duA;
	data->gpu.v = getNode->g3duV;
	data->gpu.w = getNode->g3duW;
}

void stopEnergyMonitoring() {
	getNode->CloseINA231();
}
