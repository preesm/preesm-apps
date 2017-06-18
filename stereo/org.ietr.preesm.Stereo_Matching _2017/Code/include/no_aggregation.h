/*
	============================================================================
	Name        : wta_selection_parallel.h
	Author      : Florian Lemarchand
	Date        : 15/06/17
	Description : This function just copies the input to the output! It just allows us to represent
	a non aggregation actor in the streo matching dataflow graph .
	============================================================================
*/

#ifndef NO_AGGREGATION_H
#define NO_AGGREGATION_H

//#define VERBOSE

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "costMatrix.h"


/**
* Transmits input to output after removing extra data added when slicing before cost construction
* if select = 0, does nothing otherwise.
*
*
* \param[in] select  algorithm selector (0 for no aggregation)
* \param[in] n_slice number of slice into the input buffer
* \param[in] height height of the original images
* \param[in] width width of the original images
* \param[in] n_disp number of disparities
* \param[in] nb_lines_sup number of extra lines added on top and bottom of each slice
* \param[in] in pointer on the input buffer
* \param[out] out pointer on the output buffer
*/
void no_aggregation(int select, int n_slice, int height, int width, int n_disp, int nb_lines_sup, uint8_t * in, uint8_t * out);




#endif //NO_AGGREGATION_H
