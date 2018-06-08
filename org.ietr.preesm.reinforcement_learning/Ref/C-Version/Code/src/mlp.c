//
// Created by farresti on 03/11/17.
//

// math lib
#include <math.h>
// std libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <actor_mlp.h>
// file header
#include "../include/mlp.h"
#include "../include/common.h"

void layer(int input_size, int layer_size,
           IN float *weights, IN float *bias_values, IN float *input, IN int *valid,
           OUT float *output) {
    if (*valid == 0) {
        for (int i = 0; i < layer_size; ++i) {
            output[i] = 0;
        }
        return;
    }
    /*
     * Structure of layer in a MLP:
     *
     * input:       -> N tokens with N the number of input to the layer
     * output:      -> O tokens with O the number of neurons of the layer
     *
     * weights:     -> Matrix of dimension N*O tokens
     * bias_values: -> Vector of O tokens
     *
     */
    // Performs the matrix product between the input vector and the weight matrix
    int offset_neuron = 0;
    for (int n = 0; n < layer_size; ++n) {
        float neuron = bias_values[n];
        for (int i = 0; i < input_size; ++i) {
            neuron += input[i] * weights[offset_neuron + i];
        }
        output[n] = neuron;
        offset_neuron += input_size;
    }
}

void neuron(int input_size,
            IN float *input, IN float *weights, IN float *bias_values, IN int *valid,
            OUT float *output) {
    if (*valid == 0) {
        (*output) = 0;
    } else {
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
            result += input[wi] * weights[wi];
        }
        (*output) = result;
    }
}

void activateTanHyperbolic(IN float *input,
                           OUT float *output) {
    output[0] = (float)(tanh((double)(input[0])));
}

void derivativeTanHyperbolic(IN float *input,
                             OUT float *output) {
    float f_x = (float)(tanh((double)(input[0])));
    output[0] = 1 - (f_x * f_x);
}

void derivativeTanHyperbolicActivated(IN float *input,
                                      OUT float *output) {
    output[0] = 1 - (input[0] * input[0]);
}

void activateReLU(IN float *input,
                  OUT float *output) {
    if (input[0] < 0) {
        output[0] = 0.f;
    } else {
        output[0] = input[0];
    }
}

void derivativeReLU(IN float *input,
                    OUT float *output) {
    if (input[0] < 0) {
        output[0] = 0.f;
    } else {
        output[0] = 1.f;
    }
}

void activateSoftSign(IN float *input,
                      OUT float *output) {
    output[0] = input[0] / (1.f + ABS(input[0]));
}

void derivativeSoftSign(IN float *input,
                        OUT float *output) {
    float den = (1.f + ABS(input[0]));
    output[0] = 1.f / (den * den);
}

void activateLogistic(IN float *input,
                      OUT float *output) {
    output[0] = 1 / (1.f + (float)(exp((double)(-input[0]))));
}

void derivativeLogistic(IN float *input,
                        OUT float *output) {
    float f_x = 1 / (1.f + (float)(exp((double)(-input[0]))));
    output[0] = f_x * (1  - f_x);
}

void activateLinear(IN float *input,
                    OUT float *output) {
    output[0] = input[0];
}

void derivativeLinear(IN float *input,
                      OUT float *output) {
    output[0] = 1;
}


/************************************/
/********  SEQUENTIAL FUNC **********/
/************************************/

mlp_net* create_mlp(int size, int input_size, int *sizes, float learning_rate,
                    activate activation_hidden,
                    activate activation_output,
                    derivative derivative_hidden,
                    derivative derivative_output) {
    mlp_net *network = malloc(sizeof(mlp_net));
    if (network) {
        // Set general parameters
        network->size = size;
        network->input_size = input_size;
        network->output_size = sizes[size - 1];
        network->learning_rate = learning_rate;
        network->activation_hidden = activation_hidden;
        network->activation_output = activation_output;
        network->derivative_hidden = derivative_hidden;
        network->derivative_output = derivative_output;
        network->weight_optimizer.beta1 = 0.9;
        network->weight_optimizer.beta2 = 0.999;
        network->weight_optimizer.beta1_pow = network->weight_optimizer.beta1;
        network->weight_optimizer.beta2_pow = network->weight_optimizer.beta2;
        network->weight_optimizer.epsilon = 1e-8;
        network->bias_optimizer.beta1 = 0.9;
        network->bias_optimizer.beta2 = 0.999;
        network->bias_optimizer.beta1_pow = network->bias_optimizer.beta1;
        network->bias_optimizer.beta2_pow = network->bias_optimizer.beta2;
        network->bias_optimizer.epsilon = 1e-8;

        // Allocate the needed memories
        network->weights = malloc(size * sizeof(float*));
        network->bias = malloc(size * sizeof(float*));
        network->inputs_layer = malloc(size * sizeof(float*));
        network->output = malloc(network->output_size * sizeof(float));
        network->errors = malloc(size * sizeof(float*));
        network->gradients = malloc(size * sizeof(float*));
        network->weight_optimizer.fst_order_moments = malloc(size * sizeof(double*));
        network->weight_optimizer.sec_order_moments = malloc(size * sizeof(double*));
        network->bias_optimizer.fst_order_moments = malloc(size * sizeof(double*));
        network->bias_optimizer.sec_order_moments = malloc(size * sizeof(double*));
        network->layer_size = malloc(size * sizeof(int));

        // Initializes network's layers.
        int layer_input_size = input_size;
        if (network->weights &&
            network->bias &&
            network->inputs_layer &&
            network->errors &&
            network->gradients &&
            network->output &&
            network->layer_size) {
            // Copy layer sizes
            memcpy(network->layer_size, sizes, size * sizeof(int));

            for (int i = 0; i < size; ++i) {
                int weights_size = sizes[i] * layer_input_size;

                // Allocate vectors
                network->bias[i] = malloc(sizes[i] * sizeof(float));
                network->errors[i] = malloc(sizes[i] * sizeof(float));
                network->inputs_layer[i] = malloc(layer_input_size * sizeof(float));
                network->weights[i] = malloc(weights_size* sizeof(float));
                network->gradients[i] = malloc(weights_size* sizeof(float));
                network->weight_optimizer.fst_order_moments[i] = malloc(weights_size * sizeof(double));
                network->weight_optimizer.sec_order_moments[i] = malloc(weights_size * sizeof(double));
                network->bias_optimizer.fst_order_moments[i] = malloc(sizes[i] * sizeof(double));
                network->bias_optimizer.sec_order_moments[i] = malloc(sizes[i] * sizeof(double));

                // Initializes weights and bias vector
                randomVectorInitializer(weights_size, 0.f, (float)rand() / (float)(RAND_MAX), network->weights[i]);
                constantVectorInitializer(sizes[i], 0.f, network->bias[i]);
                constantVectorInitializer(sizes[i], 0.f, network->errors[i]);
                constantVectorInitializer(weights_size, 0.f, network->gradients[i]);
                constantVectorInitializerDBL(weights_size, 0., network->weight_optimizer.fst_order_moments[i]);
                constantVectorInitializerDBL(weights_size, 0., network->weight_optimizer.sec_order_moments[i]);
                constantVectorInitializerDBL(sizes[i], 0., network->bias_optimizer.fst_order_moments[i]);
                constantVectorInitializerDBL(sizes[i], 0., network->bias_optimizer.sec_order_moments[i]);

                layer_input_size = sizes[i];
            }
        } else {
            free_mlp(&network);
            return NULL;
        }
    }
    return network;
}

void run_mlp(mlp_net* network, float *input, float *output) {
    int input_size = network->input_size;
    int valid = 1;
    // fetch input vector
    memcpy(network->inputs_layer[0], input, network->input_size * sizeof(float));
    // hidden layers
    for (int n = 0; n < network->size - 1; ++n) {
        layer(input_size, network->layer_size[n], network->weights[n], network->bias[n], network->inputs_layer[n], &valid,
              network->inputs_layer[n + 1]);
        for (int i = 0; i < network->layer_size[n]; ++i) {
            network->activation_hidden(&network->inputs_layer[n + 1][i], &network->inputs_layer[n + 1][i]);
        }
        input_size = network->layer_size[n];
    }
    // output layer
    int n = network->size - 1;
    layer(input_size, network->layer_size[n], network->weights[n], network->bias[n], network->inputs_layer[n], &valid,
          network->output);
    for (int i = 0; i < network->layer_size[n]; ++i) {
        network->activation_output(&network->output[i], &network->output[i]);
    }
    memcpy(output, network->output, network->output_size * sizeof(float));
}

void print_mlp_full(mlp_net *network, char *name) {
    int input_size = network->input_size;
    fprintf(stderr, "Printing NETWORK\n");
    fprintf(stderr, "================\n");
    fprintf(stderr, "%s\n", name);
    for (int n = 0; n < network->size; ++n) {
        fprintf(stderr, "Layer: %d\n", n);
        for (int j = 0; j < network->layer_size[n]; ++j) {
            for (int i = 0; i < input_size; ++i) {
                fprintf(stderr, "weights for input[%d] to neuron[%d]: %f\n", i, j, network->weights[n][j * input_size + i]);
            }
            fprintf(stderr, "bias for neuron[%d]: %f\n", j, network->bias[n][j]);
        }
        input_size = network->layer_size[n];
    }
}

void free_mlp(mlp_net **network) {
    if (*network) {
        free_vector((*network)->bias, (*network)->size);
        free_vector((*network)->weights, (*network)->size);
        free_vector((*network)->inputs_layer, (*network)->size);
        free_vector((*network)->errors, (*network)->size);
        free_vector((*network)->gradients, (*network)->size);
        free_vector((*network)->weight_optimizer.fst_order_moments, (*network)->size);
        free_vector((*network)->weight_optimizer.sec_order_moments, (*network)->size);
        free_vector((*network)->bias_optimizer.fst_order_moments, (*network)->size);
        free_vector((*network)->bias_optimizer.sec_order_moments, (*network)->size);
        if ((*network)->layer_size) {
            free((*network)->layer_size);
            (*network)->layer_size = NULL;
        }
        if ((*network)->output) {
            free((*network)->output);
            (*network)->output = NULL;
        }
        free(*network);
        *network = NULL;
    }
}

void compute_gradient(mlp_net* network, float *target) {
    // Compute first the output layer errors
    for (int k = 0; k < network->output_size; ++k) {
        float derivative = 0.f;
        network->derivative_output(&network->output[k], &derivative);
        network->errors[network->size - 1][k] = 2.f * (network->output[k] - target[k]) * derivative;
    }

    //  Compute error for other layers
    for (int n = network->size - 2; n >= 0; --n) {
        int layer_size = network->layer_size[n];
        for (int j = 0; j < layer_size; ++j) {
            // Compute the backpropagated error
            float prop = 0.f;
            for (int k = 0; k < network->layer_size[n + 1]; ++k) {
                prop += network->errors[n + 1][k] * network->weights[n + 1][j + k * layer_size];
            }
            float derivative = 0.f;
            network->derivative_hidden(&network->inputs_layer[n + 1][j], &derivative);
            network->errors[n][j] = prop * derivative;
        }
    }

    // Compute gradients
    int input_size = network->input_size;
    for (int n = 0; n < network->size; ++n) {
        int layer_size = network->layer_size[n];
        for (int j = 0; j < layer_size; ++j) {
            int offset = j * input_size;
            // Feedforward to compute the gradient
            for (int i = 0; i < input_size; ++i) {
                network->gradients[n][offset + i] = network->errors[n][j] * network->inputs_layer[n][i];
            }
        }
        input_size = layer_size;
    }
}

void apply_gradient(mlp_net* network) {
    int input_size = network->input_size;
    for (int n = 0; n < network->size; ++n) {
        int layer_size = network->layer_size[n];
        // Apply Adam optimizer
        double lr = network->learning_rate * sqrt(1 - network->bias_optimizer.beta2_pow) / (1. - network->bias_optimizer.beta1_pow);
        double bias_epsilon_t = sqrt(1 - network->bias_optimizer.beta2_pow) * network->bias_optimizer.epsilon;
        double weights_epsilon_t = sqrt(1 - network->weight_optimizer.beta2_pow) * network->weight_optimizer.epsilon;
        for (int j = 0; j < layer_size; ++j) {
            // bias gradient is equal to backpropagated error
            double grad = network->errors[n][j];
            network->bias_optimizer.fst_order_moments[n][j] = network->bias_optimizer.fst_order_moments[n][j] *
                                                              network->bias_optimizer.beta1 + (1. - network->bias_optimizer.beta1) * grad;
            network->bias_optimizer.sec_order_moments[n][j] = network->bias_optimizer.sec_order_moments[n][j] *
                                                              network->bias_optimizer.beta2 + (1. - network->bias_optimizer.beta2) * grad * grad;
            network->bias[n][j] -= (lr * network->bias_optimizer.fst_order_moments[n][j] /
                    (bias_epsilon_t + sqrt(network->bias_optimizer.sec_order_moments[n][j])));

            int offset = j * input_size;
            for (int i = 0; i < input_size; ++i) {
                grad = network->gradients[n][offset + i];
                network->weight_optimizer.fst_order_moments[n][offset + i] = network->weight_optimizer.fst_order_moments[n][offset + i] *
                        network->weight_optimizer.beta1 + (1. - network->weight_optimizer.beta1) * grad;
                network->weight_optimizer.sec_order_moments[n][offset + i] = network->weight_optimizer.sec_order_moments[n][offset + i] *
                                                                      network->weight_optimizer.beta2 + (1. - network->weight_optimizer.beta2) * grad * grad;
                network->weights[n][offset + i] -= (lr * network->weight_optimizer.fst_order_moments[n][offset + i] /
                                        (weights_epsilon_t + sqrt(network->weight_optimizer.sec_order_moments[n][offset + i])));
            }
        }
        input_size = layer_size;
    }
    network->weight_optimizer.beta1_pow *= network->weight_optimizer.beta1;
    network->weight_optimizer.beta2_pow *= network->weight_optimizer.beta2;
    network->bias_optimizer.beta1_pow *= network->bias_optimizer.beta1;
    network->bias_optimizer.beta2_pow *= network->bias_optimizer.beta2;
}

void update_mlp(mlp_net* network, float *target) {
    // Compute the gradients
    compute_gradient(network, target);

    // Apply the gradients
    apply_gradient(network);
}

void print_gradients(mlp_net* network) {
    int input_size = network->input_size;
    fprintf(stderr, "Printing GRADIENTS\n");
    fprintf(stderr, "================\n");
    for (int n = 0; n < network->size; ++n) {
        fprintf(stderr, "Layer: %d\n", n);
        for (int j = 0; j < network->layer_size[n]; ++j) {
            for (int i = 0; i < input_size; ++i) {
                fprintf(stderr, "gradient of weight for input[%d] to neuron[%d]: %f\n", i, j, network->gradients[n][j * input_size + i]);
            }
            fprintf(stderr, "gradient of bias for neuron[%d]: %f\n", j, network->errors[n][j]);
        }
        input_size = network->layer_size[n];
    }
}

void save_mlp(mlp_net *network) {
    int *size_weights = malloc(network->size * sizeof(int));
    if (size_weights) {
        fprintf(stderr, "saving network..\n");
        int input_size = network->input_size;
        for (int i = 0; i < network->size; ++i) {
            size_weights[i] = network->layer_size[i] * input_size;
            input_size = network->layer_size[i];
        }
        saveNetWork(network->size, size_weights, network->layer_size, network->weights, network->bias);
        free(size_weights);
        fprintf(stderr, "network saved.\n");
    }
}

