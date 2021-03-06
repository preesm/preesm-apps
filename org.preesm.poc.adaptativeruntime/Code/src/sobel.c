/*
	============================================================================
	Name        : sobel.c
	Author      : kdesnos
	Version     : 1.2
	Copyright   : CECILL-C
	Description : Adapted from sobel-morpho project for brussels demo
	============================================================================
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "sobel.h"

#define clamp(x) (x>255)?255:x

void sobel(int width, int height, int background, unsigned char *input, unsigned char *output){
    int i,j;

    // Apply the filter
    for(j=1; j<height-1; j++){
        for(i=1; i<width-1; i++){
            int gx = -input[(j-1)*width + i-1] -2*input[  j*width + i-1] -input[(j+1)*width + i-1]
                     +input[(j-1)*width + i+1] +2*input[  j*width + i+1] +input[(j+1)*width + i+1];
            int gy = -input[(j-1)*width + i-1] -2*input[(j-1)*width + i] -input[(j-1)*width + i+1]
                     +input[(j+1)*width + i-1] +2*input[(j+1)*width + i] +input[(j+1)*width + i+1];
            int result = sqrt(gx*gx + gy*gy) + background;
            output[(j-1)*width + i] = clamp(result);
        }
    }

    // Fill the left and right sides
    for(j=0; j<height-2 ; j++){
        output[j*width] = 0;
        output[(j+1)*width-1] = 0;
    }
}
