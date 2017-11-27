//
// Created by farresti on 23/11/17.
//

#ifndef CACLA_MLP_TRAINING_H
#define CACLA_MLP_TRAINING_H

#include "preesm.h"


/**
 * @brief Compute sigma values of a layer. The sigma value is used to compute the gradient
 *        of the weights of a layer.
 *
 *        s_j = g_j'(z_j) * sum(s_k * w_jk)
 *
 *        where:
 *        - j:    index of a node in the current layer l
 *        - g_j:  activation function of node j. (thus g_j' is the derivative of this function)
 *        - z_j:  input to node j. -> z_j = b_j + sum(a_i * w_ij)
 *        - b_j:  bias value of node j in layer l
 *        - a_i:  output value of node i in layer (l - 1). -> a_i = g_i(z_i)
 *        - w_ij: weight connecting node i in layer (l - 1) to node j in layer l
 *        - w_jk: weight connecting node j in layer l to node k in layer (l + 1)
 *        - s_k:  sigma value of node k in layer (l + 1)
 *
 *
 * @param layer_size          Size of the current layer (l).
 * @param next_layer_size     Size of the next layer (l + 1).
 * @param derivative_values   Input vector of the pre-computed derivative values (g_j'(z_j)). Size of (l).
 * @param next_layer_sigmas   Input vector of sigma values of layer (l + 1). Size of (l + 1).
 * @param next_layer_weights  Input vector of weights connecting layer (l) to layer (l + 1). Size of (l) * (l + 1).
 * @param layer_sigmas        Output vector of layer (l) sigma values.
 */
void computeLayerSigma(int layer_size, int next_layer_size,
                       IN float *derivative_values, IN float *next_layer_sigmas, IN float *next_layer_weights,
                       OUT float *layer_sigmas);


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

/**
 * @brief Compute weights' gradients for a given layer
 *
 * @param input_size   Size of the input vector to the layer
 * @param layer_size   Size of the layer
 * @param sigmas       Vector of sigmas (i.e propagated errors) of the layer
 * @param inputs       Vector of inputs to the layer
 * @param gradients    Output vector of gradients
 */
void computeLayerWeightsGradients(int input_size, int layer_size,
                                  IN float *sigmas, IN float *inputs,
                                  OUT float *gradients);


/**
 * @brief  Apply the Adam gradient optimizer
 *         source: KINGMA, Diederik et BA, Jimmy.
 *         Adam: A method for stochastic optimization. arXiv preprint arXiv:1412.6980, 2014.
 *
 * @param size           Size of the vectors
 * @param param_in       Input param vector to update.
 * @param fo_moment_in   First order moment estimation.
 * @param learning_rate  Hyper parameter of the method (default is 0.001)
 * @param so_moment_in   Second raw order moment estimation.
 * @param betas          Hyper parameters beta1 and beta2, also including beta1^t, beta2^t for optimization
 *                       default values: beta1 = 0.9, beta2=0.999
 * @param gradients      Gradient vector of current parameter.
 * @param param_out      Parameter vector updated.
 * @param fo_moment_out  First order moment estimation updated.
 * @param so_moment_out  Second raw order moment estimation updated.
 * @param betas_out
 */
void applyAdamOptimizer(int size,
                        IN float *param_in, IN float *fo_moment_in, IN float *learning_rate,
                        IN float *so_moment_in, IN float *betas, IN float *gradients,
                        OUT float *param_out, OUT float *fo_moment_out, OUT float *so_moment_out, OUT float *betas_out);

#endif //CACLA_MLP_TRAINING_H
