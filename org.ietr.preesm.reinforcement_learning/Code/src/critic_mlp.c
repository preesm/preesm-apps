//
// Created by farresti on 03/11/17.
//

#include "../include/critic_mlp.h"


void td_error(IN float *gamma_in,IN float reward, IN float value_state, IN float value_next_state,
              OUT float *target, OUT float *sigma, OUT float *gamma_out) {
    (*gamma_out) = gamma_in[0];
    (*target) = reward + gamma_in[0] * value_next_state;
    (*sigma) = (*target) - value_state;
}