/**
 * @file main.c
 * @generated by CPrinter
 * @date Fri Dec 01 14:45:14 CET 2017
 *  
 */


#include <zconf.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <clock.h>
#include <stdlib.h>
#include <render.h>
#include <mlp.h>
#include <environment.h>
#include <actor_mlp.h>
#include <common.h>
#include <stdio.h>
#include <critic_mlp.h>
#include <memory.h>
#include <string.h>

#define CACLA_train
int preesmStopThreads = 0;

#if  defined(LEARN_SIN)

#define INPUT 2
#define SIZE 3

#define getRand() -M_PI + 2.f * M_PI * (float)(rand()) / (float)(RAND_MAX)

int main(void) {
    srand((unsigned int)time(NULL));
    int mlp_sizes[SIZE] = {5, 40, INPUT};
    mlp_net *network = create_mlp(SIZE, INPUT, mlp_sizes, 0.00005f,
                                  activateTanHyperbolic,
                                  activateLinear,
                                  derivativeTanHyperbolicActivated,
                                  derivativeLinear);

    if (network) {
        //print_mlp(network);
        float inputs[INPUT];
        float targets[INPUT];
        float predictions[INPUT];
        double error = 0;
        long long int i = 0;
        double epsilon = 1e-3;
        double mean_error = 0;
        do {
            // get inputs
            inputs[0] = getRand();
            inputs[1] = getRand();
            // get targets
            targets[0] = (float)(sin((double)(inputs[0])));
            targets[1] = (float)(cos((double)(inputs[1])));

            run_mlp(network, inputs, predictions);

            update_mlp(network, targets);
            lossMSE(INPUT, targets, predictions, &error);
            mean_error = 0.99 * mean_error + 0.01 * error;
            ++i;
        } while(mean_error > epsilon);
        fprintf(stderr, "targets: %f pred: %f error: %lf.\n", targets[0], predictions[0], error);
        fprintf(stderr, "training done in %lld iterations.\n", i);
        fprintf(stderr, "testing...\n");
        double mean_mse = 0.f;
        int iter = 50;
        for (int i = 0; i < iter; ++i) {
            // get inputs
            inputs[0] = getRand();
            inputs[1] = getRand();
            // get targets
            targets[0] = (float)(sin((double)(inputs[0])));
            targets[1] = (float)(cos((double)(inputs[1])));
            run_mlp(network, inputs, predictions);
            fprintf(stderr, "%f\t%f\t%f\t%f\t\n", targets[0], predictions[0], targets[1], predictions[1]);
            lossMSE(INPUT, targets, predictions, &error);
            mean_mse += error;
        }

        fprintf(stderr, "mean mse: %lf\n", mean_mse / (double)(iter));
        //print_mlp(network);
        free_mlp(&network);
    }
    return 0;
}

#elif defined(MLP_cmp)
#define getRand() -M_PI + 2.f * M_PI * (float)(rand()) / (float)(RAND_MAX)

#define SIZE_HIDDEN 20
#define SIZE_HIDDEN2 5
#define SIZE_OUTPUT 2
int main(void) {
    srand((unsigned int)time(NULL));
    int mlp_sizes[3] = {SIZE_HIDDEN, SIZE_HIDDEN2, SIZE_OUTPUT};
    mlp_net *network = create_mlp(3, 2, mlp_sizes, 0.00005f,
                                  activateTanHyperbolic,
                                  activateLinear,
                                  derivativeTanHyperbolicActivated,
                                  derivativeLinear);
    mlp_net *network_dataflow = create_mlp(3, 2, mlp_sizes, 0.00005f,
                                  activateTanHyperbolic,
                                  activateLinear,
                                  derivativeTanHyperbolicActivated,
                                  derivativeLinear);

    memcpy(network_dataflow->weights[0], network->weights[0], 2 * SIZE_HIDDEN * sizeof(float));
    memcpy(network_dataflow->weights[1], network->weights[1], SIZE_HIDDEN * SIZE_HIDDEN2 * sizeof(float));
    memcpy(network_dataflow->weights[2], network->weights[2], SIZE_HIDDEN2 * SIZE_OUTPUT * sizeof(float));
    memcpy(network_dataflow->bias[0], network->bias[0], SIZE_HIDDEN * sizeof(float));
    memcpy(network_dataflow->bias[1], network->bias[1], SIZE_HIDDEN2 * sizeof(float));
    memcpy(network_dataflow->bias[2], network->bias[2], SIZE_OUTPUT * sizeof(float));


    if (network &&
        network_dataflow) {
        //print_mlp(network);
        float inputs[2];
        float targets[SIZE_OUTPUT];
        float predictions[SIZE_OUTPUT];
        float predictions_bis[SIZE_OUTPUT];
        double error = 0.f;
        double mse = 0.;

        // Dataflow intermediate buffers
        int valid = 1;
        float output_hidden_raw[SIZE_HIDDEN];
        float output_hidden[SIZE_HIDDEN];
        float output_hidden_derivative[SIZE_HIDDEN];
        float error_hidden[SIZE_HIDDEN];
        float output_hidden2_raw[SIZE_HIDDEN2];
        float output_hidden2[SIZE_HIDDEN2];
        float output_hidden2_derivative[SIZE_HIDDEN2];
        float error_hidden2[SIZE_HIDDEN2];
        float output_raw[SIZE_OUTPUT];
        float output_derivative[SIZE_OUTPUT];
        float output[SIZE_OUTPUT];
        float error_output[SIZE_OUTPUT];

        double betas[4];
        double epsilon = 1e-8;
        initAdam(betas);

        for (long int i = 0; i < 10000; ++i) {
            // get inputs
            inputs[0] = getRand();
            inputs[1] = getRand();
            // get targets
            targets[0] = (float)(sin((double)(inputs[0])));
            targets[1] = (float)(cos((double)(inputs[1])));

            // Sequential version
            run_mlp(network, inputs, predictions);

            // Dataflow version
            run_mlp(network_dataflow, inputs, predictions_bis);

            for (int n = 0; n < 10; ++n) {
                update_mlp(network, targets);
                run_mlp(network, inputs, predictions);
            }

            // Generate the input of output layer
            // Compute hidden layer feedforward + derivative
            for (int n = 0; n < 10; ++n) {
                layer(2, SIZE_HIDDEN, network_dataflow->weights[0], network_dataflow->bias[0], inputs, &valid,
                      output_hidden_raw);
                for (int j = 0; j < SIZE_HIDDEN; ++j) {
                    activateTanHyperbolic(&output_hidden_raw[j], &output_hidden[j]);
                    derivativeTanHyperbolic(&output_hidden_raw[j], &output_hidden_derivative[j]);
                }
                layer(SIZE_HIDDEN, SIZE_HIDDEN2, network_dataflow->weights[1], network_dataflow->bias[1], output_hidden,
                      &valid, output_hidden2_raw);
                for (int j = 0; j < SIZE_HIDDEN2; ++j) {
                    activateTanHyperbolic(&output_hidden2_raw[j], &output_hidden2[j]);
                    derivativeTanHyperbolic(&output_hidden2_raw[j], &output_hidden2_derivative[j]);
                }
                // Compute output layer feedforward + derivative
                layer(SIZE_HIDDEN2, SIZE_OUTPUT, network_dataflow->weights[2], network_dataflow->bias[2],
                      output_hidden2, &valid, output_raw);
                for (int j = 0; j < SIZE_OUTPUT; ++j) {
                    activateLinear(&output_raw[j], &output[j]);
                    derivativeLinear(&output_raw[j], &output_derivative[j]);
                }

                // Compute sigma and gradients for output layer
                computeOutputError(SIZE_OUTPUT, output_derivative, output, targets, &valid, error_output);
                computeWeightsGradients(SIZE_HIDDEN2, SIZE_OUTPUT, error_output, output_hidden2, &valid,
                                        network_dataflow->gradients[2]);

                // Compute sigma and gradients for hidden layer 2
                computeLayerBackPropError(SIZE_HIDDEN2, SIZE_OUTPUT, output_hidden2_derivative, error_output,
                                          network_dataflow->weights[2], &valid, error_hidden2);
                computeWeightsGradients(SIZE_HIDDEN, SIZE_HIDDEN2, error_hidden2, output_hidden, &valid,
                                        network_dataflow->gradients[1]);

                // Compute sigma and gradients for hidden layer
                computeLayerBackPropError(SIZE_HIDDEN, SIZE_HIDDEN2, output_hidden_derivative, error_hidden2,
                                          network_dataflow->weights[1], &valid, error_hidden);
                computeWeightsGradients(2, SIZE_HIDDEN, error_hidden, inputs, &valid, network_dataflow->gradients[0]);

                // Apply adam optimizer for output
                applyAdamOptimizer(SIZE_HIDDEN2 * SIZE_OUTPUT, &valid, &network_dataflow->learning_rate, betas,
                                   &epsilon,
                                   network_dataflow->weights[2],
                                   network_dataflow->weight_optimizer.fst_order_moments[2],
                                   network_dataflow->weight_optimizer.sec_order_moments[2],
                                   network_dataflow->gradients[2],
                                   network_dataflow->weights[2],
                                   network_dataflow->weight_optimizer.fst_order_moments[2],
                                   network_dataflow->weight_optimizer.sec_order_moments[2]);
                applyAdamOptimizer(SIZE_OUTPUT, &valid, &network_dataflow->learning_rate, betas, &epsilon,
                                   network_dataflow->bias[2],
                                   network_dataflow->bias_optimizer.fst_order_moments[2],
                                   network_dataflow->bias_optimizer.sec_order_moments[2],
                                   error_output,
                                   network_dataflow->bias[2],
                                   network_dataflow->bias_optimizer.fst_order_moments[2],
                                   network_dataflow->bias_optimizer.sec_order_moments[2]);

                // Apply adam optimizer for hidden 2
                applyAdamOptimizer(SIZE_HIDDEN * SIZE_HIDDEN2, &valid, &network_dataflow->learning_rate, betas,
                                   &epsilon,
                                   network_dataflow->weights[1],
                                   network_dataflow->weight_optimizer.fst_order_moments[1],
                                   network_dataflow->weight_optimizer.sec_order_moments[1],
                                   network_dataflow->gradients[1],
                                   network_dataflow->weights[1],
                                   network_dataflow->weight_optimizer.fst_order_moments[1],
                                   network_dataflow->weight_optimizer.sec_order_moments[1]);
                applyAdamOptimizer(SIZE_HIDDEN2, &valid, &network_dataflow->learning_rate, betas, &epsilon,
                                   network_dataflow->bias[1],
                                   network_dataflow->bias_optimizer.fst_order_moments[1],
                                   network_dataflow->bias_optimizer.sec_order_moments[1],
                                   error_hidden2,
                                   network_dataflow->bias[1],
                                   network_dataflow->bias_optimizer.fst_order_moments[1],
                                   network_dataflow->bias_optimizer.sec_order_moments[1]);

                // Apply adam optimizer for hidden
                applyAdamOptimizer(2 * SIZE_HIDDEN, &valid, &network_dataflow->learning_rate, betas, &epsilon,
                                   network_dataflow->weights[0],
                                   network_dataflow->weight_optimizer.fst_order_moments[0],
                                   network_dataflow->weight_optimizer.sec_order_moments[0],
                                   network_dataflow->gradients[0],
                                   network_dataflow->weights[0],
                                   network_dataflow->weight_optimizer.fst_order_moments[0],
                                   network_dataflow->weight_optimizer.sec_order_moments[0]);
                applyAdamOptimizer(SIZE_HIDDEN, &valid, &network_dataflow->learning_rate, betas, &epsilon,
                                   network_dataflow->bias[0],
                                   network_dataflow->bias_optimizer.fst_order_moments[0],
                                   network_dataflow->bias_optimizer.sec_order_moments[0],
                                   error_hidden,
                                   network_dataflow->bias[0],
                                   network_dataflow->bias_optimizer.fst_order_moments[0],
                                   network_dataflow->bias_optimizer.sec_order_moments[0]);

                adamUpdateBetas(betas, &valid, betas);

            }

            lossMSE(2, predictions, output, &error);
            mse += error;
        }
        fprintf(stderr, "total mse: %lf\n", mse);
    }
    free_mlp(&network);
    free_mlp(&network_dataflow);
    return 0;
}

#elif defined(CACLA_train)

int main(void) {
    srand((unsigned int)time(NULL));
    // Init render
    renderInit();

    //Creates both mlps
    int sizes_critic[4] = {10, 20, 10, 1};
    int sizes_actor[3] = {20, 10, 1};
    float actor_learning_rate = 0.001f;
    float critic_learning_rate = 0.0005f;
    mlp_net *actor_mlp = create_mlp(3, 3, sizes_actor, actor_learning_rate,
                                    activateTanHyperbolic,
                                    activateLinear,
                                    derivativeTanHyperbolicActivated,
                                    derivativeLinear);
    mlp_net *critic_mlp = create_mlp(4, 3, sizes_critic, critic_learning_rate,
                                     activateTanHyperbolic,
                                     activateLinear,
                                     derivativeTanHyperbolicActivated,
                                     derivativeLinear);
    startTiming(50);

    // Environment related variable
    float action = 0.f;
    float angular_state[2] = {0.f};
    float obs_state[3] = {0.f};
    float obs_state_next[3] = {0.f};
    float reward = 0.f;
    // Init state
    envInit(angular_state, obs_state);
    float variance = 1.f;
    float beta = 0.0001f;
    float sigma = 2.f;
    long int i = 0;
    float limits[2] = {-MAX_TORQUE, MAX_TORQUE};
    while(!preesmStopThreads) {
        // pred action
        run_mlp(actor_mlp, obs_state, &action);
        float action_sampled = action;
        actionSampler(1, &sigma, &action, &action_sampled);
        clipValues(1, &action_sampled, limits, &action_sampled);

        // apply action
        step(3, 1, 2, angular_state, angular_state, &action_sampled, obs_state_next, &reward);

        if (action_sampled > MAX_TORQUE) {
            char stringTime[20];
            int timeStamp = stopTiming(50);
            double secs = (timeStamp / 1000000.);
            sprintf(stringTime, "%.2f secs", secs);
            save_mlp(actor_mlp);
            fprintf(stderr, "Training finished in %s\n", stringTime);
            break;
        }

        // compute td-error
        float value = 0.f;
        float value_next = 0.f;
        run_mlp(critic_mlp, obs_state_next, &value_next);
        run_mlp(critic_mlp, obs_state, &value);
        float target;
        target = reward + DISCOUNT_FACTOR * value_next;
        float delta = target - value;

        // update critic network
        update_mlp(critic_mlp, &delta);

        if (delta > 0.f) {
            int n = (int)ceil((delta / sqrt(variance)));
            for (int i = 0; i < n; ++i) {
                update_mlp(actor_mlp, &action_sampled);
                run_mlp(actor_mlp, obs_state, &action);
            }
        }

        // render display
        renderEnv(2, angular_state);

        variance = variance * (1 - beta) + beta * delta * delta;

        // update state
        memcpy(obs_state, obs_state_next, 3 * sizeof(float));

        // sigma decay
        //sigma = sigma - sigma_reset / sigma_decay_period;
//        if (i >= 100000) {
//            //sigma = sigma_reset;
//            envInit(angular_state, obs_state);
//            actor_mlp->bias_optimizer.beta1_pow = actor_mlp->bias_optimizer.beta1;
//            actor_mlp->bias_optimizer.beta2_pow = actor_mlp->bias_optimizer.beta2;
//            actor_mlp->weight_optimizer.beta1_pow = actor_mlp->weight_optimizer.beta1;
//            actor_mlp->weight_optimizer.beta2_pow = actor_mlp->weight_optimizer.beta2;
//            critic_mlp->bias_optimizer.beta1_pow = critic_mlp->bias_optimizer.beta1;
//            critic_mlp->bias_optimizer.beta2_pow = critic_mlp->bias_optimizer.beta2;
//            critic_mlp->weight_optimizer.beta1_pow = critic_mlp->weight_optimizer.beta1;
//            critic_mlp->weight_optimizer.beta2_pow = critic_mlp->weight_optimizer.beta2;
//            i = 0;
//        }
        ++i;
    }



    // Free MLP
    free_mlp(&actor_mlp);
    free_mlp(&critic_mlp);

    // Exit render
    renderFinalize();

    exit(0);
}

#elif defined(CACLA_run)
int main(void) {
    srand((unsigned int)time(NULL));
    // Init render
    renderInit();

    //Creates both mlps
    int sizes_actor[2] = {20, 1};
    mlp_net *actor_mlp = create_mlp(2, 3, sizes_actor, 0.0001f,
                                    activateTanHyperbolic,
                                    activateLinear,
                                    derivativeTanHyperbolicActivated,
                                    derivativeLinear);

    actorWeightGenInit(0, actor_mlp->weights[0], actor_mlp->bias[0]);
    actorWeightGenInit(1, actor_mlp->weights[1], actor_mlp->bias[1]);
    startTiming(50);

    // Environment related variable
    float action = 0.f;
    float angular_state[2] = {0.f};
    float obs_state[3] = {0.f};
    float obs_state_next[3] = {0.f};
    float reward = 0.f;
    // Init state
    envInit(angular_state, obs_state);
    long int i = 0;
    float limits[2] = {-MAX_TORQUE, MAX_TORQUE};
    while(!preesmStopThreads) {
        // pred action
        run_mlp(actor_mlp, obs_state, &action);
        float action_sampled = action;
        clipValues(1, &action_sampled, limits, &action_sampled);

        // apply action
        step(3, 1, 2, angular_state, angular_state, &action_sampled, obs_state_next, &reward);

        if (action_sampled > MAX_TORQUE) {
            char stringTime[20];
            int timeStamp = stopTiming(50);
            double secs = (timeStamp / 1000000.);
            sprintf(stringTime, "%.2f secs", secs);
            save_mlp(actor_mlp);
            fprintf(stderr, "Training finished in %s\n", stringTime);
            break;
        }

        // render display
        renderEnv(2, angular_state);

        // update state
        memcpy(obs_state, obs_state_next, 3 * sizeof(float));

        // fps management
//        usleep(50000);
    }



    // Free MLP
    free_mlp(&actor_mlp);

    // Exit render
    renderFinalize();

}
#elif defined(BENCH)

void bench(void) {
    int sizes[3] = {20, 20, 1};
    mlp_net *network = create_mlp(3, 3, sizes, 0.01f,
                                  activateTanHyperbolic,
                                  activateLinear,
                                  derivativeTanHyperbolicActivated,
                                  derivativeLinear);

    actorWeightGenInit(0, network->weights[0], network->bias[0]);
    actorWeightGenInit(1, network->weights[1], network->bias[1]);
    actorWeightGenInit(2, network->weights[2], network->bias[2]);

    double iterations = 10000.;
    fprintf(stderr, "Bench configuration:\n");
    fprintf(stderr, "==> Sigma:         %f\n", SIGMA_GAUSSIAN);
    fprintf(stderr, "==> Learning rate: %f\n", network->learning_rate);
    fprintf(stderr, "==> Beta 1:        %e\n", network->weight_optimizer.beta1);
    fprintf(stderr, "==> Beta 2:        %e\n", network->weight_optimizer.beta2);
    fprintf(stderr, "==> Beta 1 pow:    %e\n", network->weight_optimizer.beta1_pow);
    fprintf(stderr, "==> Beta 2 pow:    %e\n", network->weight_optimizer.beta2_pow);
    fprintf(stderr, "==> Epsilon:       %e\n", network->weight_optimizer.epsilon);
    fprintf(stderr, "==> Iterations:    %d\n", (int)iterations);
    fprintf(stderr, "The benchmark uses fixed sinus values for learning.\n"
                  "Values of sinus used are evenly spaced (1 / iterations) in [0, 1]\n");
    double delta = 1. / iterations;
    print_mlp(network);
    for (int i = 0; i < (int)iterations; ++i){
        double x = (double)(i) * delta;
        float target = (float)sin(x);
        float state[3] = {x, x, x};
        float pred;
        run_mlp(network, state, &pred);
        fprintf(stderr, "target: %f\n", target);
        fprintf(stderr, "value: %f\n", pred);
        compute_gradient(network, &target);
        apply_gradient(network);
    }
    print_mlp(network);
    fprintf(stderr, "==> Beta 1 pow:    %e\n", network->weight_optimizer.beta1_pow);
    fprintf(stderr, "==> Beta 2 pow:    %e\n", network->weight_optimizer.beta2_pow);
}

int main(void) {
    bench();
    return 0;
}

#endif
