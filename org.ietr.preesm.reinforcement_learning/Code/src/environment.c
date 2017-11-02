// std lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// math lib
#include <math.h>
// time lib
#include <time.h>

#include "../include/environment.h"

#ifndef M_PI
    #define M_PI 3.1415926535897932385f
#endif

#define MODF(a,b) ((a) - (b) * (int)((a) / (b)))

// Global Variable
float last_action = 0.f;

void envInit(float *state_angular, float *state_observation) {
    srand((unsigned int)time(NULL));
    // Use a random value to determine the sign of initial values
    float sign = (float)(rand()) / (float)(RAND_MAX);
    if (sign > 0.5f) {
        sign = 1.f;
    } else {
        sign = -1.f;
    }
    state_angular[0] = sign * M_PI * (float)(rand()) / (float)(RAND_MAX);
    sign = (float)(rand()) / (float)(RAND_MAX);
    if (sign > 0.5f) {
        sign = 1.f;
    } else {
        sign = -1.f;
    }
    state_angular[1] = sign * (float)(rand()) / (float)(RAND_MAX);
    fprintf(stderr, "Initial angular state:\n");
    fprintf(stderr, "     Angular Position: %f rad\n", state_angular[0]);
    fprintf(stderr, "     Angular Velocity: %f rad/s\n", state_angular[1]);
    state_observation[0] = cos(state_angular[0]);
    state_observation[1] = sin(state_angular[0]);
    state_observation[2] = state_angular[1];
    fprintf(stderr, "Initial state: %f - %f - %f\n", state_observation[0], state_observation[1], state_observation[2]);
}


void step(int state_space_size, int action_space_size, int state_angular_size,
          IN float *state_angular_in, OUT float *state_angular_out, IN float *input_actions, OUT float *state_observation) {
    // Get current angular state
    float theta = state_angular_in[0];
    float angular_speed = state_angular_in[1];

    // Clip value of action
    float action_clip = MIN(MAX(input_actions[0], -MAX_TORQUE), MAX_TORQUE);
    last_action = action_clip;

    // Compute reward
    float reward = POW2(MODF((theta + M_PI), (2.f * M_PI)) - M_PI) + 0.1f * POW2(angular_speed) + 0.001f*(POW2(action_clip));
    reward = -(reward);

    // Update angular state
    angular_speed = angular_speed + ((-3.f) * G_CONSTANT / (2.f * LENGTH_CONSTANT) * sin(theta + M_PI) +
            (3.f / (MASS_CONSTANT * POW2(LENGTH_CONSTANT))) * action_clip) * TIME_DELTA;
    theta = theta + angular_speed * TIME_DELTA;
    angular_speed = MIN(MAX(angular_speed, -MAX_SPEED), MAX_SPEED);
    state_angular_out[0] = theta;
    state_angular_out[1] = angular_speed;

    // Output the observations
    state_observation[0] = cos(theta);
    state_observation[1] = sin(theta);
    state_observation[2] = angular_speed;
}
