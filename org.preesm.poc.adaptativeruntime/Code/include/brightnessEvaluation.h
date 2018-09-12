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

#include "preesm.h"
#include <spider.h>

typedef long Param;

/*
 * TODO
 */
void evalBrightness(int height, int width, IN unsigned char * in, OUT float * brightness, OUT unsigned char * out);

void makeDecision(IN float* brightness, Param * decision);

void generateNothing(int height, int width, int value, OUT unsigned char * out);

#endif
