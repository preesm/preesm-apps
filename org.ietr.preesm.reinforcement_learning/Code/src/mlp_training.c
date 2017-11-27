//
// Created by farresti on 23/11/17.
//

#include <math.h>
#include "../include/mlp_training.h"


void computeLayerSigma(int layer_size, int next_layer_size,
                       IN float *derivative_values, IN float *next_layer_sigmas, IN float *next_layer_weights,
                       OUT float *layer_sigmas) {
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


void lossMSE(int size,
             IN float *labels, IN float *predictions,
             OUT float *mse_output) {
    // Compute element wise (label - prediction) * (label - prediction)
    float mse = 0.f;
    for (int i = 0; i < size; ++i) {
        mse += (labels[i] - predictions[i]) * (labels[i] - predictions[i]);
    }
    mse_output[0] = mse / (float)(size);
}


void computeLayerWeightsGradients(int input_size, int layer_size,
                                  IN float *sigmas, IN float *inputs,
                                  OUT float *gradients) {
    /* Gradients are computed as follows:
     *
     *     G(wij) = Sj * Ai
     *
     *     where:
     *        i      -> index of input to current layer (l)
     *        j      -> index of node in current layer (l)
     *        G(wij) -> gradients of weight i, j
     *        wij    -> weight connecting input i from layer (l - 1) to node j in layer (l)
     *        Sj     -> sigmas of node j (see computeLayerSigma for more on that)
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
            gradients[i + j * input_size] = sigmas[j] * inputs[i];
        }
    }
}


void applyAdamOptimizer(int size,
                        IN float *param_in, IN float *fo_moment_in, IN float *learning_rate,
                        IN float *so_moment_in, IN float *betas, IN float *gradients,
                        OUT float *param_out, OUT float *fo_moment_out, OUT float *so_moment_out, OUT float *betas_out) {
    float epsilon = 1e-8f;
    // Update betas powered
    betas_out[0] = betas[0]; // Save B1
    betas_out[1] = betas[1]; // Save B2
    betas_out[2] = betas[2] * betas[0]; // Update B1^t
    betas_out[3] = betas[3] * betas[1]; // Update B2^t

    float beta1 = betas_out[0];
    float beta2 = betas_out[1];
    float beta1_pow_t = betas_out[2];
    float beta2_pow_t = betas_out[3];

    for (int i = 0; i < size; ++i) {
        // Updates moments
        float g = gradients[i];
        fo_moment_out[i] = fo_moment_in[i] * beta1 + (1 - beta1) * g;     // Biased first order moment estimate
        so_moment_out[i] = so_moment_in[i] * beta2 + (1 - beta2) * g * g; // Biased second raw order moment estimate

        // Compute non biased moments
        float unbiased_fo_moment = fo_moment_out[i] / (1 - beta1_pow_t);
        double unbiased_so_moment = so_moment_out[i] / (1 - beta2_pow_t);

        param_out[i] = param_in[i] - (float)(learning_rate[0] * unbiased_fo_moment / (epsilon + sqrt(unbiased_so_moment)));
    }
}