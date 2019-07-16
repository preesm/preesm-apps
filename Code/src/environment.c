// std lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// math lib
#include <math.h>
// time lib
#include <time.h>
// file headers
#include "../include/environment.h"
#include "../include/common.h"

// environment
#include "sdflearner.h"

extern int preesmStopThreads;
struct sdfLearner;


void envInit(float *state_angular, int state_angular_size, float *state_observation, int state_space_size, float x_target, float y_target) {

	sdfLearner = initWrapper(state_angular, state_angular_size, state_observation, state_space_size, x_target, y_target);
}


void step(int state_space_size, int action_space_size, int state_angular_size, float x_target, float y_target,
          IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation, OUT float *reward) {

	stepWrapper(sdfLearner, state_space_size, action_space_size, state_angular_size, x_target, y_target, state_angular_in, state_angular_out, input_actions, state_observation, reward);
}

void step_noreward(int state_space_size, int action_space_size, int state_angular_size, float x_target, float y_target,
                   IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation) {
    step(state_space_size,
         action_space_size,
         state_angular_size,
		 x_target,
		 y_target,
         state_angular_in,
         state_angular_out,
         input_actions,
         state_observation, NULL);
}


void envActionLimits(OUT float *limits) {
    limits[0] = -MAX_TORQUE;
    limits[1] = MAX_TORQUE;
}
