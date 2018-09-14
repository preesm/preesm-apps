/*
	============================================================================
	Name        : scale.h
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

void applyScale(int size, int scale, IN unsigned char *in, OUT uint8_t *out);
#endif
