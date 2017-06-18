#ifndef BP1D_PREESM_H
#define BP1D_PREESM_H

#include "BP1D.h"
#include "costMatrix.h"
#include <stdio.h>
#include <math.h>

#define VERBOSE

/**
* Proceed a slice of cost map using functions of BP1D.h
*
* \param[in] slice_cost Pointer on the slice of cost map to proceed
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[in] n_slice number of slice of the modeling
* \param[in] n_disp Number of disparities of the modeling
* \param[in] phi0 BP1D phi0 constant
* \param[in] select algorithm selector 0 for BP1D
* \param[out] slice_disp_map Output slice of disparity map
*/

void bp1d_PREESM_parallel(const uint8_t* slice_cost, int height, int width, int n_slice, int n_disp, int phi0, int select, uint8_t* slice_disp_map);

#endif // BP1D_PREESM_H
