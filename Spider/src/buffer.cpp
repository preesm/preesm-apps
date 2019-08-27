

#include "../include/buffer.h"


void setNbSampleToFill(Param initSize, Param nextSize,
						OUT Param* out){

	static bool init = false;

	*out = init ? nextSize : initSize;

	if(!init) init = true;
}



void shuffleBuffer(int bufferSize, int state_space_size, int action_space_size,
					IN float* reward_in, IN float* state_in, IN float* next_state_in, IN float* action_in,
					OUT float* reward_out, OUT float* state_out, OUT float* next_state_out, OUT float* action_out){

	// Create indexes array
	int index[bufferSize];
	for(int i=0; i < bufferSize; i++){
		index[i] = i;
	}

	// Shuffle indexes
	for(int i=0; i < bufferSize; i++){
		int rnd = rand() % bufferSize;

		int temp = index[rnd];
		index[rnd] = index[i];
		index[i] = temp;
	}

	// Fill state array
	for(int i=0; i < bufferSize; i++)
		for(int j=0; j < state_space_size; j++) state_out[i + j] = state_in[index[i] + j];

	// Fill next state array
	for(int i=0; i < bufferSize; i++)
		for(int j=0; j < state_space_size; j++) next_state_out[i + j] = next_state_in[index[i] + j];

	// Fill action array
	for(int i=0; i < bufferSize; i++)
		for(int j=0; j < action_space_size; j++) action_out[i + j] = action_in[index[i] + j];

	// Fill reward array
	for(int i=0; i < bufferSize; i++)
		action_out[i] = action_in[index[i]];


}

int valueInBuffer(int val, int bufferSize, int* buffer){
	for(int i=0; i < bufferSize; i++){
		if(val == buffer[i]) return true;
	}
	return false;
}


void initBuffer(){
	srand((unsigned) time(NULL));
}




void endState(int nbFilled, int nbSaved, int state_space_size,
				IN float* in){

}

void endReward(int nbFilled, int nbSaved,
				IN float* in){

}

void endAction(int nbFilled, int nbSaved, int action_space_size,
				IN float* in){

}
