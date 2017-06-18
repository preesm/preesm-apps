/*
 * sad.h
 *
 *  Created on: 25 avr. 2016
 *      Author: jmenant
 */

#ifndef _SAD_H_
#define _SAD_H_

#include "costMatrix.h"

void sad_cost_d(const uint8_t* iml, const uint8_t* imr, int disp, uint8_t thres, struct str_image_gray* out);
void sad_cost_dxy(const struct dispMatrix_size* size, const struct str_image_gray* iml, const struct str_image_gray* imr, uint8_t thres, uint8_t* out);

#endif /* _SAD_H_ */
