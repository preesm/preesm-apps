//
// Created by farresti on 21/08/18.
//

#include <stdio.h>
#include <math.h>
#include <common.h>
#include "convolution-sequential.h"

static inline float activationReLU(float x) {
    return x > 0 ? x : 0;
}

static inline float activationLinear(float x) {
    return x;
}

static float
convolutionFilterNoPadding(const float *input, int x, int y, int input_width, const float *weights, int filter_size,
                           int padding_size) {
    float value = 0;
    for (int j = 0; j < filter_size; ++j) {
        for (int i = 0; i < filter_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[(i) + (j) * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterLeftPadding(const float *input, int x, int y, int input_width, const float *weights, int filter_size,
                             int padding_size) {
    float value = 0;
    int padding_offset = padding_size - x;
    for (int j = 0; j < filter_size; ++j) {
        for (int i = 0; i < filter_size - padding_offset; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[(i + padding_offset) + j * filter_size];
        }
    }
    return value;
}


static float
convolutionFilterRightPadding(const float *input, int x, int y, int input_width, const float *weights, int filter_size,
                             int padding_size) {
    float value = 0;
    for (int j = 0; j < filter_size; ++j) {
        for (int i = 0; i < filter_size - padding_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[i + j * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterTopPadding(const float *input, int x, int y, int input_width, const float *weights,
                            int filter_size,
                            int padding_size) {
    float value = 0;
    int padding_offset = padding_size - y;
    for (int j = 0; j < filter_size - padding_offset; ++j) {
        for (int i = 0; i < filter_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[i + (j + padding_offset) * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterTopLeftPadding(const float *input, int x, int y, int input_width, const float *weights,
                                int filter_size,
                                int padding_size) {
    float value = 0;
    int padding_offset_x = padding_size - x;
    int padding_offset_y = padding_size - y;
    for (int j = 0; j < filter_size - padding_offset_y; ++j) {
        for (int i = 0; i < filter_size - padding_offset_x; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[(i + padding_offset_x) + (j + padding_offset_y) * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterTopRightPadding(const float *input, int x, int y, int input_width, const float *weights,
                                int filter_size,
                                int padding_size) {
    float value = 0;
    int padding_offset_y = padding_size - y;
    for (int j = 0; j < filter_size - padding_offset_y; ++j) {
        for (int i = 0; i < filter_size - padding_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[i + (j + padding_offset_y) * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterBottomPadding(const float *input, int x, int y, int input_width, const float *weights,
                            int filter_size,
                            int padding_size) {
    float value = 0;
    for (int j = 0; j < filter_size - padding_size; ++j) {
        for (int i = 0; i < filter_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[i + j * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterBottomLeftPadding(const float *input, int x, int y, int input_width, const float *weights,
                                int filter_size,
                                int padding_size) {
    float value = 0;
    int padding_offset_x = padding_size - x;
    for (int j = 0; j < filter_size - padding_size; ++j) {
        for (int i = 0; i < filter_size - padding_offset_x; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[(i + padding_offset_x) + j * filter_size];
        }
    }
    return value;
}

static float
convolutionFilterBottomRightPadding(const float *input, int x, int y, int input_width, const float *weights,
                                 int filter_size,
                                 int padding_size) {
    float value = 0;
    for (int j = 0; j < filter_size - padding_size; ++j) {
        for (int i = 0; i < filter_size - padding_size; ++i) {
            value += input[(x + i) + (y + j) * input_width] *
                     weights[i + j * filter_size];
        }
    }
    return value;
}

static void convolution2DPaddingSame(layer_t *input_layer, layer_t *output_layer, filter_t *kernels, int stride,
                                     float (*activationFunction)(float)) {
    /* Offset between the different filter kernels */
    long kernel_filter_offset = kernels->size * kernels->size;
    /* Offset between the different channel of the input layer */
    long input_layer_channel_offset = input_layer->width * input_layer->height;
    /* Offset between the different channel of the output layer */
    long output_layer_channel_offset = output_layer->width * output_layer->height;

    // 0. We compute the padding sides conditions
    int padding_size = (kernels->size - 1) / 2;
    int padding_left_needed = ((output_layer->width - 1) * stride + kernels->size) > input_layer->width + padding_size;
    int padding_top_needed = ((output_layer->height - 1) * stride + kernels->size) > input_layer->height + padding_size;

    int i_start = padding_left_needed ? -padding_size : 0;
    int j_start = padding_top_needed ? -padding_size : 0;

    // 1. We iterate over the output layer depth
    #pragma omp parallel for
    for (int k = 0; k < output_layer->depth; ++k) {
        /* Current output layer channel */
        float *output_current_layer_channel =
                output_layer->data + output_layer_channel_offset * k;
        /* Offset between output channel kernels */
        int output_weights_offset = k * input_layer->depth;
        // 2. We iterate over the pixels
        //#pragma omp parallel for
        for (int i = i_start; i < input_layer->width + i_start; i += stride) {
            for (int j = j_start; j < input_layer->height + j_start; j += stride) {
                /* Convolution function used */
                float (*convolutionFilter)(const float *, int, int, int, const float *, int,
                                           int) = convolutionFilterNoPadding;
                if (i < 0) {
                    convolutionFilter = convolutionFilterLeftPadding;
                } else if (i + kernels->size > input_layer->width) {
                    convolutionFilter = convolutionFilterRightPadding;
                }
                if (j < 0) {
                    if (convolutionFilter == convolutionFilterLeftPadding) {
                        convolutionFilter = convolutionFilterTopLeftPadding;
                    } else if (convolutionFilter == convolutionFilterRightPadding) {
                        convolutionFilter = convolutionFilterTopRightPadding;
                    } else {
                        convolutionFilter = convolutionFilterTopPadding;
                    }
                } else if (j + kernels->size > input_layer->height) {
                    if (convolutionFilter == convolutionFilterLeftPadding) {
                        convolutionFilter = convolutionFilterBottomLeftPadding;
                    } else if (convolutionFilter == convolutionFilterRightPadding) {
                        convolutionFilter = convolutionFilterBottomRightPadding;
                    } else {
                        convolutionFilter = convolutionFilterBottomPadding;
                    }
                }
                /* Raw value result of the convolution before activation */
                float convolution_value = 0.f;
                // 3. We iterate over the input layer depth
                for (int l = 0; l < input_layer->depth; ++l) {
                    /* Current input layer channel */
                    float *input_current_layer_channel =
                            input_layer->data + input_layer_channel_offset * l;
                    /* Current kernel weights */
                    float *current_kernel_weights =
                            kernels->weights + kernel_filter_offset * (output_weights_offset + l);
                    /* Doing the actual convolution */
                    convolution_value += convolutionFilter(input_current_layer_channel, max(i, 0), max(j, 0),
                                                           input_layer->width,
                                                           current_kernel_weights, kernels->size, padding_size);

                }
                /* Adding the bias */
                convolution_value = convolution_value + kernels->bias[k];
                // 4. We save the result of the output layer
                output_current_layer_channel[(i - i_start) / stride +
                                             ((j - j_start) / stride) * output_layer->width] = activationFunction(
                        convolution_value);
            }
        }
    }
}

static void convolution2DPaddingValid(layer_t *input_layer, layer_t *output_layer, filter_t *kernels, int stride,
                                      float (*activationFunction)(float)) {
    /* Offset between the different filter kernels */
    long kernel_filter_offset = kernels->size * kernels->size;
    /* Offset between the different channel of the input layer */
    long input_layer_channel_offset = input_layer->width * input_layer->height;
    /* Offset between the different channel of the output layer */
    long output_layer_channel_offset = output_layer->width * output_layer->height;


    // 1. We iterate over the output layer depth
    //#pragma omp parallel for
    for (int k = 0; k < output_layer->depth; ++k) {
        /* Current output layer channel */
        float *output_current_layer_channel =
                output_layer->data + output_layer_channel_offset * k;
        /* Offset between output channel kernels */
        int output_weights_offset = k * input_layer->depth;
        // 2. We iterate over the pixels
        for (int i = 0; i < input_layer->width; i += stride) {
            for (int j = 0; j < input_layer->height; j += stride) {
                /* Raw value result of the convolution before activation */
                float convolution_value = 0.f;
                // 3. We iterate over the input layer depth
                for (int l = 0; l < input_layer->depth; ++l) {
                    /* Current input layer channel */
                    float *input_current_layer_channel =
                            input_layer->data + input_layer_channel_offset * l;
                    /* Current kernel weights */
                    float *current_kernel_weights =
                            kernels->weights + kernel_filter_offset * (output_weights_offset + l);
                    /* Doing the actual convolution */
                    convolution_value += convolutionFilterNoPadding(input_current_layer_channel, i, j,
                                                                    input_layer->width,
                                                                    current_kernel_weights, kernels->size, 0);

                }
                /* Adding the bias */
                convolution_value = convolution_value + kernels->bias[k];
                // 4. We save the result of the output layer
                output_current_layer_channel[i / stride +
                                             (j / stride) * output_layer->width] = activationFunction(
                        convolution_value);
            }
        }
    }
}

int convolution2D_sequential(layer_t *input_layer, layer_t *output_layer, filter_t *kernel_filters, int stride, int padding,
                  int activation) {
    if (!input_layer || !output_layer || !kernel_filters) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (input_layer->height <= 0 || input_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", input_layer->width, input_layer->height);
        return -1;
    }
    if (output_layer->height <= 0 || output_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", output_layer->width, output_layer->height);
        return -1;
    }
    if (kernel_filters->size <= 0) {
        fprintf(stderr, "ERROR: Invalid size for kernel filters.\n");
        fprintf(stderr, "       |--> Size: %d\n", kernel_filters->size);
        return -1;
    }

    // 0. Select the activation function
    float (*activationFunction)(float) = activationReLU;
    if (activation == ACTIVATION_LINEAR) {
        activationFunction = activationLinear;
    }

    // 1. Select among convolution with or without padding
    if (padding == PADDING_SAME) {
        convolution2DPaddingSame(input_layer, output_layer, kernel_filters, stride, activationFunction);
    } else {
        convolution2DPaddingValid(input_layer, output_layer, kernel_filters, stride, activationFunction);
    }

    return 0;
}


int maxPooling2D_sequential(layer_t *input_layer, layer_t *output_layer, int max_pool_width, int max_pool_height, int stride) {
    if (!input_layer || !output_layer) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (input_layer->height <= 0 || input_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", input_layer->width, input_layer->height);
        return -1;
    }
    if (output_layer->height <= 0 || output_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", output_layer->width, output_layer->height);
        return -1;
    }
    if (max_pool_width <= 0 || max_pool_height <= 0) {
        fprintf(stderr, "ERROR: Invalid size for max pool operator.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", max_pool_width, max_pool_height);
        return -1;
    }
    if (input_layer->depth != output_layer->depth) {
        fprintf(stderr, "ERROR: Input layer should have the same size as the output layer.\n");
        return -1;
    }

    // 1. Applying the maxpool operator
    for (int i = 0; i < input_layer->depth; ++i) {
        int input_layer_channel_offset = input_layer->width * input_layer->height * i;
        int output_layer_channel_offset = output_layer->width * output_layer->height * i;
        for (int x = 0; x < input_layer->width; x += stride) {
            for (int y = 0; y < input_layer->height; y += stride) {
                float max_pool = 0;
                for (int mi = 0; mi < max_pool_width; ++mi) {
                    for (int mj = 0; mj < max_pool_height; ++mj) {
                        float value = input_layer->data[input_layer_channel_offset + (y + mj) +
                                                        (x + mi) * input_layer->width];
                        max_pool = max_pool < value ? value : max_pool;
                    }
                }
                output_layer->data[output_layer_channel_offset + y / stride +
                                   (x / stride) * output_layer->width] = max_pool;
            }
        }
    }

    return 0;
}


int averagePooling2D_sequential(layer_t *input_layer, layer_t *output_layer, int avg_width, int avg_height) {
    if (!input_layer || !output_layer) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Checking sizes
    if (input_layer->height <= 0 || input_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for input layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", input_layer->width, input_layer->height);
        return -1;
    }
    if (output_layer->height <= 0 || output_layer->width <= 0) {
        fprintf(stderr, "ERROR: Invalid size for output layer.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", output_layer->width, output_layer->height);
        return -1;
    }
    if (output_layer->depth != input_layer->depth) {
        fprintf(stderr, "ERROR: Layers should have the same size!\n");
        fprintf(stderr, "       Input layer size:  %d\n", input_layer->depth);
        fprintf(stderr, "       Output layer size: %d\n", output_layer->depth);
        return -1;
    }

    int offset_output_layer = output_layer->width * output_layer->height;
    int offset_input_layer = input_layer->width * input_layer->height;
    /* Going though input / output layer channels */
    for (int i = 0; i < output_layer->depth; ++i) {
        for (int y = 0; y < output_layer->height; ++y) {
            for (int x = 0; x < output_layer->width; ++x) {
                float average = 0.f;
                /* Averaging over the kernel size */
                for (int aj = 0; aj < avg_height; ++aj) {
                    for (int ai = 0; ai < avg_width; ++ai) {
                        average += input_layer->data[offset_input_layer * i + ai + aj * input_layer->width];
                    }
                }
                average /= (avg_width * avg_height);
                output_layer->data[offset_output_layer * i + x + y * output_layer->width] = average;
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
