/*
 ============================================================================
 Name        : upsample.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : image up-sampling
 ============================================================================
 */

#ifndef UPSAMPLE_H
#define UPSAMPLE_H

#include "preesm.h"

/**
 * Funciton to upsample a input image of size width * height
 * to an output image of size (2 * width) * (2 * height).
 *
 * @param width
 * 		  The width of the input image
 * @param height
 * 		  The height of the input image
 * @param input
 * 		  The pointer to the input y sequence
 * @param output
 * 		  The pointer to the output y sequence
 */
void upsample(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif /* UPSAMPLE_H */
