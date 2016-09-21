/*
	============================================================================
	Name        : sad.h
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the SAD cost.
	============================================================================
*/

#ifndef _SAD_H_
#define _SAD_H_

#include <stdint.h>
#include "preesm.h"

void sad_cost_d(int height, int width, const uint8_t* iml, const uint8_t* imr, IN uint8_t * disp, uint8_t thres, OUT uint8_t * out);

#endif /* _SAD_H_ */
