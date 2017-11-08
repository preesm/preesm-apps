//
// Created by farresti on 03/11/17.
//

#include "../include/critic_mlp.h"


void td_error(IN float gamma, IN float reward, IN float value_state, IN float value_next_state,
              OUT float *target, OUT float *sigma) {
    (*target) = reward + gamma * value_next_state;
    (*sigma) = (*target) - value_state;
}