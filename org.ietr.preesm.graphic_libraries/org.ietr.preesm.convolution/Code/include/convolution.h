/*
 ============================================================================
 Name        : convolution.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D convolution function
 ============================================================================
 */

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "preesm.h"

/**
 * Function to apply a convolution kernel to an image of size width*height.
 * The coefficients of the kernel are fed to the actor by from
 * input along with a normalizing constant. A borderSize-width
 * border will not be computed and will be given the value 0 in
 * the output
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The heigth of the processed image
 * @param filterSize
 * 		  The size of the kernel
 * @param borderSize
 * 		  The border which is not computed
 * @param coefficients
 * 		  The coefficients of the kernel
 * @param norm
 * 		  The normalizing constant
 * @param input
 *        The input image
 * @param output
 *        The output image
 */
void convolution(int width, int height, int kernelSize, int borderSize,
		IN char *coefficients, IN unsigned char *norm, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// CONVOLUTION_H
