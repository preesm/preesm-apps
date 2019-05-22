#ifndef UTILITY_H
#define UTILITY_H

#include "common.h"

#include "preesm.h"

/**
 * @brief Read an image specified by a given path and load it as an F32 vector
 *
 * @param path   Path to the image.
 * @param depth  Pointer to be filled with the depth of the image.
 * @param width  Pointer to be filled with the width of the image.
 * @param height Pointer to be filled with the height of the image.
 * @return pointer to the F32 loaded image on SUCCESS, NULL on ERROR
 */
float *loadImageF32(const char *path, int *depth, int *width, int *height);


/**
 * @brief Read an image specified by DEFAULT_PATH_IMG and load it as an F32 vector.
 *        We assume the image is of depth 3.
 *
 * @param width  Width of the image.
 * @param height Height of the image.
 * @param out    Pointer to be filled with the F32 image.
 * @return 0 on SUCCESS, -1 on ERROR
 */
int readImageRawF32(IN int width, IN int height, OUT float *out);

/**
 * @brief Load weights and biases from raw binary file
 *
 * @param pathWeights  Path to the file containing the weights.
 * @param pathBiases   Path to the file containing the biases.
 * @param weights       Pointer of the array of weights to be initialized and filled by the content of the weights file.
 * @param biases        Pointer of the array of biases to be initialized and filled by the content of the biases file.
 * @return 0 on SUCCESS, -1 on ERROR
 */
int loadRawWeightsAndBiases(const char *pathWeights, const char *pathBiases, const float **weights, const float **biases);

/**
 * @brief Load weights and biases from raw binary file specified by DEFAULT_PATH_WEIGHTS and DEFAULT_PATH_BIASES.
 *
 * @param path_weights  Path to the file containing the weights.
 * @param path_biases   Path to the file containing the biases.
 * @param weights       Pointer of the array of weights to be initialized and filled by the content of the weights file.
 * @param biases        Pointer of the array of biases to be initialized and filled by the content of the biases file.
 * @return 0 on SUCCESS, -1 on ERROR
 */
int genRawWeightsAndBiases(IN long sizeWeights, IN long sizeBiases, 
                           OUT float *weights, OUT float *biases);


#endif // UTILITY_H
