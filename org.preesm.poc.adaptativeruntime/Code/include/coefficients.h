/*
 ============================================================================
 Name        : coefficients.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : filter coefficients
 ============================================================================
 */

#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include "preesm.h"

/**
 * Function to feed the coefficients to the filter actor. The
 * coefficients are read in order (left to right, up to down).
 * The developer need to ensure that the values are given in
 * the correct memory range. A normalizing constant can be used
 * to further refine the coefficients. It should be given the
 * value 1 if not used.
 *
 * @param coefficients
 *        The coefficients of the filter
 * @param norm
 *        The normalizing constant
 */
void setCoefficients(OUT char *coefficients, OUT int *norm);

#endif	// COEFFICIENTS_H
