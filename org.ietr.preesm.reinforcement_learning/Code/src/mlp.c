//
// Created by farresti on 03/11/17.
//

// Math lib
#include <math.h>
// Std libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File header
#include "../include/mlp.h"

#ifndef M_PI
#define M_PI 3.1415926535897932385
#endif

void layer(int layer_size, int output_size, float *weights, float *bias_values, float *input, float *output) {
    /*
     * Structure of layer in a MLP:
     *
     * input:       -> N tokens with N the number of neurons of the layer
     * output:      -> O tokens with O the number of neurons of the next layer
     *
     * weights:     -> Matrix of dimension N*O tokens
     * bias_values: -> Vector of O tokens
     *
     */
    // Performs the matrix product between the input vector and the weight matrix
    for (int wo_i = 0; wo_i < output_size; ++wo_i) {
        // Start with the bias_value
        output[wo_i] = bias_values[wo_i];
        int matrix_row = output_size * wo_i;
        for (int wl_i = 0; wl_i < layer_size; ++wl_i) {
            output[wo_i] += weights[matrix_row + wo_i] * input[wl_i];
        }
    }
}

void neuron(int input_size,
            IN float *input, IN float *weights, IN float *bias_values,
            OUT float *output) {
    float result = bias_values[0];
    /*
     * This compute the output of neuron[i] of a layer of a MLP neural network
     *
     * With n input values, weights array is constructed this way:
     *      weight[0] -> weight from input[0] to neuron[i]
     *      weight[1] -> weight from input[1] to neuron[i]
     *      ...
     *      weight[n] -> weight from input[n] to neuron[i]
     *
     */
    for (int wi = 0; wi < input_size; ++wi) {
        //fprintf(stderr, "%lf\n", weights[wi]);
        result += input[wi] * weights[wi];
    }
    (*output) = tanh(result);
}

void neuron_output(int input_size,
                   IN float *input, IN float *weights, IN float *bias_values,
                   OUT float *output) {
    float result = bias_values[0];
    /*
     * This compute the output of neuron[i] of an output layer of a MLP neural network
     *
     * With n input values, weights array is constructed this way:
     *      weight[0] -> weight from input[0] to neuron[i]
     *      weight[1] -> weight from input[1] to neuron[i]
     *      ...
     *      weight[n] -> weight from input[n] to neuron[i]
     *
     */
    for (int wi = 0; wi < input_size; ++wi) {
        //fprintf(stderr, "%lf\n", weights[wi]);
        result += input[wi] * weights[wi];
    }
    (*output) = result;
}


void weightsGen(int input_size, int layer_size,
                IN float *weights_in, IN float *bias_in,
                OUT float *weights_out, OUT float *bias_out) {
    /*
     * Simple copy of the IN data to the OUT data
     */
    memcpy(weights_out, weights_in, input_size * layer_size * sizeof(float));
    memcpy(bias_out, bias_in, layer_size * sizeof(float));
}