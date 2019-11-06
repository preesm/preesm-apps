/*
	============================================================================
	Name        : difference.h
	Author      : mpelcat
	Version     : 1.1
	Copyright   : CeCILL-C
	Description : Difference between two images
	============================================================================
*/

#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "preesm.h"

/**
* Function that computes the pixelwise difference of slices input - previous and returns it on result.
* The function also returns on output the same image as input.
*
* @param width
*        The width of the processed image
* @param heigth
*        The heigth of the processed image
* @param nbSlices
*        The number of slices composing the image
* @param input
*        The input image of size height/nbSlices*width
* @param previous
*        The previous image of size height/nbSlices*width
* @param output
*        The copy of the input image of size height/nbSlices*width
* @param result
*        The difference image (input-previous) of size height/nbSlices*width
*/
void difference(int width, int height, int nbSlices, IN unsigned char *input, IN unsigned char *previous, OUT unsigned char *output, OUT unsigned char *result);

/**
* Function that computes the pixelwise difference of slices input - previous and returns it on result.
*
* @param width
*        The width of the processed image
* @param heigth
*        The heigth of the processed image
* @param nbSlices
*        The number of slices composing the image
* @param input
*        The input image of size height/nbSlices*width
* @param previous
*        The previous image of size height/nbSlices*width
* @param result
*        The difference image (input-previous) of size height/nbSlices*width
*/
void difference2(int width, int height, int nbSlices, IN unsigned char *input, IN unsigned char *previous, OUT unsigned char *result);


#endif
