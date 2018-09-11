/*
 ============================================================================
 Name        : filter.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D filtering function
 ============================================================================
 */

#ifndef FILTER_H
#define FILTER_H

#include "preesm.h"

/**
 * Function to apply a dot-product kernel to an image of size width*height.
 * The coefficients of the filter are fed to the actor by from
 * input along with a normalizing constant. A borderSize-width
 * border will not be computed and will be given the value 0 in
 * the output
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The height of the processed image
 * @param filterSize
 * 		  The size of the filter
 * @param borderSize
 * 		  The border which is not computed
 * @param coefficients
 * 		  The coefficients of the filter
 * @param norm
 * 		  The normalizing constant
 * @param input
 *        The input image
 * @param output
 *        The output image
 */
void filter(int width, int height, int filterSize, int borderSize,
		IN char *coefficients, IN int *norm, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// FILTER_H
