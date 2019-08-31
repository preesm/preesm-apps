#ifndef BUFFER_MLP_H__
#define BUFFER_MLP_H__

#include "preesm.h"
#include "spider.h"


/**
 * @brief Sets the number of samples to get (by firying actor) in order to fill the buffer
 *
 * @param initSize size of first fill
 * @param nextSize size of next fills
 *
 * The first time, buffer is empty and has to be filled entirely. After the first iteration, It requires only the missing elements extracted from buffer.
 */
void setNbSampleToFill(Param initSize, Param nextSize, Param* out);


/**
 * @brief Shuffles the buffer, when sampling, the first examples will be extracted
 *
 * @param bufferSize size of the input buffer, combination of saved samples and new ones sent by actor
 * @param state_space_size size of state space
 * @param action_space_size size of action space
 * @param reward_in input reward
 * @param state_in input state
 * @param next_state_in input next state
 * @param action_in input action
 * @param reward_out output reward
 * @param state_out output state
 * @param next_state_out output next state
 * @param action_out output action
 */
void shuffleBuffer(int bufferSize, int state_space_size, int action_space_size,
					IN float* reward_in, IN float* state_in, IN float* next_state_in, IN float* action_in,
					OUT float* reward_out, OUT float* state_out, OUT float* next_state_out, OUT float* action_out);

/**
 * @brief Checks whether value is in buffer or not
 *
 * @param val value to verify
 * @param bufferSize size of the buffer
 * @param buffer buffer to check in
 */
int valueInBuffer(int val, int bufferSize, int* buffer);

/**
 * @brief Initializes randomness to extract random samples
 */
void initBuffer();


void endState(int nbFilled, int nbSaved, int state_space_size,
				IN float* in);

void endReward(int nbFilled, int nbSaved,
				IN float* in);

void endAction(int nbFilled, int nbSaved, int action_space_size,
				IN float* in);


#endif
