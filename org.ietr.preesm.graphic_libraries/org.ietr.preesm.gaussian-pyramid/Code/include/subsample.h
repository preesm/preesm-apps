/*
 ============================================================================
 Name        : subsample.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : image sub-sampling
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
 *        The width of the input image
 * @param height
 *        The height of the input image
 * @param input
 *        The pointer to the input y sequence
 * @param output
 *        The pointer to the output y sequence
 */
void subsample(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// SUBSAMPLE_H
