//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_SQUEEZENET_H
#define SQUEEZENET_C_SQUEEZENET_H

#include "convolution-sequential.h"

#define MAX_BUFFER_SIZE (112*112*64)

typedef struct image_t {
    float *rawPixels;
    int width;
    int height;
    int depth;
} image_t;

typedef struct param_t {
    const float *weights;
    const float *biases;
} param_t;


/**
 *
 * @param inputLayer
 * @param outputLayer
 * @param kernelsWeights
 * @param biases
 * @param sizes
 */
void
fire(layer_t *inputLayer, layer_t *outputLayer, const float *kernelsWeights, const float *biases, const int sizes[3]);

/**
 * @brief Perform a single prediction of the squeezenet network
 *
 * @param inputImage Float values of the input image pixels
 * @param width       Width of the input image (224)
 * @param height      Height of the input image (224)
 * @param depth       Depth of the input image (3)
 * @param weights     Array of the raw pre-trained weights
 * @param biases      Array of the raw pre-trained bias
 * @return 0 on SUCCESS, -1 on ERROR
 */
int squeezenetPredict(const image_t *image, const param_t *parameters, double *result);


/**
 * @brief Return best prediction label index
 *
 * @param predictions Output result of the softmax layer
 *
 * @return index of the best prediction result in the label array;
 */
int squeezenetDecode(int size, const double *predictions);

#endif //SQUEEZENET_C_SQUEEZENET_H
