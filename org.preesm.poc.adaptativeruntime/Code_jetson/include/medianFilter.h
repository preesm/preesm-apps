/*
	============================================================================
	Name        : medianFilter.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CeCILL-C, IETR, INSA Rennes
	Description : Application of a 3x3 median filter to an image.
	============================================================================
*/

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif


/**
* This function applies a median filter to the input image. 
* This filter consists of replacing each pixel with the median value of its
* 3x3 neighborhood. For example:
* |18|21|13|  => {13, 13, 16, 15, 18, 18, 19, 20, 21}
* |15|20|19|  => 20 is replaced with 18. 
* |13|18|16|
*
* @param height
*        The height of the filtered image
* @param width
*        The width of the filtered image
* @param topDownBorderSize
*        Number of unfiltered lines at the top and bottom of the image
* @param rawDisparity
*        The height*width input image
* @param filteredDisparity
*        The (height-2)*width output image
*/
void medianFilter(int height, int width,
                  IN unsigned char *rawDisparity,
                  OUT unsigned char *filteredDisparity);

#endif
