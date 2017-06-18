/*
	============================================================================
	Name        : bfa_aggregation_parallel.h
	Author      : Florian Lemarchand
	Date        : 23/04/17
	Description : Functions designed to use code of bfa.h in a slicced environement.
                  Actually used for PREESM parallel implementation of BFA cost
                  aggregation algorithm.
	============================================================================
*/

#ifndef BFA_AGGREGATION_PARALLEL
#define BFA_AGGREGATION_PARALLEL

//#define VERBOSE

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "bfa.h"
#include "costMatrix.h"

/**
* Refines a set of cost maps using BFA aggregation model.
*
* \param[in] im_l Pointer on the left input image in RGB
* \param[in] im_r Pointer on the right input image in RGB
* \param[in] costs Pointer on a buffer containing the cost maps to refine
* \param[out] refined_costs_refined Pointer on a buffer containing the refined cost maps
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[in] n_disp Number of disparity level to be used
* \param[in] n_slice Number of slice done on the original image
* \param[in] threshold_BFA weight threshold for BFA algorithm
* \param[in] cst_cd distance constant for BFA
* \param[in] niter Number of iteration of BFA
* \param[in] dmax distamce max  for BFA
* \param[in] select algorithm slector (1 for BFA)
* \param[in] nb_lines_sup number of lines to remove and add to input and output slices
*/
void bfa_aggregation_parallel(const struct str_image_rgb * im_l, const struct str_image_rgb * im_r, uint8_t * costs, uint8_t * refined_costs, int width, int height, int n_disp, int n_slice, int threshold_BFA, int cst_cd, int niter, int dmax, int nb_lines_sup, int select);

#endif // BFA_AGGREGATION_PARALLEL



