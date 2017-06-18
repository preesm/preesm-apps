/*
 * stereomatch.h
 *
 *  Created on: 18 févr. 2014
 *      Author: jmenant
 */

#ifndef STEREOMATCH_H_
#define STEREOMATCH_H_

#include <stdint.h>

#include "costMatrix.h"
#include "image.h"

void compute_vweigth(
	int heigth, int width,
	int delta,
	const uint8_t* imr,
	const uint8_t* img,
	const uint8_t* imb,
	uint8_t* out,
	int thr_weight,
	int cst_cd);

void compute_hweigth(
	int heigth, int width,
	int delta,
	const uint8_t* imr,
	const uint8_t* img,
	const uint8_t* imb,
	uint8_t* out,
	int thr_weight,
	int cst_cd);

void aggregateV(
	int height, int width,
	int delta,
	uint8_t* cost_in,
	uint8_t* weight,
	uint8_t* cost_out);

void aggregateH(
	int height, int width,
	int delta,
	uint8_t* cost_in,
	uint8_t* weight,
	uint8_t* cost_out);

void bfa_aggregation(
    const struct dispMatrix_size* size,
    const uint8_t* costIn,
    uint8_t* costOut,
    const struct str_image_rgb* iml, const struct str_image_rgb* imr,
    int thr_weight, int cst_cd, int niter, int dmax);

#endif /* STEREOMATCH_H_ */
