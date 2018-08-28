#ifndef SAMPLE_H
#define SAMPLE_H

#include "preesm.h"

void subSample(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

void upSample(int width, int height, IN unsigned char *input,
		OUT unsigned char *output);

#endif	// SAMPLE_H
