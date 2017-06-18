#ifndef CENSUS_PREESM_H
#define CENSUS_PREESM_H

#include <stdio.h>
#include "census.h"

//#define VERBOSE

/**
* Proceed two slices from image right and left to produce a slice of cost map
*
* \param[in] slice_r slice of the right image
* \param[in] slice_l slice of the left image
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[in] n_disp Number of disparities of the modelling
* \param[in] census_size size of the census window to use
* \param[in] select algorithm selector 0 for census
* \param[out] slice_cost Output cost slice
*/

void census_PREESM(struct str_image_gray * slice_r, struct str_image_gray * slice_l, int width, int height,int n_disp, int census_size, int select, uint8_t * slice_cost);

#endif // CENSUS_PREESM_H

