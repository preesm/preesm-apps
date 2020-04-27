#ifndef ROTATE_H
#define ROTATE_H

#include "preesm.h"

void rotateClockWise(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

void rotateCounterClockWise(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// ROTATE_H
