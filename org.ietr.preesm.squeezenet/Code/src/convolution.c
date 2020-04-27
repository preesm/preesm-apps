//
// Created by farresti on 21/08/18.
//

#include <stdio.h>
#include <math.h>
#include <common.h>
#include <convolution.h>

static inline float activationReLU(float x) {
    return x > 0 ? x : 0;
}

static inline float activationLinear(float x) {
    return x;
}

int maxPooling2D(IN int widthInput, IN int heightInput,
                 IN int widthOutput, IN int heightOutput,
                 IN int poolWidth, IN int poolHeight, IN int stride,
                 IN float *input, OUT float *out) {
    if (!input || !out) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (widthInput <= 0 || heightInput <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", widthInput, heightInput);
        return -1;
    }
    if (widthOutput <= 0 || heightOutput <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", widthOutput, heightOutput);
        return -1;
    }
    if (poolWidth <= 0 || poolHeight <= 0) {
        fprintf(stderr, "ERROR: Invalid size for max pool operator.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", poolWidth, poolHeight);
        return -1;
    }

    // 1. Applying the maxpool operator
    for (int x = 0; x < widthInput - (poolWidth - 1); x += stride) {
        for (int y = 0; y < heightInput - (poolHeight - 1); y += stride) {
            float max = 0;
            for (int mi = 0; mi < poolWidth; ++mi) {
                for (int mj = 0; mj < poolHeight; ++mj) {
                    float value = input[(x + mi) + (y + mj) * widthInput];
                    max = max < value ? value : max;
                }
            }
            out[(x / stride) + (y / stride) * widthOutput] = max;
        }
    }
    return 0;
}


int averagePooling2D(IN int widthInput, IN int heightInput,
                     IN int widthOutput, IN int heightOutput,
                     IN int avgWidth, IN int avgHeight,
                     IN float *input, OUT float *out) {
    if (!input || !out) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (heightOutput <= 0 || widthOutput <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", widthOutput, heightOutput);
        return -1;
    }
    if (heightInput <= 0 || widthInput <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", widthInput, heightInput);
        return -1;
    }

    /* Going though input / output layer channels */
    float averageFactor = avgWidth * avgHeight;
    for (int y = 0; y < heightOutput; ++y) {
        for (int x = 0; x < widthOutput; ++x) {
            int currentOutputPixel = x + y * widthOutput;
            out[currentOutputPixel] = 0.f;
            /* Averaging over the kernel size */
            for (int aj = 0; aj < avgHeight; ++aj) {
                for (int ai = 0; ai < avgWidth; ++ai) {
                    out[currentOutputPixel] += input[ai + aj * widthInput];
                }
            }
            out[currentOutputPixel] /= averageFactor;
        }
    }
    return 0;
}

int softmaxActivation(IN int size, IN float *input, OUT double *output) {
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


void convolution2D(IN int widthInput, IN int heightInput, IN int depthInput,
                   IN int widthOutput, IN int heightOutput,
                   IN int sizeKernel, IN int stride,
                   IN float *input, IN float *weights, IN float *bias,
                   OUT float *out) {
    /* Offset between the different filter kernels */
    long weightsOffset = sizeKernel * sizeKernel;
    /* Offset between the different channel of the input layer */
    long inputOffset = widthInput * heightInput;

    // 0. We compute the padding sides conditions
    int paddingSize = (sizeKernel - 1) / 2;
    int paddingLeftNeeded = ((widthOutput - 1) * stride + sizeKernel) > widthInput + paddingSize;
    int paddingTopNeeded = ((heightOutput - 1) * stride + sizeKernel) > heightInput + paddingSize;

    int iStart = paddingLeftNeeded ? -paddingSize : 0;
    int jStart = paddingTopNeeded ? -paddingSize : 0;

    int convolutionParameters[6] = {0};

    // 1. We iterate over the pixels
    for (int i = iStart; i < widthInput + iStart; i += stride) {
        for (int j = jStart; j < heightInput + jStart; j += stride) {
            /* Convolution function used */
            getConvolutionParameters(i, j, sizeKernel, widthInput, heightInput, paddingSize,
                                     convolutionParameters);


            /* Raw value result of the convolution before activation */
            float convolutionValue = 0.f;
            // 3. We iterate over the input layer depth
            for (int l = 0; l < depthInput; ++l) {
                /* Current input layer channel */
                float *currentInput = input + inputOffset * l;
                /* Current kernel weights */
                float *currentWeights = weights + weightsOffset * (l);
                /* Doing the actual convolution */
                convolutionValue += convolutionFilterGeneric(currentInput, currentWeights,
                                                             convolutionParameters, widthInput,
                                                             sizeKernel);

            }
            /* Adding the bias */
            convolutionValue = convolutionValue + bias[0];
            float (*activationFunction)(float) = activationReLU;
            // 4. We save the result of the output layer
            out[(i - iStart) / stride + ((j - jStart) / stride) * widthOutput] = activationFunction(convolutionValue);
        }
    }
}
