/*
	============================================================================
	Name        : difference.c
	Author      : mpelcat
	Version     : 1.2
	Copyright   : CECILL-C
	Description :
	============================================================================
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "sobel.h"

void difference(int width, int height, int nbSlices, IN unsigned char *input, IN unsigned char *previous, OUT unsigned char *output, OUT unsigned char *result){
    int i,j;

	if ((height % nbSlices) != 0)
	{
		fprintf(stderr, "Image height (%d) should be divisible by nbSlices (%d).\n", height, nbSlices);
#ifdef _WIN32
        system("PAUSE");
#endif
		exit(1);
	}

    // Copy input into output
    for(j=0; j<height/nbSlices; j++){
        for(i=0; i<width; i++){
            output[j*width + i] = input[j*width + i];
        }
    }

    // Set input-previous into result
    for(j=0; j<height/nbSlices; j++){
        for(i=0; i<width; i++){
        	result[j*width + i] = input[j*width + i]-previous[j*width + i];
        }
    }
}
