/**
 * *****************************************************************************
 * Copyright or © or Copr. IETR/INSA: Maxime Pelcat, Jean-François Nezan,
 * Karol Desnos, Julien Heulot, Clément Guy, Yaset Oliva Venegas
 *
 * [mpelcat,jnezan,kdesnos,jheulot,cguy,yoliva]@insa-rennes.fr
 *
 * This software is a computer program whose purpose is to prototype
 * parallel applications.
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 * ****************************************************************************
 */

#ifndef TRAINING_H
#define TRAINING_H

#include <spider.h>

#define N_PE_TYPE 1
#define N_CORE_TYPE_X86 4
#define N_PE (N_CORE_TYPE_X86)
#define SH_MEM_SIZE (0x04000000)

void initArchi();
void freeArchi();

#define N_FCT_TRAINING 60
extern lrtFct training_fcts[N_FCT_TRAINING];

void init_training(Param action_space_size = 3, Param actor_hidden_size = 20, Param critic_hidden_size = 20, Param state_angular_size = 3, Param state_space_size = 5, Param value_space_size = 1, Param x_target = 3, Param y_target = 4);
void free_training();
std::map<lrtFct, std::map<const char *, PapifyConfig*>> get_training_papifyConfigs();
void free_training_papifyConfigs(std::map<lrtFct, std::map<const char *, PapifyConfig*>>& map);

enum class PEVirtID : std::uint32_t {
	CORE_CORE0 = 0,
	CORE_CORE1 = 1,
	CORE_CORE2 = 2,
	CORE_CORE3 = 3,
}; 

enum class PEHardwareID : std::uint32_t {
	CORE_CORE0 = 0,
	CORE_CORE1 = 1,
	CORE_CORE2 = 2,
	CORE_CORE3 = 3,
}; 

enum class PEType : std::uint32_t {
	CORE_TYPE_X86 = 0,
};

typedef enum{
	TRAINING_ENVIRONMENT_FCT = 0,
	TRAINING_TEMPORAL_DIFFERENCE_ERROR_FCT = 1,
	TRAINING_GAUSSIANPOLICY_FCT = 2,
	TRAINING_VALID_ACTOR_FCT = 3,
	TRAINING_VALID_CRITIC_FCT = 4,
	TRAINING_GEN_GAMMA_FCT = 5,
	TRAINING_GEN_SIGMA_FCT = 6,
	TRAINING_GEN_ACTOR_LEARNING_RATE_FCT = 7,
	TRAINING_GEN_CRITIC_LEARNING_RATE_FCT = 8,
	TRAINING_CLIPACTION_FCT = 9,
	TRAINING_GEN_ENVIRONMENT_LIMITS_FCT = 10,
	TRAINING_CRITIC_MLP_NEXT_ACTIVATIONFUNCTION_FCT = 11,
	TRAINING_CRITIC_MLP_NEXT_VALID_MLP_FCT = 12,
	TRAINING_CRITIC_MLP_NEXT_OUTPUTACTIVATION_FCT = 13,
	TRAINING_CRITIC_MLP_NEXT_OUTPUT_LAYER_COMPUTENEURON_FCT = 14,
	TRAINING_CRITIC_MLP_NEXT_HIDDEN_LAYER_COMPUTENEURON_FCT = 15,
	TRAINING_CRITIC_MLP_ACTIVATIONFUNCTION_FCT = 16,
	TRAINING_CRITIC_MLP_VALID_MLP_FCT = 17,
	TRAINING_CRITIC_MLP_OUTPUTACTIVATION_FCT = 18,
	TRAINING_CRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT = 19,
	TRAINING_CRITIC_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT = 20,
	TRAINING_ACTOR_MLP_ACTIVATIONFUNCTION_FCT = 21,
	TRAINING_ACTOR_MLP_VALID_MLP_FCT = 22,
	TRAINING_ACTOR_MLP_OUTPUTACTIVATION_FCT = 23,
	TRAINING_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT = 24,
	TRAINING_ACTOR_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT = 25,
	TRAINING_UPDATE_CRITIC_GEN_EPSILON_FCT = 26,
	TRAINING_UPDATE_CRITIC_ADAMBETAS_FCT = 27,
	TRAINING_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT = 28,
	TRAINING_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEBIAS_FCT = 29,
	TRAINING_UPDATE_CRITIC_ADAMHIDDEN_OPTIMIZEWEIGHTS_FCT = 30,
	TRAINING_UPDATE_CRITIC_ADAMHIDDEN_OPTIMIZEBIAS_FCT = 31,
	TRAINING_UPDATE_CRITIC_MLP_ACTIVATIONFUNCTION_FCT = 32,
	TRAINING_UPDATE_CRITIC_MLP_VALID_MLP_FCT = 33,
	TRAINING_UPDATE_CRITIC_MLP_OUTPUTACTIVATION_FCT = 34,
	TRAINING_UPDATE_CRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT = 35,
	TRAINING_UPDATE_CRITIC_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT = 36,
	TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_DERIVATIVE_FUNCTION_FCT = 37,
	TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_BACKPROPAGATED_ERROR_FCT = 38,
	TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_GRADIENTS_FCT = 39,
	TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_OUTPUT_ERROR_FCT = 40,
	TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_GRADIENTS_FCT = 41,
	TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT = 42,
	TRAINING_UPDATE_ACTOR_GEN_EPSILON_FCT = 43,
	TRAINING_UPDATE_ACTOR_ADAMBETAS_FCT = 44,
	TRAINING_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT = 45,
	TRAINING_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEBIAS_FCT = 46,
	TRAINING_UPDATE_ACTOR_ADAMHIDDEN_OPTIMIZEWEIGHTS_FCT = 47,
	TRAINING_UPDATE_ACTOR_ADAMHIDDEN_OPTIMIZEBIAS_FCT = 48,
	TRAINING_UPDATE_ACTOR_MLP_ACTIVATIONFUNCTION_FCT = 49,
	TRAINING_UPDATE_ACTOR_MLP_VALID_MLP_FCT = 50,
	TRAINING_UPDATE_ACTOR_MLP_OUTPUTACTIVATION_FCT = 51,
	TRAINING_UPDATE_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT = 52,
	TRAINING_UPDATE_ACTOR_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT = 53,
	TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_DERIVATIVE_FUNCTION_FCT = 54,
	TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_BACKPROPAGATED_ERROR_FCT = 55,
	TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_GRADIENTS_FCT = 56,
	TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_OUTPUT_ERROR_FCT = 57,
	TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_GRADIENTS_FCT = 58,
	TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT = 59,
} FctIxs;

#endif//TRAINING_H
