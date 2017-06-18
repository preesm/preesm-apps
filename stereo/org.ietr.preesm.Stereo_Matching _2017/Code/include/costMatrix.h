/*
 * costMatrix.h
 *
 *  Created on: 5 avr. 2016
 *      Author: jmenant
 */

#ifndef COSTMATRIX_H_
#define COSTMATRIX_H_

#include "../include/image.h"

struct dispMatrix_size
{
	imsize xsize;
	imsize ysize;
	imsize dsize;
};

void costMatrix_dxy_addDisparity(const struct dispMatrix_size* size, imsize d, uint8_t* matrix, const uint8_t* curd);
void costMatrix_dxy_getDisparity(const struct dispMatrix_size* size, imsize d, const uint8_t* matrix, uint8_t* curd);
void costMatrix_dxy_getLine(const struct dispMatrix_size* size, imsize y, const uint8_t* matrix, uint8_t* curd);

void costMatrix_debug_dxy_u8(const struct dispMatrix_size* size, const uint8_t* costs, const char* prefix);
void debugs_xy_u8(size_t xs, size_t ys, const uint8_t* costs, uint8_t min, uint8_t max, const char* prefix);

void costMatrix_debug_dxy_u16(const struct dispMatrix_size* size, const uint16_t* costs, const char* prefix);
#endif /* COSTMATRIX_H_ */
