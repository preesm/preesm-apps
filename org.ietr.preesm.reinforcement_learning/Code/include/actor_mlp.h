#ifndef ACTOR_MLP_H__
#define ACTOR_MLP_H__

#include "preesm.h"

#define SIGMA_GAUSSIAN 0.1

void actorWeightGenInit(int id, OUT float *weights_out, OUT float *bias_out);


/**
 * @brief Samples a random action for each action in the action space
 *        based on a Normal distribution.
 *        Each distribution is parameterized by mu = action_in[i] and
 *        sigma = sigma_in
 *
 * @param size       Number of actions
 * @param sigma_in   Sigma used for the distribution
 * @param action_in  Vector of input actions
 * @param action_out Vector of output actions
 * @param sigma_out  Output the sigma (temp)
 */
void normalSampler(int size,
                     IN float *sigma_in, IN const float *action_in,
                     OUT float *action_out, OUT float *sigma_out);

#endif
