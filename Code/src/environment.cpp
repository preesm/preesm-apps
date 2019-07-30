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

SdfLearner* learn;
int initialized=0;


void envInit(float *state_angular, int state_angular_size, float *state_observation, int state_space_size, float x_target, float y_target) {

	learn = initWrapper(state_angular, state_angular_size, state_observation, state_space_size, x_target, y_target);
	initialized = 1;
}


void step(int state_space_size, int action_space_size, int state_angular_size, float x_target, float y_target,
          IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation, OUT float *reward) {

	if(!initialized) envInit(state_angular_out, state_angular_size, state_observation, state_space_size, x_target, y_target);
	stepWrapper(learn, state_space_size, action_space_size, state_angular_size, x_target, y_target, state_angular_in, state_angular_out, input_actions, state_observation, reward);
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



void stateInit(int state_space_size,
				OUT float *first_state){

	for(int i=0; i < state_space_size; i++){
		first_state[i] = 0;
	}

	if(state_space_size == 6){
		state_space_size[0] = 2048;
		state_space_size[1] = 2048;
		state_space_size[2] = 2048;
		state_space_size[3] = 2048;
		state_space_size[4] = 512;
		state_space_size[5] = 256;
	}

}

void stateEnd(int state_space_size,
				IN float *last_state){

}


