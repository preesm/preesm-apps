//
// Created by farresti on 21/08/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "squeezenet.h"
#include "convolution-sequential.h"
#include "labels.h"



static void conv1(float *input, float *output, float *weights, float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 224, .height = 224, .depth = 3, .data = input};
    layer_t conv1_layer = {.width = 112, .height = 112, .depth = 64, .data = output};
    filter_t conv1_kernels = {.size = 3, .weights = weights, .bias = biases};

    // Convolution layer
    convolution2D_sequential(&input_layer, &conv1_layer, &conv1_kernels, 2, PADDING_SAME, ACTIVATION_RELU);
}

static void maxpool1( float *input, float *output)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 112, .height = 112, .depth = 64, .data = input};
    layer_t maxpool1_layer = {.width = 55, .height = 55, .depth = 64, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&input_layer, &maxpool1_layer, 3, 3, 2);
}

static void fire2( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 55, .height = 55, .depth = 64, .data = input};
    layer_t fire2_concatenate_layer = {.width = 55, .height = 55, .depth = 128, .data = output};
    const int fire2_sizes[3] = {16, 64, 64};

    // Squeeze - Expand layer
    fire(&input_layer, &fire2_concatenate_layer, weights, biases, fire2_sizes);
}

static void fire3( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 55, .height = 55, .depth = 128, .data = input};
    layer_t fire3_concatenate_layer = {.width = 55, .height = 55, .depth = 128, .data = output};
    const int fire3_sizes[3] = {16, 64, 64};

    // Squeeze - Expand layer
    fire(&input_layer, &fire3_concatenate_layer, weights, biases, fire3_sizes);
}

static void maxpool3( float *input, float *output)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 55, .height = 55, .depth = 128, .data = input};
    layer_t maxpool3_layer = {.width = 27, .height = 27, .depth = 128, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&input_layer, &maxpool3_layer, 3, 3, 2);

}

static void fire4( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 27, .height = 27, .depth = 128, .data = input};
    layer_t fire4_concatenate_layer = {.width = 27, .height = 27, .depth = 256, .data = output};
    const int fire4_sizes[3] = {32, 128, 128};

    // Squeeze - Expand layer
    fire(&input_layer, &fire4_concatenate_layer, weights, biases, fire4_sizes);
}

static void fire5( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 27, .height = 27, .depth = 256, .data = input};
    layer_t fire5_concatenate_layer = {.width = 27, .height = 27, .depth = 256, .data = output};
    const int fire5_sizes[3] = {32, 128, 128};

    // Squeeze - Expand layer
    fire(&input_layer, &fire5_concatenate_layer, weights, biases, fire5_sizes);
}

static void maxpool5( float *input, float *output)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 27, .height = 27, .depth = 256, .data = input};
    layer_t maxpool5_layer = {.width = 13, .height = 13, .depth = 256, .data = output};

    // MaxPooling layer
    maxPooling2D_sequential(&input_layer, &maxpool5_layer, 3, 3, 2);

}

static void fire6( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 256, .data = input};
    layer_t fire6_concatenate_layer = {.width = 13, .height = 13, .depth = 384, .data = output};
    const int fire6_sizes[3] = {48, 192, 192};

    // Squeeze - Expand layer
    fire(&input_layer, &fire6_concatenate_layer, weights, biases, fire6_sizes);
}

static void fire7( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 384, .data = input};
    layer_t fire7_concatenate_layer = {.width = 13, .height = 13, .depth = 384, .data = output};
    const int fire7_sizes[3] = {48, 192, 192};

    // Squeeze - Expand layer
    fire(&input_layer, &fire7_concatenate_layer, weights, biases, fire7_sizes);
}

static void fire8( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 384, .data = input};
    layer_t fire8_concatenate_layer = {.width = 13, .height = 13, .depth = 512, .data = output};
    const int fire8_sizes[3] = {64, 256, 256};

    // Squeeze - Expand layer
    fire(&input_layer, &fire8_concatenate_layer, weights, biases, fire8_sizes);
}

static void fire9( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 512, .data = input};
    layer_t fire9_concatenate_layer = {.width = 13, .height = 13, .depth = 512, .data = output};
    const int fire9_sizes[3] = {64, 256, 256};

    // Squeeze - Expand layer
    fire(&input_layer, &fire9_concatenate_layer, weights, biases, fire9_sizes);
}

static void conv10( float *input, float *output,  float *weights,  float *biases)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 512, .data = input};
    layer_t conv10_layer = {.width = 13, .height = 13, .depth = 1000, .data = output};
    filter_t conv10_kernels = {.size = 1, .weights = weights, .bias = biases};

    // Convolution layer
    convolution2D_sequential(&input_layer, &conv10_layer, &conv10_kernels, 1, PADDING_SAME, ACTIVATION_LINEAR);
}

static void avgpool10(float *input, float *output)  {
    // Setting up the layer parameters
    layer_t input_layer = {.width = 13, .height = 13, .depth = 1000, .data = input};
    layer_t avgpool10_layer = {.width = 1, .height = 1, .depth = 1000, .data = output};

    // Average Layer
    averagePooling2D_sequential(&input_layer, &avgpool10_layer, 13, 13);
}

static void softmax( float *input, double *output) {
    softmaxActivation_sequential(input, output, 1000);
}


int squeezenetDecode(IN int size, IN double *predictions) {
    // Find the maximum values
    double top_probs[3] = {0};
    int top_indexes[3] = {0};
    for (int i = 0; i < size; ++i) {
        if (top_probs[0] < predictions[i]) {
            top_indexes[0] = i;
            top_probs[0] = predictions[i];
        }
    }
    for (int i = 0; i < size; ++i) {
        if (top_probs[1] < predictions[i] && predictions[i] < top_probs[0]) {
            top_indexes[1] = i;
            top_probs[1] = predictions[i];
        }
    }
    for (int i = 0; i < size; ++i) {
        if (top_probs[2] < predictions[i] && predictions[i] < top_probs[1]) {
            top_indexes[2] = i;
            top_probs[2] = predictions[i];
        }
    }
    fprintf(stderr, "Top 3 predictions: \n");
    fprintf(stderr, "    1. %s with probability: %.10e\n",squeezenet_labels[top_indexes[0]], predictions[top_indexes[0]]);
    fprintf(stderr, "    2. %s with probability: %.10e\n",squeezenet_labels[top_indexes[1]], predictions[top_indexes[1]]);
    fprintf(stderr, "    3. %s with probability: %.10e\n",squeezenet_labels[top_indexes[2]], predictions[top_indexes[2]]);
    return top_indexes[0];
}

void fire(layer_t *input_layer, layer_t *output_layer, float *kernels_weights, float *biases, const int sizes[3]) {
    // 0. First, building the layers
    layer_t expand1x1_layer = {.width = input_layer->width,
            .height = input_layer->height,
            .depth = sizes[1],
            .data = output_layer->data};
    long long expand1x1_layer_offset = expand1x1_layer.width * expand1x1_layer.height * expand1x1_layer.depth;
    layer_t expand3x3_layer = {.width = input_layer->width,
            .height = input_layer->height,
            .depth = sizes[2],
            .data = output_layer->data + expand1x1_layer_offset};
    long long expand3x3_layer_offset = expand1x1_layer_offset * 2;
    layer_t squeeze_layer = {.width = input_layer->width,
            .height = input_layer->height,
            .depth = sizes[0],
            .data = output_layer->data + expand3x3_layer_offset};

    // 1. Squeeze layer
    filter_t squeeze_kernels = {.size = 1, .weights =  kernels_weights, .bias = biases};
    convolution2D_sequential(input_layer, &squeeze_layer, &squeeze_kernels, 1, PADDING_SAME, ACTIVATION_RELU);

    // 2. Expand 1x1 layer
    filter_t expand1x1_kernels = {.size = 1, .weights =  kernels_weights + squeeze_layer.depth *
                                                                           input_layer->depth, .bias =
    biases + squeeze_layer.depth};
    convolution2D_sequential(&squeeze_layer, &expand1x1_layer, &expand1x1_kernels, 1, PADDING_SAME, ACTIVATION_RELU);

    // 3. Expand 3x3 layer
    filter_t expand3x3_kernels = {.size = 3, .weights =  kernels_weights +
                                                         squeeze_layer.depth * input_layer->depth +
                                                         expand1x1_layer.depth *
                                                         squeeze_layer.depth, .bias = biases +
                                                                                      squeeze_layer.depth +
                                                                                      expand1x1_layer.depth};
    convolution2D_sequential(&squeeze_layer, &expand3x3_layer, &expand3x3_kernels, 1, PADDING_SAME, ACTIVATION_RELU);
}

int squeezenetPredict(float *input_image, int width, int height, int depth, float *weights, float *biases, double *result) {
    // 0. First create the full size arrays for all layers
    float *input_buffer = malloc(MAX_BUFFER_SIZE * sizeof(float));
    if (!input_buffer) {
        fprintf(stderr, "ERROR: Unable to allocate memory input buffer.\n");
        return -1;
    }

    float *output_buffer = malloc(MAX_BUFFER_SIZE * sizeof(float));
    if (!output_buffer) {
        fprintf(stderr, "ERROR: Unable to allocate memory input buffer.\n");
        return -1;
    }

    float *local_weights = weights;
    float *local_biases = biases;

    // 1. Conv2D
    memcpy(input_buffer, input_image, width * height * depth * sizeof(float));
    conv1(input_buffer, output_buffer, local_weights, local_biases);

    // 2. MaxPooling2D
    maxpool1(output_buffer, input_buffer);

    // 3. Fire2
    local_weights = local_weights + 1728;
    local_biases = local_biases + 64;
    fire2(input_buffer, output_buffer, local_weights, local_biases);

    // 4. Fire3
    local_weights = local_weights + 1024 + 1024 + 9216;
    local_biases = local_biases + 16 + 64 + 64;
    fire3(output_buffer, input_buffer, local_weights, local_biases);

    // 5. MaxPooling2D
    maxpool3(input_buffer, output_buffer);

    // 6. Fire4
    local_weights = local_weights + 2048 + 1024 + 9216;
    local_biases = local_biases + 16 + 64 + 64;
    fire4(output_buffer, input_buffer, local_weights, local_biases);

    // 7. Fire5
    local_weights = local_weights + 4096 + 4096 + 36864;
    local_biases = local_biases + 32 + 128 + 128;
    fire5(input_buffer, output_buffer, local_weights, local_biases);

    // 8. MaxPooling2D
    maxpool5(output_buffer, input_buffer);

    // 9. Fire6
    local_weights = local_weights + 8192 + 4096 + 36864;
    local_biases = local_biases + 32 + 128 + 128;
    fire6(input_buffer, output_buffer, local_weights, local_biases);

    // 10. Fire7
    local_weights = local_weights + 12288 + 9216 + 82944;
    local_biases = local_biases + 48 + 192 + 192;
    fire7(output_buffer, input_buffer, local_weights, local_biases);

    // 11. Fire8
    local_weights = local_weights + 18432 + 9216 + 82944;
    local_biases = local_biases + 48 + 192 + 192;
    fire8(input_buffer, output_buffer, local_weights, local_biases);

    // 12. Fire9
    local_weights = local_weights + 24576 + 16384 + 147456;
    local_biases = local_biases + 64 + 256 + 256;
    fire9(output_buffer, input_buffer, local_weights, local_biases);

    // 13. Conv2D
    local_weights = local_weights + 32768 + 16384 + 147456;
    local_biases = local_biases + 64 + 256 + 256;
    conv10(input_buffer, output_buffer, local_weights, local_biases);

    // 14. GlobalAveragePooling2D
    avgpool10(output_buffer, input_buffer);

    // 15. SoftMax
    softmax(input_buffer, result);

    // 16. Decode prediction
    //int best = squeezenetDecode(result);

    // Cleaning memory
    free(input_buffer);
    free(output_buffer);
    return 0;
}







