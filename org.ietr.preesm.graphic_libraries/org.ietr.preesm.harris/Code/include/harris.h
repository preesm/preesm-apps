/*
 ============================================================================
 Name        : harris.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D Harris corner detection function
 ============================================================================
 */

#ifndef HARRIS_H
#define HARRIS_H

#include "stdio.h"
#include "preesm.h"

/**
 * HARRIS_K an empirically determined constant between 0.04 and 0.06.
 */
#define HARRIS_K            0.04

/**
 * A threshold used for non-maximum supression.
 * Value suggested between 0.00001 and 0.00008.
 */
#define HARRIS_THRESHOLD    0.00002

/**
 * Function to apply the Harris corner detection to an image of size
 * width * height. gx and gy are results issue from the sobel functions.
 * HARRIS_K is a constant defined in the algorithm. A threshold is used
 * to eliminate the non-corner points. The value of the threshold should
 * be changed to adapt to different sequences and needs.A white pixel is
 * put in the output image if a corner is detected; otherwise, a black
 * pixel is put in the position.
 *
 * @param width
 *        The width of the processed image
 * @param height
 *        The heigth of the processed image
 * @param y
 *        The y component of the input image
 * @param gx
 *        The result of the x-sobel function on the input image
 * @param gy
 *        The result of the y-sobel function on the input image
 * @param output
 *        The y component of the output image
 */
void harris(int width, int height, IN unsigned char *y, IN char *gx, IN char *gy, OUT unsigned char *output);

#endif    // HARRIS_H
