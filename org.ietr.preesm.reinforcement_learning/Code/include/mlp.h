//
// Created by farresti on 03/11/17.
//

#ifndef MLP_H
#define MLP_H

#include "preesm.h"

/**
 * @brief Generic layer actor for a MLP
 *
 * The activation function use is the hyperbolic tangent
 *
 * @param layer_size   Number of neurons composing current layer
 * @param output_size  Number of neurons of the next layer
 * @param weights      Weights matrix of the layer (size=layer_size*output_size)
 * @param bias_values  Bias vector values of the layer (size=output_size)
 * @param input   Input value vector of size "layer_size"
 * @param output  Output value vector of size "output_size"
 */
void layer(int layer_size, int output_size, float *weights, float *bias_values, float *input, float *output);


/**
 * @brief Generic neuron actor for MLP
 *
 * This compute the output of neuron[i] of a layer of a MLP neural network
 *
 * With n input values, weights array is constructed this way:
 *      weight[0] -> weight from input[0] to neuron[i]
 *      weight[1] -> weight from input[1] to neuron[i]
 *      ...
 *      weight[n] -> weight from input[n] to neuron[i]
 *
 * Output is obtained using an hyperbolic tangent activation function
 *
 * @param input_size  Size of the previous layer
 * @param input       Input values (output of the previous layer)
 * @param weights     Weights associated to the inputs
 * @param bias_values Bias values associated to the neuron
 * @param output      Response of the neuron to the inputs
 */
void neuron(int input_size,
            IN float *input, IN float *weights, IN float *bias_values,
            OUT float *output);

/**
 * @brief Output neuron actor for MLP
 *
 * This compute the output of neuron[i] of a layer of a MLP neural network
 *
 * With n input values, weights array is constructed this way:
 *      weight[0] -> weight from input[0] to neuron[i]
 *      weight[1] -> weight from input[1] to neuron[i]
 *      ...
 *      weight[n] -> weight from input[n] to neuron[i]
 *
 *
 * @param input_size  Size of the previous layer
 * @param input       Input values (output of the previous layer)
 * @param weights     Weights associated to the inputs
 * @param bias_values Bias values associated to the neuron
 * @param output      Response of the neuron to the inputs
 */
void neuron_output(int input_size,
                   IN float *input, IN float *weights, IN float *bias_values,
                   OUT float *output);
/**
 * @brief Handle the weights and biases of layer of a MLP
 *
 * @param input_size  Size of the previous layer
 * @param layer_size  Size of the current layer
 * @param weights_in  Input weights
 * @param bias_in     Input bias
 * @param weights_out Output copy of the input
 * @param bias_out    Output copy of the input
 */

void weightsGen(int input_size, int layer_size,
                IN float *weights_in, IN float *bias_in,
                OUT float *weights_out, OUT float *bias_out);

#endif //MLP_H
