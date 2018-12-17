//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_CONVOLUTION_H
#define SQUEEZENET_C_CONVOLUTION_H


#define PADDING_VALID 0
#define PADDING_SAME  1

#define ACTIVATION_RELU 0
#define ACTIVATION_LINEAR 1


//typedef enum padding_t{PADDING_LEFT = 0, PADDING_TOP = 1, PADDING_RIGHT = 2, PADDING_BOTTOM = 3, PADDING_RIGHT = 0, PADDING_RIGHT = 0};

typedef struct layer_t {
    int width;
    int height;
    int depth;
    float *data;
} layer_t;

typedef struct filter_t {
    int size;
    float *weights;
    float *bias;
} filter_t;


/**
 * @brief  Convolution layer of a CNN
 *
 * @param input_layer    input layer of size N*M*D
 * @param output_layer   output layer of size N2*M2*D2
 * @param kernel_filters kernel filters used for the convolution
 * @param stride         stride of the filtering
 * @param padding        type of padding used (PADDING_VALID = no padding, PADDING_SAME = padding)
 * @return 0 on SUCCESS, -1 on ERROR
 */
int convolution2D_sequential(layer_t *input_layer, layer_t *output_layer, filter_t *kernel_filters, int stride, int padding,
                  int activation);

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
int maxPooling2D_sequential(layer_t *input_layer, layer_t *output_layer, int max_pool_width, int max_pool_height, int stride);

/**
 * @brief Perform an average pooling operation
 *
 * @param input_layer  Input layer of size N*M*D
 * @param output_layer Output layer of size N2*M2*D2
 * @param avg_width    Width of the average operator
 * @param avg_height   Height of the average operator
 * @return
 */
int averagePooling2D_sequential(layer_t *input_layer, layer_t *output_layer, int avg_width, int avg_height);

int softmaxActivation_sequential(float *input, double *output, int size);


#endif //SQUEEZENET_C_CONVOLUTION_H
