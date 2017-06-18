/*
 * wta.h
 *
 *  Created on: 25 avr. 2016
 *      Author: jmenant
 */

#ifndef _WTA_H_
#define _WTA_H_

#include "../include/costMatrix.h"

void wta_selection(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* dispout);

#endif /* _WTA_H_ */
