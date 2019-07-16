#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "preesm.h"


/**
 * @brief Initializes the angular state of the system to random values
 *        The angular position is initialized in [-pi;pi]
 *        The angular velocity is initialized in [-1;1]
 *
 * @param state_angular Values of angular state of the system
 */
void envInit(float *state_angular, int state_angular_size, float *state_observation, int state_space_size, float x_target, float y_target);


/**
 * @brief Performs a step in the dynamic of the environment
 *
 * @param state_angular_in  Angular state of the system
 * @param state_angular_out Angular state of the system
 * @param input_actions     List of input actions to apply to the environment
 * @param state_observation List of output observation of the next state of the environment
 * @param reward            Step reward from the actions applied
 */
void step(int state_space_size, int action_space_size, int state_angular_size, float x_target, float y_target,
IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation, OUT float *reward);


void step_noreward(int state_space_size, int action_space_size, int state_angular_size, float x_target, float y_target,
                   IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation);

void envActionLimits(OUT float *limits);

#endif
