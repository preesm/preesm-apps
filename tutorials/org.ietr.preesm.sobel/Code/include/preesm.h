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

//#define PREESM_VERBOSE
//#define PREESM_LOOP_SIZE 50

#include "yuvRead.h"
#include "yuvDisplay.h"

#include "sobel.h"
#include "splitMerge.h"

typedef unsigned char uchar;

#define NB_DISPLAY 1

#define PATH PROJECT_ROOT_PATH "/dat/akiyo_cif.yuv"
#define NB_FRAME 300
#define DISPLAY_W 352*NB_DISPLAY
#define DISPLAY_H 288

/*
#define PATH PROJECT_ROOT_PATH "/dat/sunflower_1080p25.yuv"
#define NB_FRAME 500
#define DISPLAY_W 1920*NB_DISPLAY
#define DISPLAY_H 1080
*/

#define INIT_OVERLAY {NULL} // must be se same size as NB_DISPLAY

#define PATH_TTF PROJECT_ROOT_PATH "/dat/DejaVuSans.ttf"

#endif
