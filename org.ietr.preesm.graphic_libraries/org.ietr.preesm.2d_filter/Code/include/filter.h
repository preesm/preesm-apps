#ifndef FILTER_H
#define FILTER_H

#include "preesm.h"

/**
 * Function to apply a filter to an image of size width*height.
 * The 1 pixel-wide border of the image will not be computed.
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The heigth of the processed image
 * @param filterSize
 * 		  The size of the filter
 * @param input
 *        The input image
 * @param output
 *        The output image
 */
void filter(int width, int height, int filterSize, int borderSize,
		IN char *coefficients, IN unsigned char *norm, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// FILTER_H
