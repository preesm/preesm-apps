/*
	============================================================================
	Name        : sobel.h
	Author      : kdesnos
	Version     : 1.1
	Copyright   : CeCILL-C
	Description : 2D Sobel filtering function
	============================================================================
*/

#ifndef SOBEL_H
#define SOBEL_H

#include "preesm.h"

#define HEIGHT (146)
#define WIDTH  (352)

#define NUMROWS HEIGHT
#define NUMCOLS WIDTH
#define BYTESHIFT 8
#define YUV_BLACK_VAL 0x0080
#define YUV_WHITE_VAL 0xff80

/**
* Function to apply the sobel filter to an image of size width*height.
* The 1 pixel-wide border of the image will not be computed.
*
* @param width
*        The width of the processed image
* @param heigth
*        The heigth of the processed image
* @param input
*        The input image
* @param output
*        The output image
* 
* Note: for the HLS version of the filter the width is useless because it is fixed.
* If you want to chenge the video input, please change the parameters on top of this header file.
* 
*/



#ifdef __cplusplus
extern "C"{
#endif

void sobel(int width, int height, IN unsigned char *input, OUT unsigned char *output);
void sobel_filter0( IN unsigned char *yc_in,OUT unsigned char *yc_out, int height);
void sobel_filter1( IN unsigned char *yc_in,OUT unsigned char *yc_out, int height);
void sobel_filter2( IN unsigned char *yc_in,OUT unsigned char *yc_out, int height);
void sobel_filter3( IN unsigned char *yc_in,OUT unsigned char *yc_out, int height);

#ifdef __cplusplus
}
#endif

#endif /* SOBEL_H */
