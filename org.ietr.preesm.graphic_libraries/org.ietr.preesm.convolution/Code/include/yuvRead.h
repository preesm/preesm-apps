/*
 ============================================================================
 Name        : readYUV.h
 Author      : kdesnos & mpelcat
 Version     : 1.1
 Copyright   : CECILL-C
 Description : Actor code to read a file from the hard drive
 ============================================================================
 */

#ifndef READ_YUV_H
#define READ_YUV_H

#include "preesm.h"

#define PATH PROJECT_ROOT_PATH "/dat/GivingScholarlyFallowdeer1280x720-415f.yuv"

#define NB_FRAME 415

/**
 * Initialize the readYUV actor.
 * Open the YUV file at the given PATH and check its size.
 *
 * @param width
 *        The width of the opened YUV file
 * @param height
 *        The heigth of the opened YUV file
 */
void initReadYUV(int width, int height);

/**
 * Read a new frame from the YUV file and take only the Y component.
 * U and V are given the value 128 since in the YUV representation, black
 * is (0, 128, 128) and white is (255, 128, 128).
 *
 * @param width
 *        The width of the opened YUV file
 * @param height
 *        The heigth of the opened YUV file
 * param y
 *       Destination of the Y component read from the file
 * param u
 *       Destination of the U component read from the file
 * param v
 *       Destination of the V component read from the file
 */
void readY(int width, int height, OUT unsigned char *y, OUT unsigned char *u,
		OUT unsigned char *v);

#endif