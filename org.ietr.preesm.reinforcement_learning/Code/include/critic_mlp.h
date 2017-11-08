//
// Created by farresti on 03/11/17.
//

#ifndef CRITIC_MLP_H
#define CRITIC_MLP_H

#include "preesm.h"

void criticWeightGenInit(int id, OUT float *weights_out, OUT float *bias_out);

void td_error(IN float gamma,IN float reward, IN float value_state, IN float value_next_state,
              OUT float *target, OUT float *sigma);

#endif //CRITIC_MLP_H
