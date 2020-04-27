#ifndef PIXELSEL_H
#define PIXELSEL_H

#include "preesm.h"

void pixelSel(int width, int height, IN unsigned char *laneY,
		IN unsigned char *imageY, IN unsigned char *imageU,
		IN unsigned char *imageV, OUT unsigned char *y, OUT unsigned char *u,
		OUT unsigned char *v);

#endif	// PIXELSEL_H
