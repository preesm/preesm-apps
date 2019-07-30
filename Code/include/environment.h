#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "preesm.h"

#define MAX_TORQUE 100

/**
 * @brief Initializes the angular state of the system to random values
 *        The angular position is initialized in [-pi;pi]
 *        The angular velocity is initialized in [-1;1]
 *
 * @param state_observation Initial state of the system
 * @param state_space_size 	Size of the state space
 * @param x_target 			Target x coordinate
 * @param y_target 			Target y coordinate
 * @param z_target 			Target z coordinate
 */
void envInit(float *state_observation, int state_space_size, float x_target, float y_target, float z_target);


/**
 * @brief Performs a step in the dynamic of the environment
 *
 * @param state_space_size  Size of the state space
 * @param action_space_size Size of the action space
 * @param x_target 			Target x coordinate
 * @param y_target 			Target y coordinate
 * @param z_target 			Target z coordinate
 * @param input_actions     List of input actions to apply to the environment
 * @param state_observation List of output observation of the next state of the environment
 * @param reward            Step reward from the actions applied
 */
void step(int state_space_size, int action_space_size, float x_target, float y_target, z_target,
					IN float *input_actions, OUT float *state_observation, OUT float *reward);


void step_noreward(int state_space_size, int action_space_size, float x_target, float y_target, float z_target,
					IN float *input_actions, OUT float *state_observation);

void envActionLimits(OUT float *limits);

void stateInit(int state_space_size,
				OUT float *first_state);

void stateEnd(int state_space_size,
				IN float *last_state);

#endif
