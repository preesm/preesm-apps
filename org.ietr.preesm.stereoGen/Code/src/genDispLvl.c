/*
	============================================================================
	Name        : genDispLvl.c
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : generate ndisp level in an array.
	============================================================================
*/

#include "genDispLvl.h"

void genDispLvl(int ndisp, OUT unsigned char *disp){
	int i;	
	for(i=0;i<ndisp;i++){
		disp[i]=i;	
	}
}

