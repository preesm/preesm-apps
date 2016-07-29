/*
	============================================================================
	Name        : rgb2Gray.h
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Apply scale factor on output image.
	============================================================================
*/

#ifndef SCALE_H
#define SCALE_H

#include <stdint.h>
#include "preesm.h"

/**
* This function convert the input RGB image into its gray equivalent.
*
* @param size
*        Total number of pixel of the input image
* @param rgb
*        3 components of the input image
* @param gray
*        Output buffer for the gray image.
*/
void applyScale(int size, int scale, IN unsigned char *in, OUT uint8_t *out);
#endif
