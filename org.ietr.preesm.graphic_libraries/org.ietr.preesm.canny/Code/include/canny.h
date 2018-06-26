/*
 ============================================================================
 Name        : canny.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D Canny edge detection function
 ============================================================================
 */

#ifndef CANNY_H
#define CANNY_H

#include "preesm.h"

#define HIGH_THRESHOLD	80000
#define LOW_THRESHOLD	12000

/**
 * Constant PI used to determine the value of the four thresholds
 * to classify the direction of derivatives.
 */
#define PI	3.1415926536

/**
 * Function to apply the Canny edge detector to an image of size
 * width * height. The input gx and gy are results of Sobel filter.
 *
 * A pixel is considered to be an edge point if its value is larger
 * than the two neighbor pixels in the perpendicular direction of
 * its derivative.
 * 					b		(neighbor pixel 1)
 * 					|
 * 					a--->	(direction of derivative)
 * 					|
 * 					c		(neighbor pixel 2)
 * (a is considered to be an edge if (|a| > |b| and |a| > |c|))
 *
 * Since the function is applied to digital images, only four
 * directions are possible: 0°, 45°, 90° and 135°. Four thresholds
 * are used to classify the direction of derivatives into one of the
 * angles.
 * arg = atan2(y, x);
 *
 *       	| 0°,	if (-22.5° <= arg < 22.5°)
 *       	|		or (arg >= 157.5°)
 *       	|		or (arg < -157.5°)
 *    arg = | 45°, 	if (22.5° <= arg < 67.5°)
 * 		 	|		or (-157.5° <= arg < -112.5°)
 *       	| 90°, 	if (67.5° <= arg < 112.5°)
 *       	|		or (-112.5° <= arg < -67.5°)
 *       	| 135°, if (112.5° <= arg < 157.5°)
 *       	|		or (-67.5° <= arg < -22.5°)
 *
 * Two thresholds are used to further refine the results.
 *
 * @param width
 * 		  The width of the processed image
 * @param height
 * 		  The height of the processed image
 * @param gx
 * 		  The result of the x-sobel function on the input image
 * @param gy
 * 		  The result of the y-sobel function on the input image
 * @param output
 * 		  The output image
 */
void canny(int width, int height, IN char *gx, IN char *gy,
		OUT unsigned char *output);

#endif	// CANNY_H
