/*
 ============================================================================
 Name        : subsample.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : image sampling
 ============================================================================
 */

#ifndef SUBSAMPLE_H
#define SUBSAMPLE_H

#include "preesm.h"

/**
 * Function to subsample an input image of size width*height to
 * an output image of size (width/2)*(height/2). The first one of
 * the two neighboring lines is considered and the first one of the
 * two neighboring pixels is taken. The developer needs to make sure
 * that the width and the height of the input image are even numbers.
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The height of the processed image
 * @param input
 *        The input image
 * @param output
 *        The output image
 */
void subsample(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// SUBSAMPLE_H
