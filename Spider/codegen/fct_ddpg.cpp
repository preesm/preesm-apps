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

#include <spider.h>
#include "ddpg.h"

#include "environment.h"
#include "critic.h"
#include "actor.h"
#include "common.h"
#include "buffer.h"
#include "mlp.h"

void ddpg_Environment(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Temporal_Difference_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_GaussianPolicy(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_valid_actor(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_valid_critic(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_gamma(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_sigma(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_actor_learning_rate(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_critic_learning_rate(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_ClipAction(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_environment_limits(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Set_FillSize(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Init_State(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_End_State(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_gen_to(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Actor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Fill_Buffer_Shuffle(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetActor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_TargetCritic_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Set_TargetActor_SetWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Set_TargetActor_SetBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Set_TargetCritic_SetWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Set_TargetCritic_SetBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_gen_epsilon(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_adamBetas(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsOutput_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsOutput_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_gen_epsilon(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_adamBetas(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsOutput_Output_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsOutput_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsOutput_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);
void ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]);

lrtFct ddpg_fcts[N_FCT_DDPG] = {
	&ddpg_Environment,
	&ddpg_Temporal_Difference_Error,
	&ddpg_GaussianPolicy,
	&ddpg_valid_actor,
	&ddpg_valid_critic,
	&ddpg_gen_gamma,
	&ddpg_gen_sigma,
	&ddpg_gen_actor_learning_rate,
	&ddpg_gen_critic_learning_rate,
	&ddpg_ClipAction,
	&ddpg_gen_environment_limits,
	&ddpg_Set_FillSize,
	&ddpg_Init_State,
	&ddpg_End_State,
	&ddpg_gen_to,
	&ddpg_Actor_MLP_activationFunction_0,
	&ddpg_Actor_MLP_valid_mlp,
	&ddpg_Actor_MLP_outputActivation,
	&ddpg_Actor_MLP_activationFunction_1,
	&ddpg_Actor_MLP_Output_layer_computeNeuron,
	&ddpg_Actor_MLP_Hidden_layer_0_computeNeuron,
	&ddpg_Actor_MLP_Hidden_layer_1_computeNeuron,
	&ddpg_Fill_Buffer_Shuffle,
	&ddpg_TargetActor_MLP_activationFunction_0,
	&ddpg_TargetActor_MLP_valid_mlp,
	&ddpg_TargetActor_MLP_outputActivation,
	&ddpg_TargetActor_MLP_activationFunction_1,
	&ddpg_TargetActor_MLP_Output_layer_computeNeuron,
	&ddpg_TargetActor_MLP_Hidden_layer_0_computeNeuron,
	&ddpg_TargetActor_MLP_Hidden_layer_1_computeNeuron,
	&ddpg_TargetCritic_MLP_activationFunction_0,
	&ddpg_TargetCritic_MLP_valid_mlp,
	&ddpg_TargetCritic_MLP_outputActivation,
	&ddpg_TargetCritic_MLP_activationFunction_1,
	&ddpg_TargetCritic_MLP_Output_layer_computeNeuron,
	&ddpg_TargetCritic_MLP_Hidden_layer_0_computeNeuron,
	&ddpg_TargetCritic_MLP_Hidden_layer_1_computeNeuron,
	&ddpg_Set_TargetActor_SetWeights,
	&ddpg_Set_TargetActor_SetBias,
	&ddpg_Set_TargetCritic_SetWeights,
	&ddpg_Set_TargetCritic_SetBias,
	&ddpg_Update_Networks_Update_Actor_gen_epsilon,
	&ddpg_Update_Networks_Update_Actor_adamBetas,
	&ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeWeights,
	&ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeBias,
	&ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeWeights,
	&ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeBias,
	&ddpg_Update_Networks_Update_Actor_MLP_activationFunction_0,
	&ddpg_Update_Networks_Update_Actor_MLP_valid_mlp,
	&ddpg_Update_Networks_Update_Actor_MLP_outputActivation,
	&ddpg_Update_Networks_Update_Actor_MLP_activationFunction_1,
	&ddpg_Update_Networks_Update_Actor_MLP_Output_layer_computeNeuron,
	&ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0_computeNeuron,
	&ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1_computeNeuron,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Derivative_Function,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_1_BackPropagated_Error,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Gradients,
	&ddpg_Update_Networks_Update_Actor_GradientsOutput_Gradients,
	&ddpg_Update_Networks_Update_Actor_GradientsOutput_Derivative_Function,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Derivative_Function,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_0_BackPropagated_Error,
	&ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Gradients,
	&ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeWeights,
	&ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeBias,
	&ddpg_Update_Networks_Update_Actor_Critic_activationFunction_0,
	&ddpg_Update_Networks_Update_Actor_Critic_valid_mlp,
	&ddpg_Update_Networks_Update_Actor_Critic_outputActivation,
	&ddpg_Update_Networks_Update_Actor_Critic_activationFunction_1,
	&ddpg_Update_Networks_Update_Actor_Critic_Output_layer_computeNeuron,
	&ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0_computeNeuron,
	&ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1_computeNeuron,
	&ddpg_Update_Networks_Update_Critic_gen_epsilon,
	&ddpg_Update_Networks_Update_Critic_adamBetas,
	&ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeWeights,
	&ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeBias,
	&ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeWeights,
	&ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeBias,
	&ddpg_Update_Networks_Update_Critic_MLP_activationFunction_0,
	&ddpg_Update_Networks_Update_Critic_MLP_valid_mlp,
	&ddpg_Update_Networks_Update_Critic_MLP_outputActivation,
	&ddpg_Update_Networks_Update_Critic_MLP_activationFunction_1,
	&ddpg_Update_Networks_Update_Critic_MLP_Output_layer_computeNeuron,
	&ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0_computeNeuron,
	&ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1_computeNeuron,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Derivative_Function,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_1_BackPropagated_Error,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Gradients,
	&ddpg_Update_Networks_Update_Critic_GradientsOutput_Output_Error,
	&ddpg_Update_Networks_Update_Critic_GradientsOutput_Gradients,
	&ddpg_Update_Networks_Update_Critic_GradientsOutput_Derivative_Function,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Derivative_Function,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_0_BackPropagated_Error,
	&ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Gradients,
	&ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeWeights,
	&ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeBias,
};

void ddpg_Environment(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	step(
		/* state_space_size  */ (Param) inParams[0],
		/* action_space_size */ (Param) inParams[1],
		/* x_target          */ (Param) inParams[2],
		/* y_target          */ (Param) inParams[3],
		/* z_target          */ (Param) inParams[4],
		/* input_actions     */ (float *) inputFIFOs[0],
		/* state_observation */ (float *) outputFIFOs[0],
		/* reward            */ (float *) outputFIFOs[1]
	);
}

void ddpg_Temporal_Difference_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	td_error(
		/* gamma_in         */ (float *) inputFIFOs[2],
		/* reward           */ (float *) inputFIFOs[1],
		/* value_next_state */ (float *) inputFIFOs[0],
		/* target           */ (float *) outputFIFOs[1],
		/* delta            */ (float *) outputFIFOs[0]
	);
}

void ddpg_GaussianPolicy(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	actionSampler(
		/* size       */ (Param) inParams[0],
		/* sigma_in   */ (float *) inputFIFOs[1],
		/* action_in  */ (const float *) inputFIFOs[0],
		/* action_out */ (float *) outputFIFOs[0]
	);
}

void ddpg_valid_actor(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	validActor(
		/* sigma */ (float *) inputFIFOs[0],
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_valid_critic(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_gen_gamma(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	gammaGen(
		/* gamma */ (float *) outputFIFOs[0]
	);
}

void ddpg_gen_sigma(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	sigmaGen(
		/* sigma */ (float *) outputFIFOs[0]
	);
}

void ddpg_gen_actor_learning_rate(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	actorLearningRateGen(
		/* learning_rate */ (float *) outputFIFOs[0]
	);
}

void ddpg_gen_critic_learning_rate(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	criticLearningRateGen(
		/* learning_rate */ (float *) outputFIFOs[0]
	);
}

void ddpg_ClipAction(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	clipValues(
		/* size   */ (Param) inParams[0],
		/* input  */ (float *) inputFIFOs[0],
		/* limits */ (float *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_gen_environment_limits(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	envActionLimits(
		/* limits */ (float *) outputFIFOs[0]
	);
}

void ddpg_Set_FillSize(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	setNbSampleToFill(
		/* initSize */ (Param) inParams[1],
		/* nextSize */ (Param) inParams[0],
		/* out      */ (Param*) &outParams[0]
	);
}

void ddpg_Init_State(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	stateInit(
		/* state_space_size */ (Param) inParams[0],
		/* first_state      */ (float *) outputFIFOs[0]
	);
}

void ddpg_End_State(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	stateEnd(
		/* state_space_size */ (Param) inParams[0],
		/* last_state       */ (float *) inputFIFOs[0]
	);
}

void ddpg_gen_to(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	genTo(
		/* to */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Actor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Fill_Buffer_Shuffle(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	shuffleBuffer(
		/* bufferSize       */ (Param) inParams[1],
		/* state_space_size */ (Param) inParams[0],
		/* reward_in        */ (int action_space_size IN float *) inputFIFOs[0],
		/* state_in         */ (float *) inputFIFOs[2],
		/* next_state_in    */ (float *) inputFIFOs[3],
		/* action_in        */ (float *) inputFIFOs[1],
		/* reward_out       */ (float *) outputFIFOs[0],
		/* state_out        */ (float *) outputFIFOs[2],
		/* next_state_out   */ (float *) outputFIFOs[3],
		/* action_out       */ (float *) outputFIFOs[1]
	);
}

void ddpg_TargetActor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetActor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_TargetCritic_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Set_TargetActor_SetWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	setTarget(
		/* target  */ (float *) inputFIFOs[0],
		/* current */ (float *) inputFIFOs[1],
		/* to      */ (float *) inputFIFOs[2],
		/* out     */ (float *) outputFIFOs[0]
	);
}

void ddpg_Set_TargetActor_SetBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	setTarget(
		/* target  */ (float *) inputFIFOs[0],
		/* current */ (float *) inputFIFOs[1],
		/* to      */ (float *) inputFIFOs[2],
		/* out     */ (float *) outputFIFOs[0]
	);
}

void ddpg_Set_TargetCritic_SetWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	setTarget(
		/* target  */ (float *) inputFIFOs[0],
		/* current */ (float *) inputFIFOs[1],
		/* to      */ (float *) inputFIFOs[2],
		/* out     */ (float *) outputFIFOs[0]
	);
}

void ddpg_Set_TargetCritic_SetBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	setTarget(
		/* target  */ (float *) inputFIFOs[0],
		/* current */ (float *) inputFIFOs[1],
		/* to      */ (float *) inputFIFOs[2],
		/* out     */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_gen_epsilon(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	adamEpsilonGen(
		/* epsilon */ (double *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_adamBetas(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	adamUpdateBetas(
		/* betas_in  */ (double *) inputFIFOs[0],
		/* valid     */ (int *) inputFIFOs[1],
		/* betas_out */ (double *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamOutput_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamHidden_1_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeTanHyperbolic(
		/* input  */ (float *) inputFIFOs[1],
		/* valid  */ (int *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeLayerBackPropError(
		/* layer_size         */ (Param) inParams[0],
		/* next_layer_size    */ (Param) inParams[1],
		/* valid              */ (int *) inputFIFOs[2],
		/* derivative_values  */ (float *) inputFIFOs[0],
		/* next_layer_errors  */ (float *) inputFIFOs[1],
		/* next_layer_weights */ (float *) inputFIFOs[3],
		/* errors             */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_1_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsOutput_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsOutput_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeNeuralNetwork(
		/* input_size        */ (Param) inParams[1],
		/* output_size       */ (Param) inParams[0],
		/* hidden_size_0     */ (Param) inParams[2],
		/* hidden_size_1     */ (Param) inParams[3],
		/* critic_input_size */ (Param) inParams[6],
		/* input             */ (float *) inputFIFOs[0],
		/* network_weights   */ (float *) inputFIFOs[1],
		/* network_bias      */ (float *) inputFIFOs[2],
		/* output            */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeTanHyperbolic(
		/* input  */ (float *) inputFIFOs[1],
		/* valid  */ (int *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeLayerBackPropError(
		/* layer_size         */ (Param) inParams[0],
		/* next_layer_size    */ (Param) inParams[1],
		/* valid              */ (int *) inputFIFOs[2],
		/* derivative_values  */ (float *) inputFIFOs[0],
		/* next_layer_errors  */ (float *) inputFIFOs[1],
		/* next_layer_weights */ (float *) inputFIFOs[3],
		/* errors             */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_GradientsHidden_0_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Actor_AdamHidden_0_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_gen_epsilon(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	adamEpsilonGen(
		/* epsilon */ (double *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_adamBetas(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	adamUpdateBetas(
		/* betas_in  */ (double *) inputFIFOs[0],
		/* valid     */ (int *) inputFIFOs[1],
		/* betas_out */ (double *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamOutput_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamHidden_1_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_activationFunction_0(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_valid_mlp(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	valid(
		/* valid */ (int *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_outputActivation(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_activationFunction_1(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	activateTanHyperbolic(
		/* input  */ (float *) inputFIFOs[0],
		/* valid  */ (int *) inputFIFOs[1],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_Output_layer_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1_computeNeuron(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	neuron(
		/* input_size  */ (Param) inParams[0],
		/* input       */ (float *) inputFIFOs[1],
		/* weights     */ (float *) inputFIFOs[3],
		/* bias_values */ (float *) inputFIFOs[0],
		/* valid       */ (int *) inputFIFOs[2],
		/* output      */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeTanHyperbolic(
		/* input  */ (float *) inputFIFOs[1],
		/* valid  */ (int *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeLayerBackPropError(
		/* layer_size         */ (Param) inParams[0],
		/* next_layer_size    */ (Param) inParams[1],
		/* valid              */ (int *) inputFIFOs[2],
		/* derivative_values  */ (float *) inputFIFOs[0],
		/* next_layer_errors  */ (float *) inputFIFOs[1],
		/* next_layer_weights */ (float *) inputFIFOs[3],
		/* errors             */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_1_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsOutput_Output_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeOutputError(
		/* output_size       */ (Param) inParams[0],
		/* valid             */ (int *) inputFIFOs[2],
		/* derivative_values */ (float *) inputFIFOs[0],
		/* predicted         */ (float *) inputFIFOs[1],
		/* target            */ (float *) inputFIFOs[3],
		/* errors            */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsOutput_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsOutput_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeLinear(
		/* input  */ (float *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Derivative_Function(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	derivativeTanHyperbolic(
		/* input  */ (float *) inputFIFOs[1],
		/* valid  */ (int *) inputFIFOs[0],
		/* output */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_BackPropagated_Error(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeLayerBackPropError(
		/* layer_size         */ (Param) inParams[0],
		/* next_layer_size    */ (Param) inParams[1],
		/* valid              */ (int *) inputFIFOs[2],
		/* derivative_values  */ (float *) inputFIFOs[0],
		/* next_layer_errors  */ (float *) inputFIFOs[1],
		/* next_layer_weights */ (float *) inputFIFOs[3],
		/* errors             */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_GradientsHidden_0_Gradients(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	computeWeightsGradients(
		/* input_size */ (Param) inParams[0],
		/* layer_size */ (Param) inParams[1],
		/* errors     */ (float *) inputFIFOs[0],
		/* inputs     */ (float *) inputFIFOs[1],
		/* valid      */ (int *) inputFIFOs[2],
		/* gradients  */ (float *) outputFIFOs[0]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeWeights(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[7],
		/* learning_rate */ (float *) inputFIFOs[5],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[1],
		/* param_in      */ (float *) inputFIFOs[4],
		/* fo_moment_in  */ (double *) inputFIFOs[2],
		/* so_moment_in  */ (double *) inputFIFOs[6],
		/* gradients     */ (float *) inputFIFOs[3],
		/* param_out     */ (float *) outputFIFOs[2],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[1]
	);
}

void ddpg_Update_Networks_Update_Critic_AdamHidden_0_optimizeBias(void* inputFIFOs[], void* outputFIFOs[], Param inParams[], Param outParams[]){
	applyAdamOptimizer(
		/* size          */ (Param) inParams[0],
		/* valid         */ (int *) inputFIFOs[6],
		/* learning_rate */ (float *) inputFIFOs[7],
		/* betas         */ (double *) inputFIFOs[0],
		/* epsilon       */ (double *) inputFIFOs[2],
		/* param_in      */ (float *) inputFIFOs[1],
		/* fo_moment_in  */ (double *) inputFIFOs[3],
		/* so_moment_in  */ (double *) inputFIFOs[5],
		/* gradients     */ (float *) inputFIFOs[4],
		/* param_out     */ (float *) outputFIFOs[1],
		/* fo_moment_out */ (double *) outputFIFOs[0],
		/* so_moment_out */ (double *) outputFIFOs[2]
	);
}

