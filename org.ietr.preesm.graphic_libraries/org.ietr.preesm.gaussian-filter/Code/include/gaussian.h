/*
 ============================================================================
 Name        : gaussian.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D Gaussian filtering function
 ============================================================================
 */

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "preesm.h"

/**
 * Function to apply the gaussian filter to an image of size width*height.
 * The 1 pixel-wide border of the image will not be computed.
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The heigth of the processed image
 * @param input
 *        The input image
 * @param output
 *        The output image
 */
void gaussian(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// GAUSSIAN_H
