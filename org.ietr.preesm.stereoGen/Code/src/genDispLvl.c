#include "genDispLvl.h"

void genDispLvl(int ndisp, OUT unsigned char *disp){
	int i;	
	for(i=0;i<ndisp;i++){
		disp[i]=i;	
	}
}

