//
// Created by farresti on 21/08/18.
//

#include <stdio.h>
#include <math.h>
#include <common.h>
#include <convolution-sequential.h>

static inline float activationReLU(float x) {
    return x > 0 ? x : 0;
}

static inline float activationLinear(float x) {
    return x;
}

float
convolutionFilterGeneric(const float *input, const float *weights, const int *filterParams, int width, int filterSize) {
    int x = filterParams[0];
    int y = filterParams[1];
    int offsetX = filterParams[2];
    int offsetY = filterParams[3];
    int filterSizeX = filterParams[4];
    int filterSizeY = filterParams[5];

    float result = 0.f;
    for (int j = 0; j < filterSizeY; ++j) {
        int pixelY = (y + j) * width;
        int weightY = (j + offsetY) * filterSize;
        for (int i = 0; i < filterSizeX; ++i) {
            float rawPixel = input[(x + i) + pixelY];
            float weight = weights[(i + offsetX) + weightY];
            result += rawPixel * weight;
        }
    }
    return result;
}

void
getConvolutionParameters(int i, int j, int filterSize, int width, int height, int padding, int filterParams[6]) {
    /* x value */
    filterParams[0] = max(i, 0);
    /* y value */
    filterParams[1] = max(j, 0);
    /* default offsetX value */
    filterParams[2] = 0;
    /* default offsetY value */
    filterParams[3] = 0;
    /* default filterSizeX value */
    filterParams[4] = filterSize;
    /* default filterSizeY value */
    filterParams[5] = filterSize;

    // Check if we are on a special case
    int isLeft = i < 0;
    int isRight = i + filterSize > width;
    int isTop = j < 0;
    int isBottom = j + filterSize > height;

    if (isLeft) {
        /* update offsetX value */
        filterParams[2] = padding - filterParams[0];
        /* update filterSizeX value */
        filterParams[4] = filterSize - filterParams[2];
    } else if (isRight) {
        /* update filterSizeX value */
        filterParams[4] = filterSize - padding;
    }

    if (isTop) {
        /* update offsetY value */
        filterParams[3] = padding - filterParams[1];
        /* update filterSizeY value */
        filterParams[5] = filterSize - filterParams[3];
    } else if (isBottom) {
        /* update filterSizeY value */
        filterParams[5] = filterSize - padding;
    }
}

static void convolution2DPaddingSame(layer_t *inputLayer, layer_t *outputLayer, filter_t *kernels, int stride,
                                     float (*activationFunction)(float)) {
    /* Offset between the different filter kernels */
    long kernelFilterOffset = kernels->size * kernels->size;
    /* Offset between the different channel of the input layer */
    long inputChannelOffset = inputLayer->width * inputLayer->height;
    /* Offset between the different channel of the output layer */
    long outputLayerChannelOffset = outputLayer->width * outputLayer->height;

    // 0. We compute the padding sides conditions
    int paddingSize = (kernels->size - 1) / 2;
    int paddingLeftNeeded = ((outputLayer->width - 1) * stride + kernels->size) > inputLayer->width + paddingSize;
    int paddingTopNeeded = ((outputLayer->height - 1) * stride + kernels->size) > inputLayer->height + paddingSize;

    int iStart = paddingLeftNeeded ? -paddingSize : 0;
    int jStart = paddingTopNeeded ? -paddingSize : 0;

    int convolutionParameters[6] = {0};

    // 1. We iterate over the output layer depth
    for (int k = 0; k < outputLayer->depth; ++k) {
        /* Current output layer channel */
        float *const currentOutputChannel = outputLayer->data + outputLayerChannelOffset * k;
        /* Offset between output channel kernels */
        int weightsOffset = k * inputLayer->depth;
        // 2. We iterate over the pixels
        for (int i = iStart; i < inputLayer->width + iStart; i += stride) {
            for (int j = jStart; j < inputLayer->height + jStart; j += stride) {
                /* Convolution function used */
                getConvolutionParameters(i, j, kernels->size, inputLayer->width, inputLayer->height, paddingSize,
                                         convolutionParameters);


                /* Raw value result of the convolution before activation */
                float convolutionValue = 0.f;
                // 3. We iterate over the input layer depth
                for (int l = 0; l < inputLayer->depth; ++l) {
                    /* Current input layer channel */
                    float *const currentInputChannel = inputLayer->data + inputChannelOffset * l;
                    /* Current kernel weights */
                    const float *currentKernelWeights = kernels->weights + kernelFilterOffset * (weightsOffset + l);
                    /* Doing the actual convolution */
                    convolutionValue += convolutionFilterGeneric(currentInputChannel, currentKernelWeights,
                                                                 convolutionParameters, inputLayer->width,
                                                                 kernels->size);

                }
                /* Adding the bias */
                convolutionValue = convolutionValue + kernels->bias[k];
                // 4. We save the result of the output layer
                currentOutputChannel[(i - iStart) / stride +
                                     ((j - jStart) / stride) * outputLayer->width] = activationFunction(
                        convolutionValue);
            }
        }
    }
}

static void convolution2DPaddingValid(layer_t *inputLayer, layer_t *outputLayer, filter_t *kernels, int stride,
                                      float (*activationFunction)(float)) {
    /* Offset between the different filter kernels */
    long kernelFilterOffset = kernels->size * kernels->size;
    /* Offset between the different channel of the input layer */
    long inputLayerChannelOffset = inputLayer->width * inputLayer->height;
    /* Offset between the different channel of the output layer */
    long outputLayerChannelOffset = outputLayer->width * outputLayer->height;


    /* Convolution filter parameters */
    int convolutionParameters[6] = {0};
    /* offsetX */
    convolutionParameters[2] = 0;
    /* offsetY */
    convolutionParameters[3] = 0;
    /* filterSizeX */
    convolutionParameters[4] = kernels->size;
    /* filterSizeY */
    convolutionParameters[5] = kernels->size;

    // 1. We iterate over the output layer depth
    for (int k = 0; k < outputLayer->depth; ++k) {
        /* Current output layer channel */
        float *const outputCurrentLayerChannel = outputLayer->data + outputLayerChannelOffset * k;
        /* Offset between output channel kernels */
        int weightsOffset = k * inputLayer->depth;
        // 2. We iterate over the pixels
        for (int i = 0; i < inputLayer->width; i += stride) {
            for (int j = 0; j < inputLayer->height; j += stride) {
                /* Set x, y values */
                convolutionParameters[0] = i;
                convolutionParameters[1] = j;
                /* Raw value result of the convolution before activation */
                float convolutionValue = 0.f;
                // 3. We iterate over the input layer depth
                for (int l = 0; l < inputLayer->depth; ++l) {
                    /* Current input layer channel */
                    float *const currentInput = inputLayer->data + inputLayerChannelOffset * l;
                    /* Current kernel weights */
                    const float *kernelWeights = kernels->weights + kernelFilterOffset * (weightsOffset + l);
                    /* Doing the actual convolution */
                    convolutionValue += convolutionFilterGeneric(currentInput, kernelWeights,
                                                                 convolutionParameters, inputLayer->width,
                                                                 kernels->size);
                }
                /* Adding the bias */
                convolutionValue = convolutionValue + kernels->bias[k];
                // 4. We save the result of the output layer
                outputCurrentLayerChannel[i / stride + (j / stride) * outputLayer->width] = activationFunction(
                        convolutionValue);
            }
        }
    }
}

int
convolution2D_sequential(layer_t *inputLayer, layer_t *outputLayer, filter_t *kernelFilters, int stride, int padding,
                         int activation) {
    if (!inputLayer || !outputLayer || !kernelFilters) {
        fprintf(stderr, "ERROR: Null pointer passed as inputLayer.\n");
        return -1;
    }
    // 0. Checking sizes
    if (inputLayer->height <= 0 || inputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for inputLayer layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", inputLayer->width, inputLayer->height);
        return -1;
    }
    if (outputLayer->height <= 0 || outputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", outputLayer->width, outputLayer->height);
        return -1;
    }
    if (kernelFilters->size <= 0) {
        fprintf(stderr, "ERROR: Invalid size for kernel filters.\n");
        fprintf(stderr, "       |--> Size: %d\n", kernelFilters->size);
        return -1;
    }

    // 0. Select the activation function
    float (*activationFunction)(float) = activationReLU;
    if (activation == ACTIVATION_LINEAR) {
        activationFunction = activationLinear;
    }

    // 1. Select among convolution with or without padding
    if (padding == PADDING_SAME) {
        convolution2DPaddingSame(inputLayer, outputLayer, kernelFilters, stride, activationFunction);
    } else {
        convolution2DPaddingValid(inputLayer, outputLayer, kernelFilters, stride, activationFunction);
    }

    return 0;
}


int maxPooling2D_sequential(layer_t *inputLayer, layer_t *outputLayer, int poolWidth, int poolHeight, int stride) {
    if (!inputLayer || !outputLayer) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (inputLayer->height <= 0 || inputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", inputLayer->width, inputLayer->height);
        return -1;
    }
    if (outputLayer->height <= 0 || outputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", outputLayer->width, outputLayer->height);
        return -1;
    }
    if (poolWidth <= 0 || poolHeight <= 0) {
        fprintf(stderr, "ERROR: Invalid size for max pool operator.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", poolWidth, poolHeight);
        return -1;
    }
    if (inputLayer->depth != outputLayer->depth) {
        fprintf(stderr, "ERROR: Input layer should have the same size as the output layer.\n");
        return -1;
    }

    // 1. Applying the maxpool operator
    for (int i = 0; i < inputLayer->depth; ++i) {
        float *const currentInputLayerChannel = inputLayer->data + inputLayer->width * inputLayer->height * i;
        float *const currentOutputLayerChannel = outputLayer->data + outputLayer->width * outputLayer->height * i;
        for (int x = 0; x < inputLayer->width - (poolWidth - 1); x += stride) {
            for (int y = 0; y < inputLayer->height - (poolHeight - 1); y += stride) {
                float max = 0.f;
                for (int mj = 0; mj < poolHeight; ++mj) {
                    for (int mi = 0; mi < poolWidth; ++mi) {
                        float value = currentInputLayerChannel[(x + mi) + (y + mj) * inputLayer->width];
                        max = max < value ? value : max;
                    }
                }
                currentOutputLayerChannel[x / stride + (y / stride) * outputLayer->width] = max;
            }
        }
    }

    return 0;
}


int averagePooling2D_sequential(layer_t *inputLayer, layer_t *outputLayer, int avgWidth, int avgHeight) {
    if (!inputLayer || !outputLayer) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (inputLayer->height <= 0 || inputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", inputLayer->width, inputLayer->height);
        return -1;
    }
    if (outputLayer->height <= 0 || outputLayer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", outputLayer->width, outputLayer->height);
        return -1;
    }
    if (outputLayer->depth != inputLayer->depth) {
        fprintf(stderr, "ERROR: Layers should have the same size!\n");
        fprintf(stderr, "       Input layer size:  %d\n", inputLayer->depth);
        fprintf(stderr, "       Output layer size: %d\n", outputLayer->depth);
        return -1;
    }

    int offset_output_layer = outputLayer->width * outputLayer->height;
    int offset_input_layer = inputLayer->width * inputLayer->height;
    /* Going though input / output layer channels */
    for (int i = 0; i < outputLayer->depth; ++i) {
        for (int y = 0; y < outputLayer->height; ++y) {
            for (int x = 0; x < outputLayer->width; ++x) {
                float average = 0.f;
                /* Averaging over the kernel size */
                for (int aj = 0; aj < avgHeight; ++aj) {
                    for (int ai = 0; ai < avgWidth; ++ai) {
                        average += inputLayer->data[offset_input_layer * i + ai + aj * inputLayer->width];
                    }
                }
                average /= (avgWidth * avgHeight);
                outputLayer->data[offset_output_layer * i + x + y * outputLayer->width] = average;
            }
        }
    }
    return 0;
}

int softmaxActivation_sequential(float *input, double *output, int size) {
    if (!input || !output) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }

    /* Normalization coefficient */
    float sum = 0.f;
    // 0. Compute Exp(input) for all input
    for (int i = 0; i < size; ++i) {
        output[i] = exp(input[i]);
        sum += output[i];
    }

    // 1. Compute SoftMax output
    for (int i = 0; i < size; ++i) {
        output[i] /= sum;
    }

    return 0;
}
