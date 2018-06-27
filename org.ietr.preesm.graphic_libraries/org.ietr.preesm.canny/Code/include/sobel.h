/*
 ============================================================================
 Name        : sobel.h
 Author      : kdesnos
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D Sobel filtering function
 ============================================================================
 */

#ifndef SOBEL_H
#define SOBEL_H

#include "preesm.h"

/**
 * Function to apply the x-sobel filter to an image of size width*height.
 * The 1 pixel-wide border of the image will not be computed.
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The heigth of the processed image
 * @param input
 *        The input image
 * @param output_x
 *        The x result of the sobel filter
 * @param output_y
 *        The y result of the sobel filter
 */
void sobel2(int width, int height, IN unsigned char *input, OUT char *output_x,
		OUT char *output_y);

#endif
