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

//#define PREESM_VERBOSE
//#define PREESM_LOOP_SIZE 5

#define PATH_LEFT "./dat/im0.ppm"
#define PATH_RIGHT "./dat/im1.ppm"
#define PATH_OUT "./out.ppm"
#define PATH_TTF "./dat/DejaVuSans.ttf"

#define PATH_TTF_FULL PROJECT_ROOT_PATH "/" PATH_TTF
#define PATH_LEFT_FULL PROJECT_ROOT_PATH "/" PATH_LEFT
#define PATH_RIGHT_FULL PROJECT_ROOT_PATH "/" PATH_RIGHT
#define PATH_OUT_FULL PROJECT_ROOT_PATH "/" PATH_OUT

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
