//
// Created by farresti on 21/08/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <md5.h>
#include "squeezenet.h"
#include "labels.h"
#include "common.h"


static void conv1(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 224, .height = 224, .depth = 3, .data = input};
    layer_t conv1Layer = {.width = 112, .height = 112, .depth = 64, .data = output};
    filter_t kernels = {.size = 3, .weights = weights, .bias = biases};

    // Convolution layer
    convolution2D_sequential(&inputLayer, &conv1Layer, &kernels, 2, PADDING_SAME, ACTIVATION_RELU);
}

static void maxpool1(float *const input, float *const output) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 112, .height = 112, .depth = 64, .data = input};
    layer_t maxpool1Layer = {.width = 55, .height = 55, .depth = 64, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&inputLayer, &maxpool1Layer, 3, 3, 2);
}

static void fire2(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 55, .height = 55, .depth = 64, .data = input};
    layer_t concatenateLayer = {.width = 55, .height = 55, .depth = 128, .data = output};
    const int sizes[3] = {16, 64, 64};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void fire3(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 55, .height = 55, .depth = 128, .data = input};
    layer_t concatenateLayer = {.width = 55, .height = 55, .depth = 128, .data = output};
    const int sizes[3] = {16, 64, 64};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void maxpool3(float *const input, float *const output) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 55, .height = 55, .depth = 128, .data = input};
    layer_t maxpool3Layer = {.width = 27, .height = 27, .depth = 128, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&inputLayer, &maxpool3Layer, 3, 3, 2);

}

static void fire4(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 27, .height = 27, .depth = 128, .data = input};
    layer_t concatenateLayer = {.width = 27, .height = 27, .depth = 256, .data = output};
    const int sizes[3] = {32, 128, 128};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void fire5(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 27, .height = 27, .depth = 256, .data = input};
    layer_t concatenateLayer = {.width = 27, .height = 27, .depth = 256, .data = output};
    const int sizes[3] = {32, 128, 128};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void maxpool5(float *const input, float *const output) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 27, .height = 27, .depth = 256, .data = input};
    layer_t maxpool5Layer = {.width = 13, .height = 13, .depth = 256, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&inputLayer, &maxpool5Layer, 3, 3, 2);

}

static void fire6(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 256, .data = input};
    layer_t concatenateLayer = {.width = 13, .height = 13, .depth = 384, .data = output};
    const int sizes[3] = {48, 192, 192};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void fire7(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 384, .data = input};
    layer_t concatenateLayer = {.width = 13, .height = 13, .depth = 384, .data = output};
    const int sizes[3] = {48, 192, 192};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void fire8(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 384, .data = input};
    layer_t concatenateLayer = {.width = 13, .height = 13, .depth = 512, .data = output};
    const int sizes[3] = {64, 256, 256};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void fire9(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 512, .data = input};
    layer_t concatenateLayer = {.width = 13, .height = 13, .depth = 512, .data = output};
    const int sizes[3] = {64, 256, 256};

    // Squeeze - Expand layer
    fire(&inputLayer, &concatenateLayer, weights, biases, sizes);
}

static void conv10(float *const input, float *const output, const float *weights, const float *biases) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 512, .data = input};
    layer_t conv10Layer = {.width = 13, .height = 13, .depth = 1000, .data = output};
    filter_t kernels = {.size = 1, .weights = weights, .bias = biases};

    // Convolution layer
    convolution2D_sequential(&inputLayer, &conv10Layer, &kernels, 1, PADDING_SAME, ACTIVATION_LINEAR);
}

static void avgpool10(float *const input, float *const output) {
    // Setting up the layer parameters
    layer_t inputLayer = {.width = 13, .height = 13, .depth = 1000, .data = input};
    layer_t avgpool10Layer = {.width = 1, .height = 1, .depth = 1000, .data = output};

    // Average Layer
    averagePooling2D_sequential(&inputLayer, &avgpool10Layer, 13, 13);
}

static void softmax(float *input, double *output) {
    softmaxActivation_sequential(input, output, 1000);
}

void
fire(layer_t *inputLayer, layer_t *outputLayer, const float *kernelsWeights, const float *biases, const int sizes[3]) {
    // 0. First, building the layers
    layer_t expand1x1Layer = {.width = inputLayer->width,
            .height = inputLayer->height,
            .depth = sizes[1],
            .data = outputLayer->data};
    long long expand1x1LayerOffset = expand1x1Layer.width * expand1x1Layer.height * expand1x1Layer.depth;
    layer_t expand3x3Layer = {.width = inputLayer->width,
            .height = inputLayer->height,
            .depth = sizes[2],
            .data = outputLayer->data + expand1x1LayerOffset};
    long long expand3x3LayerOffset = expand1x1LayerOffset * 2;
    layer_t squeezeLayer = {.width = inputLayer->width,
            .height = inputLayer->height,
            .depth = sizes[0],
            .data = outputLayer->data + expand3x3LayerOffset};

    // 1. Squeeze layer
    filter_t squeezeKernels = {.size = 1, .weights =  kernelsWeights, .bias = biases};
    convolution2D_sequential(inputLayer, &squeezeLayer, &squeezeKernels, 1, PADDING_SAME, ACTIVATION_RELU);

    // 2. Expand 1x1 layer
    filter_t expand1x1Kernels = {.size = 1, .weights =  kernelsWeights + squeezeLayer.depth *
                                                                         inputLayer->depth, .bias =
    biases + squeezeLayer.depth};
    convolution2D_sequential(&squeezeLayer, &expand1x1Layer, &expand1x1Kernels, 1, PADDING_SAME, ACTIVATION_RELU);

    // 3. Expand 3x3 layer
    filter_t expand3x3Kernels = {.size = 3, .weights =  kernelsWeights +
                                                        squeezeLayer.depth * inputLayer->depth +
                                                        expand1x1Layer.depth *
                                                        squeezeLayer.depth, .bias = biases +
                                                                                    squeezeLayer.depth +
                                                                                    expand1x1Layer.depth};
    convolution2D_sequential(&squeezeLayer, &expand3x3Layer, &expand3x3Kernels, 1, PADDING_SAME, ACTIVATION_RELU);
}

int squeezenetPredict(const image_t *image, const param_t *parameters, double *result) {
    // 0. First create the full size arrays for all layers
    float *inputBuffer = malloc(MAX_BUFFER_SIZE * sizeof(float));
    if (!inputBuffer) {
        fprintf(stderr, "ERROR: Unable to allocate memory input buffer.\n");
        return -1;
    }

    float *outputBuffer = malloc(MAX_BUFFER_SIZE * sizeof(float));
    if (!outputBuffer) {
        fprintf(stderr, "ERROR: Unable to allocate memory input buffer.\n");
        free(inputBuffer);
        return -1;
    }

    const float *localWeights = parameters->weights;
    const float *localBiases = parameters->biases;

    int width = image->width;
    int height = image->height;
    int depth = image->depth;

    // 1. Conv2D
    memcpy(inputBuffer, image->rawPixels, width * height * depth * sizeof(float));
    conv1(inputBuffer, outputBuffer, localWeights, localBiases);

    // 2. MaxPooling2D
    maxpool1(outputBuffer, inputBuffer);

    // 3. Fire2
    localWeights = localWeights + 1728;
    localBiases = localBiases + 64;
    fire2(inputBuffer, outputBuffer, localWeights, localBiases);

    // 4. Fire3
    localWeights = localWeights + 1024 + 1024 + 9216;
    localBiases = localBiases + 16 + 64 + 64;
    fire3(outputBuffer, inputBuffer, localWeights, localBiases);

    // 5. MaxPooling2D
    maxpool3(inputBuffer, outputBuffer);

    // 6. Fire4
    localWeights = localWeights + 2048 + 1024 + 9216;
    localBiases = localBiases + 16 + 64 + 64;
    fire4(outputBuffer, inputBuffer, localWeights, localBiases);

    // 7. Fire5
    localWeights = localWeights + 4096 + 4096 + 36864;
    localBiases = localBiases + 32 + 128 + 128;
    fire5(inputBuffer, outputBuffer, localWeights, localBiases);

    // 8. MaxPooling2D
    maxpool5(outputBuffer, inputBuffer);

    // 9. Fire6
    localWeights = localWeights + 8192 + 4096 + 36864;
    localBiases = localBiases + 32 + 128 + 128;
    fire6(inputBuffer, outputBuffer, localWeights, localBiases);

    // 10. Fire7
    localWeights = localWeights + 12288 + 9216 + 82944;
    localBiases = localBiases + 48 + 192 + 192;
    fire7(outputBuffer, inputBuffer, localWeights, localBiases);

    // 11. Fire8
    localWeights = localWeights + 18432 + 9216 + 82944;
    localBiases = localBiases + 48 + 192 + 192;
    fire8(inputBuffer, outputBuffer, localWeights, localBiases);

    // 12. Fire9
    localWeights = localWeights + 24576 + 16384 + 147456;
    localBiases = localBiases + 64 + 256 + 256;
    fire9(outputBuffer, inputBuffer, localWeights, localBiases);

    // 13. Conv2D
    localWeights = localWeights + 32768 + 16384 + 147456;
    localBiases = localBiases + 64 + 256 + 256;
    conv10(inputBuffer, outputBuffer, localWeights, localBiases);

    // 14. GlobalAveragePooling2D
    avgpool10(outputBuffer, inputBuffer);

    // 15. SoftMax
    softmax(inputBuffer, result);

    // Cleaning memory
    free(inputBuffer);
    free(outputBuffer);
    return 0;
}

int squeezenetDecode(int size, const double *predictions) {
    // Find the maximum values
    double topProbs[3] = {0};
    int topIndexes[3] = {0};
    for (int i = 0; i < size; ++i) {
        if (topProbs[0] < predictions[i]) {
            topIndexes[0] = i;
            topProbs[0] = predictions[i];
        }
    }
    for (int i = 0; i < size; ++i) {
        if (topProbs[1] < predictions[i] && predictions[i] < topProbs[0]) {
            topIndexes[1] = i;
            topProbs[1] = predictions[i];
        }
    }
    for (int i = 0; i < size; ++i) {
        if (topProbs[2] < predictions[i] && predictions[i] < topProbs[1]) {
            topIndexes[2] = i;
            topProbs[2] = predictions[i];
        }
    }
    fprintf(stderr, "Top 3 predictions: \n");
    fprintf(stderr, "    1. %s with probability: %.10e\n", getLabelFromIndex(topIndexes[0]),
            predictions[topIndexes[0]]);
    fprintf(stderr, "    2. %s with probability: %.10e\n", getLabelFromIndex(topIndexes[1]),
            predictions[topIndexes[1]]);
    fprintf(stderr, "    3. %s with probability: %.10e\n", getLabelFromIndex(topIndexes[2]),
            predictions[topIndexes[2]]);
    return topIndexes[0];
}










