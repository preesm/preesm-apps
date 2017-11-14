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
 * This compute the output of neuron[i] of a hidden layer of a MLP neural network
 *
 * With n input values, weights array is constructed this way:
 *      weight[0] -> weight from input[0] to neuron[i]
 *      weight[1] -> weight from input[1] to neuron[i]
 *      ...
 *      weight[n] -> weight from input[n] to neuron[i]
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
 * @brief Hyperbolic tangent activation function
 *
 *                            2
 *    f(x) = tanh(x) = (--------------) - 1
 *                       1 + exp(-2x)
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateTanHyperbolic(IN float *input,
                           OUT float *output);

/**
 * @brief Rectified Linear Unit activation function
 *
 *            | 0, x < 0
 *     f(x) = |
 *            | x, else
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateReLU(IN float *input,
                  OUT float *output);

/**
 * @brief Soft sign activation function
 *
 *                 x
 *     f(x) = ------------
 *             1 + abs(x)
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateSoftSign(IN float *input,
                      OUT float *output);

/**
 * @brief Sigmoid activation function
 *
 *                 1
 *     f(x) = ------------
 *             1 + exp(-x)
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateSigmoid(IN float *input,
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

/**
 * @brief Performs the Mean Square Error loss operation
 *
 * @param size         Size of the arrays
 * @param labels       Array filled with target values
 * @param predictions  Array filled with predicted values
 * @param mse_output   Scalar value of the MSE
 */
void lossMSE(int size,
             IN float *labels, IN float *predictions,
             OUT float *mse_output);

#endif //MLP_H
