//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_CONVOLUTION_SEQUENTIAL_H
#define SQUEEZENET_C_CONVOLUTION_SEQUENTIAL_H


#define PADDING_VALID 0
#define PADDING_SAME  1

#define ACTIVATION_RELU 0
#define ACTIVATION_LINEAR 1

typedef struct layer_t {
    int width;
    int height;
    int depth;
    float *const data;
} layer_t;

typedef struct filter_t {
    int size;
    const float *weights;
    const float *bias;
} filter_t;

float
convolutionFilterGeneric(const float *input, const float *weights, const int filterParams[6], int width,
                         int filterSize);

void
getConvolutionParameters(int i, int j, int filterSize, int width, int height, int padding, int filterParams[6]);

/**
 * @brief  Convolution layer of a CNN
 *
 * @param inputLayer    Input layer of size N*M*D
 * @param outputLayer   Output layer of size N2*M2*D2
 * @param kernelFilters Kernel filters used for the convolution
 * @param stride        Stride of the filtering
 * @param padding       Type of padding used (PADDING_VALID = no padding, PADDING_SAME = padding)
 * @return 0 on SUCCESS, -1 on ERROR
 */
int
convolution2D_sequential(layer_t *inputLayer, layer_t *outputLayer, filter_t *kernelFilters, int stride, int padding,
                         int activation);

/**
 * @brief Perform a max pool operation
 *
 * Note: Padding is PADDING_VALID by default.
 *
 * @param inputLayer   Input layer of size N*M*D
 * @param outputLayer  Output layer of size N2*M2*D2
 * @param poolWidth    Width of the max pool operator
 * @param poolHeight   Height of the max pool operator
 * @param stride       Stride
 *
 * @return 0 on SUCCESS, -1 on ERROR
 */
int maxPooling2D_sequential(layer_t *inputLayer, layer_t *outputLayer, int poolWidth, int poolHeight, int stride);

/**
 * @brief Perform an average pooling operation
 *
 * @param inputLayer  Input layer of size N*M*D
 * @param outputLayer Output layer of size N2*M2*D2
 * @param avgWidth    Width of the average operator
 * @param avgHeight   Height of the average operator
 * @return 0 on SUCCESS, -1 on ERROR
 */
int averagePooling2D_sequential(layer_t *inputLayer, layer_t *outputLayer, int avgWidth, int avgHeight);

/**
 * @brief Perform softmax activation on input vector.
 *
 * @param input  Input vector of size N.
 * @param output Output vector of size N.
 * @param size   Size N of the vectors.
 * @return 0 on SUCCESS, -1 on ERROR
 */
int softmaxActivation_sequential(float *input, double *output, int size);


#endif //SQUEEZENET_C_CONVOLUTION_H
