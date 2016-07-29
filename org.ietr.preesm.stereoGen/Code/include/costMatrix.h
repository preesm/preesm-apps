/*
	============================================================================
	Name        : costMatrix.h
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code to slice a cost matrix.
	============================================================================
*/

#ifndef COST_MATRIX
#define COST_MATRIX

#include "preesm.h"
#include <stdint.h>
#include "image.h"


void costMatrix_dxy_getDisparity(int height,
								 int width,
								 int ndisp,
								 IN uint8_t *d,
								 IN const uint8_t* CostIN,
								 OUT uint8_t* CostOUT);
void costMatrix_dxy_getLine(int height,
							int width,
							int ndisp,
			    			IN const uint8_t* CostIN,
			    			OUT uint8_t* phiB);
			    			
void costMatrix_debug_dxy_u8(int height, int width, int ndisp, IN const uint8_t* costs, int prefix, OUT uint8_t* costsOUT);
void debugs_xy_u8(size_t xs, size_t ys, const uint8_t* costs, uint8_t min, uint8_t max, const char* prefix);

#endif
