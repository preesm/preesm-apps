/*
	============================================================================
	Name        : sad_cost_parallel.h
	Author      : Florian Lemarchand
	Version     : 1.0
	Date        : 23/04/17
	Description : Functions designed to use code from sad.h with different parameters.
                  Actually used for PREESM parallel implementation of SAD cost
                  construction algorithm.
	============================================================================
*/

#ifndef SAD_COST_PARALLEL
#define SAD_COST_PARALLEL

//#define VERBOSE

#include <stdint.h>
#include <stdio.h>
#include "sad.h"

/**
* Computes a cost map for each disparity level using SAD cost construction functions of sad.h.
*
* \param[in] slice_l Pointer on a slice of the left input image in gray level
* \param[in] slice_r Pointer on a slice of the right input image in gray level
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[in] n_disp Number of disparity level to be used
* \param[in] thres  Saturation value, 20 is a good value (depend on snr of image)
* \param[in] select Selector of Disparity Selection 1 for SAD
* \param[out] out  Pointer on uint_8t buffer to store the slices of cost maps (must be of size height*width*n_disp)
*/
void sad_cost_parallel(const struct str_image_gray * slice_l, const struct str_image_gray * slice_r, int width, int height, int n_disp, int thres, int select, uint8_t * out);



#endif // SAD_COST_PARALLEL


