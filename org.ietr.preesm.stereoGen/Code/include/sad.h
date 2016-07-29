/*
 * sad.h
 *
 *  Created on: 25 avr. 2016
 *      Author: jmenant
 */

#ifndef _SAD_H_
#define _SAD_H_

#include <stdint.h>
#include "preesm.h"

void sad_cost_d(int height, int width, const uint8_t* iml, const uint8_t* imr, IN uint8_t * disp, uint8_t thres, OUT uint8_t * out);

#endif /* _SAD_H_ */
