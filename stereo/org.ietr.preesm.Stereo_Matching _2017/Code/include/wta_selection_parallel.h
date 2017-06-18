/*
	============================================================================
	Name        : wta_selection_parallel.h
	Author      : Florian Lemarchand
	Date        : 23/04/17
	Description : Functions designed to use code wta.h with different parameters.
                  Actually used for PREESM parallel implementation of WTA selection
                  algorithm.
	============================================================================
*/

#ifndef WTA_SELECTION_PARALLEL
#define WTA_SELECTION_PARALLEL

//#define VERBOSE

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "wta.h"

/**
* Select one disparity for each pixel out of the cost maps using WTA selection model.
*
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[in] n_disp Number of disparity level to be used
* \param[in] n_slice Number of slice done on the original image
* \param[in] select Selector of Disparity Selection 1 for WTA
* \param[in] cost_slice_refined Pointer on a buffer containing the refined cost maps (must be of size height*width*n_disp/n_slice)
* \param[in] slice_disp Pointer on a buffer containing a slice of the disparity map (must be of size height*width/n_slice)

*/
void wta_selection_parallel(int width, int height, int n_disp, int n_slice, int select, const uint8_t* slice_cost, uint8_t* slice_disp);

#endif // WTA_SELECTION_PARALLEL




