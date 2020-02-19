/*
	============================================================================
	Name        : sobel.h
	Author      : kdesnos
	Version     : 1.2
	Copyright   : CeCILL-C
	Description : 2D Sobel filtering function (tailored for the PoC)
	============================================================================
*/

#ifndef SOBEL_H
#define SOBEL_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

/**
* Function to apply the sobel filter to an image of size width*height.
* The 1 pixel-wide border of the image will not be computed.
*
* @param width
*        The width of the processed image
* @param width
*        The heigth of the processed image
* @param input
*        The input image of size height*width
* @param output
*        The output image of size (height-2)*width
*/
void sobel(int width, int height, int background, IN unsigned char *input, OUT unsigned char *output);

#endif
