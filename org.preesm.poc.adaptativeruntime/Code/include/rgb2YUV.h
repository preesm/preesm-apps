/*
	============================================================================
	Name        : rgb2YUV.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Transformation of an RGB image into an YUV image.
	============================================================================
*/

#ifndef RGB_2_YUV_H
#define RGB_2_YUV_H
#include "preesm.h"

/**
* This function convert the input YUV image into its RGB equivalent.
*
*/
void rgb2yuv(int width, int height, IN unsigned char *rgb, OUT unsigned char *y, OUT unsigned char *u, OUT unsigned char *v);

#endif
