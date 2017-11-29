//
// Created by farresti on 03/11/17.
//

#ifndef CRITIC_MLP_H
#define CRITIC_MLP_H

#include "preesm.h"

#define GAMMA 0.99

void criticWeightGenInit(int id, OUT float *weights_out, OUT float *bias_out);

/**
 * @brief Compute the Temporal Difference Error used to update the critic neural network
 *
 * @param gamma_in
 * @param reward
 * @param value_state
 * @param value_next_state
 * @param target
 * @param sigma
 * @param gamma_out
 */
void td_error(IN float *gamma_in,IN float *reward, IN float *value_state, IN float *value_next_state,
              OUT float *target, OUT float *sigma);

void validCritic(OUT int *valid);

void gammaGen(OUT float *gamma);

#endif //CRITIC_MLP_H
