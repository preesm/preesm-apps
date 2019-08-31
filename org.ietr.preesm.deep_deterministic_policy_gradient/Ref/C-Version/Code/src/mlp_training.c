//
// Created by farresti on 23/11/17.
//
// math lib
#include <math.h>
// std libs
#include <string.h>
#include <stdio.h>
// file header
#include "../include/mlp_training.h"
#include "../include/common.h"


void computeLayerBackPropError(int layer_size, int next_layer_size,
                       IN float *derivative_values, IN float *next_layer_sigmas, IN float *next_layer_weights, IN int *valid,
                       OUT float *layer_sigmas) {
    if (*valid == 0) {
        return;
    } else {
        for (int j = 0; j < layer_size; ++j) {
            float sum_next_layer = 0.f;
            for (int k = 0; k < next_layer_size; ++k) {
                /* The weights are arranged in following order:
                 *     l = layer_size
                 *     n = l - 1
                 *     ln = next_layer_size
                 *     k = ln - 1
                 *
                 *     weight[0]          -> weight from node[0] of layer (l) to node[0] of layer (l + 1)
                 *     weight[1]          -> weight from node[1] of layer (l) to node[0] of layer (l + 1)
                 *     ...
                 *     weight[n]          -> weight from node[n] of layer (l) to node[0] of layer (l + 1)
                 *     weight[n + 1]      -> weight from node[0] of layer (l) to node[1] of layer (l + 1)
                 *     ...
                 *     weight[l * ln - 1] -> weight from node[n] of layer (l) to node[k] of layer (l + 1)
                 *
                 */
                sum_next_layer += next_layer_sigmas[k] * next_layer_weights[j + k * layer_size];
            }
            layer_sigmas[j] = derivative_values[j] * sum_next_layer;
        }
    }
}

void computeOutputError(int output_size,
                        IN float *derivative_values, IN float *predicted, IN float *target, IN int *valid,
                        OUT float *output_sigmas) {
    if (*valid == 0) {
        return;
    }
    for (int j = 0; j < output_size; ++j) {
        output_sigmas[j] = 2.f * (predicted[j] - target[j]) *derivative_values[j];
    }
}


void lossMSE(int size,
             IN float *targets, IN float *predictions,
             OUT double *mse_output) {
    // Compute element wise (label - prediction) * (label - prediction)
    double mse = 0;
    for (int i = 0; i < size; ++i) {
        mse += (double)(predictions[i] - targets[i]) * (double)(predictions[i] - targets[i]);
    }
    mse_output[0] = mse / (double)(size);
}


void computeWeightsGradients(int input_size, int layer_size,
                             IN float *errors, IN float *inputs, IN int *valid,
                             OUT float *gradients) {
    if (*valid == 0) {
        return;
    }
    /* Gradients are computed as follows:
     *
     *     G(wij) = Sj * Ai
     *
     *     where:
     *        i      -> index of input to current layer (l)
     *        j      -> index of node in current layer (l)
     *        G(wij) -> gradients of weight i, j
     *        wij    -> weight connecting input i from layer (l - 1) to node j in layer (l)
     *        Sj     -> sigmas of node j (see computeLayerBackPropError for more on that)
     *        Ai     -> input i of layer (l)
     *
     *     The gradients are stored in the same way the weights are:
     *        gradients[0]     -> gradient of weight[0] (i.e weight connecting input[0] to node[0])
     *        gradients[1]     -> gradient of weight[1] (i.e weight connecting input[1] to node[0])
     *        ...
     *        gradients[n]     -> gradient of weight[n] (i.e weight connecting input[n] to node[0])
     *        gradients[n + 1] -> gradient of weight[n + 1] (i.e weight connecting input[0] to node[1])
     *        ...
     *        gradients[m]     -> gradient of weight[m] (i.e weight connecting input[n] to node[l])
     *
     */
    for (int j = 0; j < layer_size; ++j) {
        for (int i = 0; i < input_size; ++i) {
            gradients[i + j * input_size] = errors[j] * inputs[i];
        }
    }
}

void applyAdamOptimizer(int size,
                        IN int *valid, IN float *learning_rate, IN double *betas, IN double *epsilon,
                        IN float *param_in, IN double *fo_moment_in, IN double *so_moment_in, IN float *gradients,
                        OUT float *param_out, OUT double *fo_moment_out, OUT double *so_moment_out) {
    if (*valid == 0) {
        memcpy(param_out, param_in, size * sizeof(double));
        memcpy(fo_moment_out, fo_moment_in, size * sizeof(double));
        memcpy(so_moment_out, so_moment_in, size * sizeof(double));
    } else {
        double beta1 = betas[0];
        double beta2 = betas[1];
        double beta1_pow_t = betas[2];
        double beta2_pow_t = betas[3];
        double norm_beta2 = sqrt(1. - beta2_pow_t);
        double epsilon_t = epsilon[0] * norm_beta2;
        double lr = learning_rate[0] * norm_beta2 / (1. - beta1_pow_t); // Optimization, see original papers

        for (int i = 0; i < size; ++i) {
            // Updates moments
            double g = gradients[i];
            fo_moment_out[i] = fo_moment_in[i] * beta1 + (1 - beta1) * g;     // Biased first order moment estimate
            so_moment_out[i] = so_moment_in[i] * beta2 + (1 - beta2) * g * g; // Biased second raw order moment estimate

            param_out[i] = param_in[i] - (float)(lr * fo_moment_out[i] / (epsilon_t + sqrt(so_moment_out[i])));
        }
    }
}

void adamUpdateBetas(IN double *betas_in, IN int *valid,
                     OUT double *betas_out) {
    if (*valid == 0) {
        betas_out[0] = betas_in[0];
        betas_out[1] = betas_in[1];
        betas_out[2] = betas_in[2];
        betas_out[3] = betas_in[3];
    } else {
        // Update betas powered
        betas_out[0] = betas_in[0]; // Save B1
        betas_out[1] = betas_in[1]; // Save B2
        betas_out[2] = betas_in[2] * betas_in[0]; // Update B1^t
        betas_out[3] = betas_in[3] * betas_in[1]; // Update B2^t
    }
}


void initAdam(double *betas) {
    betas[0] = 0.9;
    betas[1] = 0.999;
    betas[2] = betas[0];
    betas[3] = betas[1];
}

