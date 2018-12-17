//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_SQUEEZENET_H
#define SQUEEZENET_C_SQUEEZENET_H

#include "preesm.h"
#include "convolution-sequential.h"

#define MAX_BUFFER_SIZE (112*112*64)


#define N_LABELS 1000

/**
 *
 * @param input_layer
 * @param output_layer
 * @param kernels_weights
 * @param biases
 * @param sizes
 */
void fire(layer_t *input_layer, layer_t *output_layer, float *kernels_weights, float *biases, const int sizes[3]);

/**
 * @brief Perform a single prediction of the squeezenet network
 *
 * @param input_image Float values of the input image pixels
 * @param width       Width of the input image (224)
 * @param height      Height of the input image (224)
 * @param depth       Depth of the input image (3)
 * @param weights     Array of the raw pre-trained weights
 * @param biases      Array of the raw pre-trained bias
 * @return 0 on SUCCESS, -1 on ERROR
 */
int squeezenetPredict(float *input_image, int width, int height, int depth, float *weights, float *biases, double *result);

/**
 * @brief Return best prediction label index
 *
 * @param predictions Output result of the softmax layer
 * @return index of the best prediction result in the label array;
 */
int squeezenetDecode(IN int size, IN double *predictions);

#endif //SQUEEZENET_C_SQUEEZENET_H
