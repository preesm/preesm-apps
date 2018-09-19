/*
	============================================================================
	Name        : preesm.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Usefull declarations for all headers used in preesm.
	============================================================================
*/

#ifndef PREESM_H
#define PREESM_H

#define IN
#define OUT

#define NB_FRAME 3000
// FPS: number of frame between two FPS measures
#define FPS 10

typedef unsigned char uchar;

#include "clock.h"

#include "ppm.h"
#include "displayRGB.h"
#include "rgb2Gray.h"
#include "census.h"
#include "costConstruction.h"
#include "disparityGen.h"
#include "offsetGen.h"
#include "aggregateCost.h"
#include "computeWeights.h"
#include "disparitySelect.h"
#include "medianFilter.h"
#include "splitMerge.h"
#include "yuv2RGB.h"
#include "yuvRead.h"

#include "sink.h"


#endif
