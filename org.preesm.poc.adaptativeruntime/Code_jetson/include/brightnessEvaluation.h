/*
	============================================================================
	Name        : brightnessEvaluation.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CeCILL-C
	Description : Evaluate the average brightness of an array of char. Also
	              contain the code of the actor making decisions based on this
	              brightness.
	============================================================================
*/

#ifndef BRIGHTNESS_EVALUATION_H
#define BRIGHTNESS_EVALUATION_H

#include <spider.h>

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

typedef long Param;

void computeBrightnessAndForward(int height, int width, int background, IN unsigned char *in, OUT float *brightness, OUT unsigned char *out);

void makeDecision(IN float *brightness, Param *decision);

#endif
