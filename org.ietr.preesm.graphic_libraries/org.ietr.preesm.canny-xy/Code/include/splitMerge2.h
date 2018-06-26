/*
 ============================================================================
 Name        : splitMerge.h
 Author      : kdesnos
 Version     : 1.1
 Copyright   : CECILL-C
 Description : Function used to split an image into overlapping slices and
 merge them back together.
 ============================================================================
 */

#ifndef SPLIT_MERGE_H
#define SPLIT_MERGE_H

#include "preesm.h"

/**
 * Function used to split an input image of size width*height into nbSlices
 * slices and nbColumns columns of size (width/nbColumn+2)*(height/nbSlice+2).
 * It is developer's responsibility to ensure that height is a multiple of
 * nbSlice and width is a multiple of nbColumn;
 *
 * @param nbSlice
 * 		  the number of slices produced
 * @param nbColumn
 * 		  the number of columns produced
 * @param width
 * 		  the width of the input image
 * @param height
 * 		  the height of the input image
 * @param input
 * 		  the input image of size width*height
 * @param output
 * 		  the output buffer of size
 */
void split2(int width, int height, int nbColumn, int nbSlice,
		IN unsigned char *input, OUT unsigned char *output);

/**
 * Function used to assemble nbSlices slices of size width*(height/nbSlice+2)
 * into an output image of size width*height.
 *
 * @param nbSlice
 *        the number of slices assembled
 * @param width
 *        the width of the output image
 * @param height
 *        the height of the output image
 * @param input
 *        the input image slices
 * @param output
 *        the output image of size width*height
 */
void merge2(int width, int height, int nbColumn, int nbSlice,
		IN unsigned char *input, OUT unsigned char *output);

#endif
