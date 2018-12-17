//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_CONVOLUTION_H
#define SQUEEZENET_C_CONVOLUTION_H

#include "preesm.h"

#define PADDING_VALID 0
#define PADDING_SAME  1

#define ACTIVATION_RELU 0
#define ACTIVATION_LINEAR 1





/**
 * @brief Perform a max pool operation
 *
 * Note: Padding is PADDING_VALID by default.<
 *
 * @param input_layer     Input layer of size N*M*D
 * @param output_layer    Output layer of size N2*M2*D2
 * @param max_pool_width  Width of the max pool operator
 * @param max_pool_height Height of the max pool operator
 * @param stride          Stride
 *
 * @return 0 on SUCCESS, -1 on ERROR
 */
int maxPooling2D(IN int widthInput, IN int heightInput, IN int depth, 
                 IN int widthOutput, IN int heightOutput, 
                 IN int poolWidth, IN int poolHeight, IN int stride, 
                 IN float *input, OUT float *out);

/**
 * @brief Perform an average pooling operation
 *
 * @param input_layer  Input layer of size N*M*D
 * @param output_layer Output layer of size N2*M2*D2
 * @param avg_width    Width of the average operator
 * @param avg_height   Height of the average operator
 * @return
 */
int averagePooling2D(IN int widthInput, IN int heightInput, 
                     IN int widthOutput, IN int heightOutput, 
                     IN int averageWidth, IN int averageHeight, 
                     IN float *input, OUT float *out);

int softmaxActivation(IN int size, IN float *input, OUT double *output);

void convolution2DPaddingSame(IN int widthInput, IN int heightInput, IN int depthInput, 
                              IN int widthOutput, IN int heightOutput,
                              IN int sizeKernel, IN int stride, 
                              IN float *input, IN float *weights, IN float *bias, 
                              OUT float *out);


#endif //SQUEEZENET_C_CONVOLUTION_H
