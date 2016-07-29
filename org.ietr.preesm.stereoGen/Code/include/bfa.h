/*
	============================================================================
	Name        : bfa.h
	Author      : jmenant
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for BFA aggregation.
	============================================================================
*/

#ifndef STEREOMATCH_H_
#define STEREOMATCH_H_

#include <stdint.h>

#include "preesm.h"


void compute_vweight(
	int height, int width,
	int thr_weight,
	int cst_cd,
	IN uint8_t * deltas,
	IN const uint8_t* iml,
	OUT uint8_t* out);

void compute_hweight(
	int height, int width,
	int thr_weight,
	int cst_cd,
	IN uint8_t  *deltas,
	IN const uint8_t* iml,
	OUT uint8_t* out);

void aggregateV(
	int height,
	int width,
	IN uint8_t * deltas,
	IN uint8_t* CostIN,
	IN uint8_t* vWeight,
	IN uint8_t* back,	
	OUT uint8_t* CostOUT);

void aggregateH(
	int height,
	int width,
	IN uint8_t * deltas,
	IN uint8_t* CostIN,
	IN uint8_t* hWeight,
	OUT uint8_t* CostOUT);

#endif /* STEREOMATCH_H_ */
