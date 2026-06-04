#ifndef WT_FUNCTION
#define WT_FUNCTION

#include <string.h>
#include <math.h>
#include "preesm.h"

/**
* Function to perform a cyclic convolution along the X axis
*
* @param WIDTH
*        The width of the processed image
* @param HEIGHT
*        The height of the processed image
* @param FILTER_SIZE
*        The size of the filter to be applied
* @param input
*        The input image of size WIDTH*HEIGHT
* @param filter
*        The filter to be applied of size FILTER_SIZE
* @param output
*        The output image of size WIDTH*HEIGHT
*/
void convolution_1D_row(int WIDTH, int HEIGHT, int FILTER_SIZE, IN float* input, IN float* filter, OUT float* output);

void convolution_1D_row_decimation_col(int WIDTH, int HEIGHT, int FILTER_SIZE, IN float* input, IN float* filter, OUT float* output);

/**
* Function to perform a cyclic convolution along the Y axis
*
* @param WIDTH
*        The width of the processed image
* @param HEIGHT
*        The height of the processed image
* @param FILTER_SIZE
*        The size of the filter to be applied
* @param input
*        The input image of size WIDTH*HEIGHT
* @param filter
*        The filter to be applied of size FILTER_SIZE
* @param output
*        The output image of size WIDTH*HEIGHT
*/
void convolution_1D_col(int WIDTH, int HEIGHT, int FILTER_SIZE, IN float* input, IN float* filter, OUT float* output);

/**
* Function to downsample the image by removing rows
*
* @param WIDTH
*        The width of the output image
* @param HEIGHT
*        The height of the output image
* @param input
*        The input image of size WIDTH*HEIGHT/2
* @param output
*        The output image of size WIDTH*HEIGHT
*/
void downsample_row(int WIDTH, int HEIGHT, IN float* input, OUT float* output);

/**
* Function to downsample the image by removing columns
*
* @param WIDTH
*        The width of the output image
* @param HEIGHT
*        The height of the output image
* @param input
*        The input image of size WIDTH*HEIGHT
* @param output
*        The output image of size WIDTH/2*HEIGHT
*/
void downsample_col(int WIDTH, int HEIGHT, IN float* input, OUT float* output);

/**
* Function to upsample the image be adding rows
*
* @param WIDTH
*        The width of the input image
* @param HEIGHT
*        The height of the input image
* @param input
*        The input image of size WIDTH*HEIGHT
* @param output
*        The output image of size WIDTH*HEIGHT*2
*/
void upsample_row(int WIDTH, int HEIGHT, IN float* input, OUT float* output);

/**
* Function to upsample the image be adding columns
*
* @param WIDTH
*        The width of the input image
* @param HEIGHT
*        The height of the input image
* @param input
*        The input image of size WIDTH*HEIGHT
* @param output
*        The output image of size WIDTH*2*HEIGHT
*/
void upsample_col(int WIDTH, int HEIGHT, IN float* input, OUT float* output);

void image_add(int WIDTH, int HEIGHT, IN float* input1, IN float* input2, OUT float* output);

void soft_threshold(int WIDTH, int HEIGHT, IN float* src, OUT float* snk);

void median_histogram_threshold_filter(int WIDTH, int HEIGHT, float* input, float* output);

#endif
