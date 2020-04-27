#ifndef LANEFILTER_H
#define LANEFILTER_H

#include "preesm.h"

#define THD 128

void laneFilter(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// LANEFILTER_H
