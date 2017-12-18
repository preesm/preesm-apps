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
void layer(int input_size, int layer_size,
           IN float *weights, IN float *bias_values, IN float *input, IN int *valid,
           OUT float *output);


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
            IN float *input, IN float *weights, IN float *bias_values, IN int *valid,
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
 * @brief Hyperbolic tangent derivative function
 *
 *                           2
 *    f(x) = tanh(x) = (--------------) - 1
 *                       1 + exp(-2x)
 *    f'(x) = 1 - (f(x))^2
 *
 * @param input  Input value
 * @param output Activated output of a neuron
 */
void derivativeTanHyperbolic(IN float *input,
                             OUT float *output);


/**
 * @brief Hyperbolic tangent derivative function
 *        (optimized version in which the input is f(x) instead of x)
 *
 *                           2
 *    f(x) = tanh(x) = (--------------) - 1
 *                       1 + exp(-2x)
 *    f'(x) = 1 - (f(x))^2
 *
 * @param input  Input value
 * @param output Activated output of a neuron
 */
void derivativeTanHyperbolicActivated(IN float *input,
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
 * @brief Rectified Linear Unit derivative function
 *
 *            | 0, x < 0
 *     f(x) = |
 *            | 1, else
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void derivativeReLU(IN float *input,
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
 * @brief Soft sign derivative function
 *
 *                    1
 *     f'(x) = ----------------
 *              (1 + abs(x))^2
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void derivativeSoftSign(IN float *input,
                        OUT float *output);

/**
 * @brief Logistic activation function
 *
 *                 1
 *     f(x) = ------------
 *             1 + exp(-x)
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateLogistic(IN float *input,
                      OUT float *output);


/**
 * @brief Logistic derivative function
 *
 *                 1
 *     f(x) = ------------
 *             1 + exp(-x)
 *
 *     f'(x) = f(x) * (1 - f(x))
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void derivativeLogistic(IN float *input,
                        OUT float *output);


/**
 * @brief Linear activation function
 *
 *     f(x) = x
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void activateLinear(IN float *input,
                    OUT float *output);


/**
 * @brief Linear derivative function
 *
 *     f(x) = x
 *
 *     f'(x) = 1
 *
 * @param input  Raw output of a neuron
 * @param output Activated output of a neuron
 */
void derivativeLinear(IN float *input,
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


/**************************************/
/********* SEQUENTIAL VERSION *********/
/**************************************/



typedef void (*activate)(float *, float*);
typedef void (*derivative)(float *, float*);

typedef struct {
    double beta1;
    double beta2;
    double beta1_pow;
    double beta2_pow;
    double epsilon;
    double **fst_order_moments;
    double **sec_order_moments;
}adamOptimizer;


typedef struct {
    int size;
    int input_size;
    int output_size;
    int *layer_size;
    float **inputs_layer;
    float *output;
    float **weights;
    float **errors;
    float **gradients;
    float **bias;
    float learning_rate;
    adamOptimizer weight_optimizer;
    adamOptimizer bias_optimizer;
    activate activation_hidden;
    derivative derivative_hidden;
    activate activation_output;
    derivative derivative_output;
}mlp_net;

/**
 * @brief Creates and initiliazes a MLP network.
 *
 * @param n_layer            Number of layer of the network.
 * @param input_size         Size of the input vector.
 * @param sizes              Sizes of the different layer (last value should be equal to output size).
 * @param learning_rate      Learning rate factor for the network.
 * @param activation_hidden  Activation function for hidden layers.
 * @param activation_output  Activation function for output layer.
 * @param derivative_hidden  Derivative function for hidden layers.
 * @param derivative_output  Derivative function for output layer.
 * @return Pointer to the created network, NULL if error.
 */

mlp_net* create_mlp(int n_layer, int input_size, int *sizes, float learning_rate,
                    activate activation_hidden,
                    activate activation_output,
                    derivative derivative_hidden,
                    derivative derivative_output);

/**
 * @brief Run the input vector through the mlp.
 *
 * @param network  Pointer to the network.
 * @param input    Input vector.
 * @param output   Output vector (prediction) of the network.
 */
void run_mlp(mlp_net* network, float *input, float *output);

/**
 *  @brief Print the structure of a MLP with the variable name as identifier
 */
#define print_mlp(net) print_mlp_full(net, #net)

/**
 * @brief Print the structure of a MLP.
 *
 * @param network Pointer to the network.
 * @param name    Name of the network.
 */
void print_mlp_full(mlp_net *network, char *name);


/**
 * @brief Free all memories allocated for a MLP.
 *        The network's pointer is set to NULL by the function.
 *
 * @param network Address of the pointer to the network.
 */
void free_mlp(mlp_net **network);

/**
 * @brief Performs gradients descent on network's weights toward a target.
 *        Update weights using the Adam optimizer algorithm.
 *
 * @param network  Pointer to the network.
 * @param target   Target vector, should be the same size as the output vector of the network.
 */
void update_mlp(mlp_net* network, float *target);

/**
 * @brief Compute gradients of the different weights and bias for every layer depending on the MSE.
 *
 * @param network Pointer to the network.
 * @param target  Target vector, should be the same size as the output vector of the network.
 */
void compute_gradient(mlp_net* network, float *target);

/**
 * @brief Apply the Adam optimizer algorithm on the gradients to update the parameters of the network.
 *
 * @param network Pointer to the network.
 */
void apply_gradient(mlp_net* network);

void print_gradients(mlp_net* network);

/**
 * @brief Saves the netw
 * @param network
 */
void save_mlp(mlp_net *network);

#endif //MLP_H
