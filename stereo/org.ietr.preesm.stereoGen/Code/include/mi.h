/*
	============================================================================
	Name        : mi.h
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the MI based cost.
	============================================================================
*/
#ifndef MUTUAL_INFORMATION_H_INCLUDED
#define MUTUAL_INFORMATION_H_INCLUDED
#include "image_png.h"
#include "preesm.h"

#define MUTUAL_INFO_SIZE 256
#define MI_MATRIX_SIZE 65536

/**
*\brief compute the mutual information matrix of two images
*\param mi : Mutual information matrix destination (size = 256*256)
*\param imgr : gray level image (right)
*\param imgl : gray level image (left)
*The two images must have the same size, no verification done in this function
*/
void stereo_mutual_info(int height, int width, int ndisp, OUT uint8_t* mi, IN const uint8_t * rgray, IN const uint8_t * lgray, IN const uint8_t * disparitymap);

void mutual_information_proba(int height, int width, int ndisp, uint16_t* P, uint16_t* PL, uint16_t* PR, const uint8_t * rgray, const uint8_t * lgray, const uint8_t * disparitymap);

void mi_cost_d(int height, int width, int ndisp, IN const uint8_t * rgray, IN const uint8_t * lgray, IN uint8_t * d, IN uint8_t *mi, OUT uint8_t *CostOUT);

#endif // MUTUAL_INFORMATION_H_INCLUDED
