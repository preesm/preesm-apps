/*
	============================================================================
	Name        : nbSliceSetter.cpp
	Author      : jheulot
	Version     :
	Copyright   : CECILL-C
	Description : Set nbSlice Parameter
	============================================================================
*/

#include "nbSliceSetter.h"
	
#include <stdio.h>
#include <time.h>

#define NCONFIG 20

void nbSliceSetter (Param height, Param* nbSlice){
	int configs[NCONFIG];

	int second = time(NULL);

	int nbConfigs=0;
	int testedSlice=1;
	while(nbConfigs<NCONFIG && testedSlice <= height){
		if((height % testedSlice) == 0)
			configs[nbConfigs++] = testedSlice;
		testedSlice++;
	}

	int selectedConfig = second%nbConfigs;

	*nbSlice = configs[selectedConfig];
}
