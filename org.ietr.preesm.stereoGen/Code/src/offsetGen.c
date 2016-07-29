/*
	============================================================================
	Name        : offsetGen.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CeCILL-C, IETR, INSA Rennes
	Description : Generation of an array of the offsets used in the 
	              computation of the depth map.
	============================================================================
*/

#include "offsetGen.h"


void deltasGen (int nbIterations, unsigned char *deltas){
	int i;
	int sum = 0;
	for(i=0; i< nbIterations; i++){
		deltas[i] = 2*sum + 1;
		sum += deltas[i];
		deltas[i] %= 32;
	}
//	deltas[0] =1;
//	deltas[1] =4;
//	deltas[2] =9;
//	deltas[3] =16;
//	deltas[4] =25;
//	deltas[5] =3;
}
