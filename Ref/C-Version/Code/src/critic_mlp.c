//
// Created by farresti on 03/11/17.
//
// std libs
#include <stdio.h>
// file header
#include "../include/critic_mlp.h"


void td_error(IN float *gamma_in,IN float *reward, IN float *value_state, IN float *value_next_state,
              OUT float *target, OUT float *sigma) {
    (*target) = reward[0] + gamma_in[0] * value_next_state[0];
    (*sigma) = (*target) - value_state[0];
//    fprintf(stderr, "reward: %f value: %f value_next: %f sigma: %f\n", reward[0], value_state[0], value_next_state[0], *sigma);
}

void validCritic(OUT int *valid) {
    valid[0] = 1;
}

void gammaGen(OUT float *gamma) {
    gamma[0] = DISCOUNT_FACTOR;
}

void criticLearningRateGen(OUT float *learning_rate) {
    learning_rate[0] = CRITIC_LEARNING_RATE;
}