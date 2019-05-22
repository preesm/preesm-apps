//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_CONVOLUTION_H
#define SQUEEZENET_C_CONVOLUTION_H

#include <preesm.h>
#include <convolution-sequential.h>

/**
 * @brief Perform a max pool operation for a given input layer.
 *
 * Note: Padding is PADDING_VALID by default.<
 *
 * @param widthInput   Width of the input layer.
 * @param heightInput  Height of the input layer.
 * @param widthOutput  Width of the output layer.
 * @param heightOutput Height of the output layer.
 * @param poolWidth    Width of the max pool operator.
 * @param poolHeight   Height of the max pool operator.
 * @param stride       Stride.
 * @param input        Input layer.
 * @param output       Output layer.
 *
 * @return 0 on SUCCESS, -1 on ERROR
 */
int maxPooling2D(IN int widthInput, IN int heightInput,
                 IN int widthOutput, IN int heightOutput,
                 IN int poolWidth, IN int poolHeight, IN int stride,
                 IN float *input, OUT float *out);

/**
 * @brief Perform an average pooling operation for a given input layer.
 *
 * @param widthInput   Width of the input layer.
 * @param heightInput  Height of the input layer.
 * @param widthOutput  Width of the output layer.
 * @param heightOutput Height of the output layer.
 * @param avgWidth     Width of the average operator.
 * @param avgHeight    Height of the average operator.
 * @param input        Input layer.
 * @param output       Output layer.
 *
 * @return 0 on SUCCESS, -1 on ERROR
 */
int averagePooling2D(IN int widthInput, IN int heightInput,
                     IN int widthOutput, IN int heightOutput,
                     IN int avgWidth, IN int avgHeight,
                     IN float *input, OUT float *out);

/**
 * @brief  Convolution layer of a CNN. Perform convolution on all input layers for a given output layer.
 *
 * @param widthInput   Width of the input layer.
 * @param heightInput  Height of the input layer.
 * @param depthInput   Depth of the input layer.
 * @param widthOutput  Width of the output layer.
 * @param heightOutput Height of the output layer.
 * @param sizeKernel   Size of the convolution kernel.
 * @param stride       Stride.
 * @param input        Input layers.
 * @param weights      Weights of the different kernels.
 * @param bias         Bias value.
 * @param output       Output layer.
 *
 * @return 0 on SUCCESS, -1 on ERROR
 */
void convolution2D(IN int widthInput, IN int heightInput, IN int depthInput,
                   IN int widthOutput, IN int heightOutput,
                   IN int sizeKernel, IN int stride,
                   IN float *input, IN float *weights, IN float *bias,
                   OUT float *out);

int softmaxActivation(IN int size, IN float *input, OUT double *output);


#endif //SQUEEZENET_C_CONVOLUTION_H
