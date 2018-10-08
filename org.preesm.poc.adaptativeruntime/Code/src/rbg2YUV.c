/*
	============================================================================
	Name        : rgb2YUV.c
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Transformation of an RGB image into a YUV image.
	============================================================================
*/

#include "rgb2YUV.h"

#define clamp(x) (x>255)? 255 : ((x<0)? 0 : x);

void rgb2yuv(int width, int height, unsigned char *rgb, unsigned char *y, unsigned char *u, unsigned char *v){
    int i,j;
	int size = height*width;

	// Luminance
    for(i=0; i< height; i++){
        for(j=0; j < width; j++){
			int idx = i*width + j;
			int idxUV = i/2*width/2 + j/2;

			int r = rgb[idx + 2*height*width];
			int g = rgb[idx + height*width];
			int b = rgb[idx ];

            y[idx] = ((66*r + 129*g + 25*b + 128 )>> 8)+16;
		}
    }
	
	// Chrominance
	for(i=0; i< height/2; i++){
        for(j=0; j < width/2; j++){
			
			int idx = i*width/2 + j;
			int idxRGB = 2*i*width + 2*j;
			
			int avgB = (rgb[idxRGB + 2*width*height] + 
			        rgb[idxRGB + 1 + 2*width*height] + 
				    rgb[idxRGB + width + 2*width*height] + 
				    rgb[idxRGB + 1+ width + 2*width*height])/4;
			int avgG = (rgb[idxRGB + width*height] + 
			        rgb[idxRGB + 1 + width*height] + 
				    rgb[idxRGB + width + width*height] + 
				    rgb[idxRGB + 1+ width + width*height])/4;
			int avgR = (rgb[idxRGB] + 
			        rgb[idxRGB + 1 ] + 
				    rgb[idxRGB + width ] + 
				    rgb[idxRGB + 1+ width ])/4;;
			
			u[idx] = ((-38*avgR - 74*avgG + 112* avgB + 128) >> 8) + 128;
			v[idx] = ((112*avgR - 94*avgG - 18* avgB + 128) >> 8) + 128;;
		}
	}
}

