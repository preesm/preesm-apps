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

#include "ddpg.h"

void ddpg(PiSDFVertex *bo_ddpg, Param action_space_size = 3, Param bufferSize = 10, Param hidden_size_0 = 400, Param hidden_size_1 = 300, Param sampleSize = 1, Param state_space_size = 6, Param value_space_size = 1, Param x_target = 3, Param y_target = 4, Param z_target = 2);
void ddpg_Actor_MLP(PiSDFVertex *bo_Actor_MLP);
void ddpg_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_Actor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_Actor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_Fill_Buffer(PiSDFVertex *bo_Fill_Buffer);
void ddpg_TargetActor_MLP(PiSDFVertex *bo_TargetActor_MLP);
void ddpg_TargetActor_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_TargetActor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_TargetActor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_TargetCritic_MLP(PiSDFVertex *bo_TargetCritic_MLP);
void ddpg_TargetCritic_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_TargetCritic_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_TargetCritic_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_Set_TargetActor(PiSDFVertex *bo_Set_TargetActor);
void ddpg_Set_TargetCritic(PiSDFVertex *bo_Set_TargetCritic);
void ddpg_Update_Networks(PiSDFVertex *bo_Update_Networks);
void ddpg_Update_Networks_Update_Actor(PiSDFVertex *bo_Update_Actor);
void ddpg_Update_Networks_Update_Actor_AdamOutput(PiSDFVertex *bo_AdamOutput);
void ddpg_Update_Networks_Update_Actor_AdamHidden_1(PiSDFVertex *bo_AdamHidden_1);
void ddpg_Update_Networks_Update_Actor_MLP(PiSDFVertex *bo_MLP);
void ddpg_Update_Networks_Update_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_1(PiSDFVertex *bo_GradientsHidden_1);
void ddpg_Update_Networks_Update_Actor_GradientsOutput(PiSDFVertex *bo_GradientsOutput);
void ddpg_Update_Networks_Update_Actor_GradientsHidden_0(PiSDFVertex *bo_GradientsHidden_0);
void ddpg_Update_Networks_Update_Actor_AdamHidden_0(PiSDFVertex *bo_AdamHidden_0);
void ddpg_Update_Networks_Update_Actor_Critic(PiSDFVertex *bo_Critic);
void ddpg_Update_Networks_Update_Actor_Critic_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_Update_Networks_Update_Critic(PiSDFVertex *bo_Update_Critic);
void ddpg_Update_Networks_Update_Critic_AdamOutput(PiSDFVertex *bo_AdamOutput);
void ddpg_Update_Networks_Update_Critic_AdamHidden_1(PiSDFVertex *bo_AdamHidden_1);
void ddpg_Update_Networks_Update_Critic_MLP(PiSDFVertex *bo_MLP);
void ddpg_Update_Networks_Update_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0);
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_1(PiSDFVertex *bo_GradientsHidden_1);
void ddpg_Update_Networks_Update_Critic_GradientsOutput(PiSDFVertex *bo_GradientsOutput);
void ddpg_Update_Networks_Update_Critic_GradientsHidden_0(PiSDFVertex *bo_GradientsHidden_0);
void ddpg_Update_Networks_Update_Critic_AdamHidden_0(PiSDFVertex *bo_AdamHidden_0);

/**
 * This is the method you need to call to build a complete PiSDF graph.
 */
void init_ddpg(Param action_space_size, Param bufferSize, Param hidden_size_0, Param hidden_size_1, Param sampleSize, Param state_space_size, Param value_space_size, Param x_target, Param y_target, Param z_target){
	PiSDFGraph* topGraph = Spider::createGraph(
		/*Edges*/    0,
		/*Params*/   0,
		/*InputIf*/  0,
		/*OutputIf*/ 0,
		/*Config*/   0,
		/*Body*/     1);

	PiSDFVertex* topVertex = Spider::addBodyVertex(
		/*Graph*/   topGraph,
		/*Name*/    "top",
		/*FctId*/   -1,
		/*InData*/   0,
		/*OutData*/  0,
		/*InParam*/  0);

	/* Top graph definition */
	ddpg(topVertex, action_space_size, bufferSize, hidden_size_0, hidden_size_1, sampleSize, state_space_size, value_space_size, x_target, y_target, z_target);

	/* Setting main application graph */
	Spider::setGraph(topGraph);
}

// Method building PiSDFGraph: ddpg
void ddpg(PiSDFVertex *bo_ddpg, Param action_space_size, Param bufferSize, Param hidden_size_0, Param hidden_size_1, Param sampleSize, Param state_space_size, Param value_space_size, Param x_target, Param y_target, Param z_target){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    67,
		/*Params*/   16,
		/*InputIf*/  0,
		/*OutputIf*/ 0,
		/*Config*/   1,
		/*Body*/     50);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_ddpg, graph);

	/* === Parameters === */

	PiSDFParam *param_action_space_size = Spider::addStaticParam(graph, "action_space_size", action_space_size);
	PiSDFParam *param_state_space_size = Spider::addStaticParam(graph, "state_space_size", state_space_size);
	PiSDFParam *param_value_space_size = Spider::addStaticParam(graph, "value_space_size", value_space_size);
	PiSDFParam *param_hidden_size_0 = Spider::addStaticParam(graph, "hidden_size_0", hidden_size_0);
	PiSDFParam *param_x_target = Spider::addStaticParam(graph, "x_target", x_target);
	PiSDFParam *param_y_target = Spider::addStaticParam(graph, "y_target", y_target);
	PiSDFParam *param_z_target = Spider::addStaticParam(graph, "z_target", z_target);
	PiSDFParam *param_hidden_size_1 = Spider::addStaticParam(graph, "hidden_size_1", hidden_size_1);
	PiSDFParam *param_sampleSize = Spider::addStaticParam(graph, "sampleSize", sampleSize);
	PiSDFParam *param_bufferSize = Spider::addStaticParam(graph, "bufferSize", bufferSize);
	PiSDFParam *param_nbFireActor = Spider::addDynamicParam(graph, "nbFireActor");
	PiSDFParam *param_critic_weights_size = Spider::addStaticDependentParam(graph, "critic_weights_size", "(state_space_size + action_space_size) * hidden_size_0 + hidden_size_0 *  hidden_size_1 + hidden_size_1 * value_space_size", {param_state_space_size, param_value_space_size, param_action_space_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_critic_bias_size = Spider::addStaticDependentParam(graph, "critic_bias_size", "value_space_size + hidden_size_1 + hidden_size_0", {param_value_space_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_actor_weights_size = Spider::addStaticDependentParam(graph, "actor_weights_size", "state_space_size * hidden_size_0 +  hidden_size_0 * hidden_size_1 + hidden_size_1 * action_space_size", {param_hidden_size_0, param_action_space_size, param_state_space_size, param_hidden_size_1});
	PiSDFParam *param_actor_bias_size = Spider::addStaticDependentParam(graph, "actor_bias_size", "action_space_size + hidden_size_1 + hidden_size_0", {param_hidden_size_0, param_action_space_size, param_hidden_size_1});
	PiSDFParam *param_actionState_space_size = Spider::addStaticDependentParam(graph, "actionState_space_size", "action_space_size + state_space_size", {param_state_space_size, param_action_space_size});

	/* === Vertices === */

	PiSDFVertex* bo_Environment = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Environment",
		/*FctId*/   DDPG_ENVIRONMENT_FCT,
		/*InData*/  1,
		/*OutData*/ 2,
		/*InParam*/ 5);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Environment, 0, param_state_space_size);
	Spider::addInParam(bo_Environment, 1, param_action_space_size);
	Spider::addInParam(bo_Environment, 2, param_x_target);
	Spider::addInParam(bo_Environment, 3, param_y_target);
	Spider::addInParam(bo_Environment, 4, param_z_target);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Environment);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Environment, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastNextStateFeature = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastNextStateFeature",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastNextStateFeature, 0, param_state_space_size);

	PiSDFVertex* bo_Temporal_Difference_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Temporal_Difference_Error",
		/*FctId*/   DDPG_TEMPORAL_DIFFERENCE_ERROR_FCT,
		/*InData*/  3,
		/*OutData*/ 2,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Temporal_Difference_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Temporal_Difference_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastWeightsCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeightsCritic",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeightsCritic, 0, param_critic_weights_size);

	PiSDFVertex* bo_BroadcastBiasCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasCritic",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastBiasCritic, 0, param_critic_bias_size);

	PiSDFVertex* bo_GaussianPolicy = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GaussianPolicy",
		/*FctId*/   DDPG_GAUSSIANPOLICY_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GaussianPolicy, 0, param_action_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_GaussianPolicy);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GaussianPolicy, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_broadcastAction = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "broadcastAction",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_broadcastAction, 0, param_action_space_size);

	PiSDFVertex* bo_BroadcastWeightsActor = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeightsActor",
		/*OutData*/ 3,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastWeightsActor, 0, param_actor_weights_size);
	Spider::addInParam(bo_BroadcastWeightsActor, 1, param_nbFireActor);

	PiSDFVertex* bo_BroadcastBiasActor = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasActor",
		/*OutData*/ 3,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastBiasActor, 0, param_actor_bias_size);
	Spider::addInParam(bo_BroadcastBiasActor, 1, param_nbFireActor);

	PiSDFVertex* bo_valid_actor = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_actor",
		/*FctId*/   DDPG_VALID_ACTOR_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_actor);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_actor, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_critic = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_critic",
		/*FctId*/   DDPG_VALID_CRITIC_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_critic);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_critic, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_gamma = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_gamma",
		/*FctId*/   DDPG_GEN_GAMMA_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_gamma);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_gamma, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_sigma = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_sigma",
		/*FctId*/   DDPG_GEN_SIGMA_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_sigma);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_sigma, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_actor_learning_rate = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_actor_learning_rate",
		/*FctId*/   DDPG_GEN_ACTOR_LEARNING_RATE_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_actor_learning_rate);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_actor_learning_rate, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_critic_learning_rate = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_critic_learning_rate",
		/*FctId*/   DDPG_GEN_CRITIC_LEARNING_RATE_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_critic_learning_rate);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_critic_learning_rate, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ClipAction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "ClipAction",
		/*FctId*/   DDPG_CLIPACTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_ClipAction, 0, param_action_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_ClipAction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_ClipAction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_environment_limits = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_environment_limits",
		/*FctId*/   DDPG_GEN_ENVIRONMENT_LIMITS_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_environment_limits);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_environment_limits, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastWeightsTargetActor = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeightsTargetActor",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastWeightsTargetActor, 0, param_actor_weights_size);
	Spider::addInParam(bo_BroadcastWeightsTargetActor, 1, param_sampleSize);

	PiSDFVertex* bo_BroadcastBiasTargetActor = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasTargetActor",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastBiasTargetActor, 0, param_actor_bias_size);
	Spider::addInParam(bo_BroadcastBiasTargetActor, 1, param_sampleSize);

	PiSDFVertex* bo_BroadcastBiasTargetCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasTargetCritic",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastBiasTargetCritic, 0, param_critic_bias_size);
	Spider::addInParam(bo_BroadcastBiasTargetCritic, 1, param_sampleSize);

	PiSDFVertex* bo_BroadcastWeightsTargetCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeightsTargetCritic",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastWeightsTargetCritic, 0, param_critic_weights_size);
	Spider::addInParam(bo_BroadcastWeightsTargetCritic, 1, param_sampleSize);

	PiSDFVertex* bo_JoinTargetActionState = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinTargetActionState",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinTargetActionState, 0, param_state_space_size);
	Spider::addInParam(bo_JoinTargetActionState, 1, param_action_space_size);
	Spider::addInParam(bo_JoinTargetActionState, 2, param_sampleSize);

	PiSDFVertex* bo_BroadcastSampledState = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastSampledState",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastSampledState, 0, param_sampleSize);
	Spider::addInParam(bo_BroadcastSampledState, 1, param_state_space_size);

	PiSDFVertex *cf_Set_FillSize = Spider::addConfigVertex(
		/*Graph*/   graph,
		/*Name*/    "Set_FillSize",
		/*FctId*/   DDPG_SET_FILLSIZE_FCT,
		/*InData*/  0,
		/*OutData*/ 0,
		/*InParam*/ 2,
		/*OutParam*/1);
	/* == Adding output parameters == */
	Spider::addOutParam(cf_Set_FillSize, 0, param_nbFireActor);
	/* == Adding input parameters == */
	Spider::addInParam(cf_Set_FillSize, 0, param_sampleSize);
	Spider::addInParam(cf_Set_FillSize, 1, param_bufferSize);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(cf_Set_FillSize);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(cf_Set_FillSize, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_JoinActionState = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinActionState",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinActionState, 0, param_state_space_size);
	Spider::addInParam(bo_JoinActionState, 1, param_action_space_size);
	Spider::addInParam(bo_JoinActionState, 2, param_sampleSize);

	PiSDFVertex* bo_Init_State = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Init_State",
		/*FctId*/   DDPG_INIT_STATE_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Init_State, 0, param_state_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Init_State);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Init_State, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_End_State = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "End_State",
		/*FctId*/   DDPG_END_STATE_FCT,
		/*InData*/  1,
		/*OutData*/ 0,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_End_State, 0, param_state_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_End_State);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_End_State, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_gen_to = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_to",
		/*FctId*/   DDPG_GEN_TO_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_to);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_to, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastTo = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastTo",
		/*OutData*/ 2,
		/*InParam*/ 4);
	Spider::addInParam(bo_BroadcastTo, 0, param_actor_weights_size);
	Spider::addInParam(bo_BroadcastTo, 1, param_actor_bias_size);
	Spider::addInParam(bo_BroadcastTo, 2, param_critic_weights_size);
	Spider::addInParam(bo_BroadcastTo, 3, param_critic_bias_size);

	PiSDFVertex* bo_BroadcastSampledNextState = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastSampledNextState",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadcastSampledNextState, 0, param_sampleSize);
	Spider::addInParam(bo_BroadcastSampledNextState, 1, param_state_space_size);

	PiSDFVertex* bo_BroadcastStateFeature = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastStateFeature",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastStateFeature, 0, param_state_space_size);

	PiSDFVertex* bo_Actor_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Actor_MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Actor_MLP, 0, param_action_space_size);
	Spider::addInParam(bo_Actor_MLP, 1, param_state_space_size);
	Spider::addInParam(bo_Actor_MLP, 2, param_hidden_size_0);
	Spider::addInParam(bo_Actor_MLP, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Actor_MLP(bo_Actor_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Actor_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Fill_Buffer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Fill_Buffer",
		/*FctId*/   -1,
		/*InData*/  8,
		/*OutData*/ 8,
		/*InParam*/ 5);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Fill_Buffer, 0, param_sampleSize);
	Spider::addInParam(bo_Fill_Buffer, 1, param_bufferSize);
	Spider::addInParam(bo_Fill_Buffer, 2, param_state_space_size);
	Spider::addInParam(bo_Fill_Buffer, 3, param_action_space_size);
	Spider::addInParam(bo_Fill_Buffer, 4, param_nbFireActor);
	/* == Generating subgraph definition == */
	ddpg_Fill_Buffer(bo_Fill_Buffer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Fill_Buffer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_TargetActor_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "TargetActor_MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_TargetActor_MLP, 0, param_action_space_size);
	Spider::addInParam(bo_TargetActor_MLP, 1, param_state_space_size);
	Spider::addInParam(bo_TargetActor_MLP, 2, param_hidden_size_0);
	Spider::addInParam(bo_TargetActor_MLP, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_TargetActor_MLP(bo_TargetActor_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_TargetActor_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_TargetCritic_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "TargetCritic_MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_TargetCritic_MLP, 0, param_value_space_size);
	Spider::addInParam(bo_TargetCritic_MLP, 1, param_actionState_space_size);
	Spider::addInParam(bo_TargetCritic_MLP, 2, param_hidden_size_0);
	Spider::addInParam(bo_TargetCritic_MLP, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_TargetCritic_MLP(bo_TargetCritic_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_TargetCritic_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Set_TargetActor = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Set_TargetActor",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Set_TargetActor, 0, param_actor_weights_size);
	Spider::addInParam(bo_Set_TargetActor, 1, param_actor_bias_size);
	/* == Generating subgraph definition == */
	ddpg_Set_TargetActor(bo_Set_TargetActor);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Set_TargetActor, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Set_TargetCritic = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Set_TargetCritic",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Set_TargetCritic, 0, param_critic_weights_size);
	Spider::addInParam(bo_Set_TargetCritic, 1, param_critic_bias_size);
	/* == Generating subgraph definition == */
	ddpg_Set_TargetCritic(bo_Set_TargetCritic);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Set_TargetCritic, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Update_Networks = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Update_Networks",
		/*FctId*/   -1,
		/*InData*/  11,
		/*OutData*/ 4,
		/*InParam*/ 7);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Update_Networks, 0, param_sampleSize);
	Spider::addInParam(bo_Update_Networks, 1, param_hidden_size_0);
	Spider::addInParam(bo_Update_Networks, 2, param_hidden_size_1);
	Spider::addInParam(bo_Update_Networks, 3, param_value_space_size);
	Spider::addInParam(bo_Update_Networks, 4, param_actionState_space_size);
	Spider::addInParam(bo_Update_Networks, 5, param_action_space_size);
	Spider::addInParam(bo_Update_Networks, 6, param_state_space_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks(bo_Update_Networks);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Update_Networks, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "((bufferSize - sampleSize) * 1)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "((bufferSize - sampleSize) * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "((bufferSize - sampleSize) * 1) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    6, 
			/* = Prod Expr = */ "((bufferSize - sampleSize) * state_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "((bufferSize - sampleSize) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "((bufferSize - sampleSize) * state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    7, 
			/* = Prod Expr = */ "((bufferSize - sampleSize) * state_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "((bufferSize - sampleSize) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "((bufferSize - sampleSize) * state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    5, 
			/* = Prod Expr = */ "((bufferSize - sampleSize) * action_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "((bufferSize - sampleSize) * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "((bufferSize - sampleSize) * action_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Set_TargetActor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(actor_weights_size)*4",
			/* = Snk = */       bo_BroadcastWeightsTargetActor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_weights_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Set_TargetActor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_BroadcastBiasTargetActor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_bias_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Set_TargetCritic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "( critic_weights_size)*4",
			/* = Snk = */       bo_BroadcastWeightsTargetCritic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_weights_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Set_TargetCritic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_BroadcastBiasTargetCritic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_bias_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Networks, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(state_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * action_space_size)*4",
			/* = Snk = */       bo_BroadcastWeightsActor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_weights_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Networks, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(action_space_size + hidden_size_1 + hidden_size_0)*4",
			/* = Snk = */       bo_BroadcastBiasActor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_bias_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Networks, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(actionState_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * value_space_size)*4",
			/* = Snk = */       bo_BroadcastWeightsCritic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_weights_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Networks, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(value_space_size + hidden_size_1 + hidden_size_0)*4",
			/* = Snk = */       bo_BroadcastBiasCritic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_bias_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastNextStateFeature, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_BroadcastStateFeature, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_space_size) * 4",
			/* = Setter = */     bo_Init_State,
			/* = Getter = */     bo_End_State,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Environment, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_BroadcastNextStateFeature, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_broadcastAction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_Environment, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Actor_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_GaussianPolicy, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Temporal_Difference_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_valid_actor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_gamma, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Temporal_Difference_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_sigma, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GaussianPolicy, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GaussianPolicy, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_ClipAction, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ClipAction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_broadcastAction, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_environment_limits, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(2)*4",
			/* = Snk = */       bo_ClipAction, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(2)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasActor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFireActor * actor_bias_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsActor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFireActor * actor_weights_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Environment, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbFireActor * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       bo_Temporal_Difference_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastNextStateFeature, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(nbFireActor * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsTargetCritic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Set_TargetCritic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "( critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasTargetCritic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Set_TargetCritic, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsTargetActor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_weights_size)*4",
			/* = Snk = */       bo_Set_TargetActor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasTargetActor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_Set_TargetActor, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(actor_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsActor, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(actor_weights_size)*4",
			/* = Snk = */       bo_Set_TargetActor, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(actor_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasActor, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_Set_TargetActor, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(actor_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsCritic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Set_TargetCritic, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "( critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasCritic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Set_TargetCritic, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsTargetActor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * actor_weights_size)*4",
			/* = Snk = */       bo_TargetActor_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasTargetActor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(sampleSize * actor_bias_size)*4",
			/* = Snk = */       bo_TargetActor_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsTargetCritic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * critic_weights_size)*4",
			/* = Snk = */       bo_TargetCritic_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(actionState_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * value_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasTargetCritic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(sampleSize * critic_bias_size)*4",
			/* = Snk = */       bo_TargetCritic_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + value_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinTargetActionState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * (state_space_size + action_space_size))*4",
			/* = Snk = */       bo_TargetCritic_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actionState_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_TargetActor_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_JoinTargetActionState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_TargetCritic_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(value_space_size)*4",
			/* = Snk = */       bo_Temporal_Difference_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_BroadcastSampledState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_broadcastAction, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(action_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(nbFireActor * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(sampleSize * action_space_size)*4",
			/* = Snk = */       bo_JoinActionState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastSampledState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_JoinActionState, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_actor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(sampleSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasActor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(action_space_size + hidden_size_1 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsActor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_weights_size)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(state_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_actor_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    10, 
			/* = Cons Expr = */ "(sampleSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastSampledState, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeightsCritic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(actionState_space_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * value_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBiasCritic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(value_space_size + hidden_size_1 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinActionState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * (state_space_size + action_space_size))*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(sampleSize * actionState_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(sampleSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_critic_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    9, 
			/* = Cons Expr = */ "(sampleSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Temporal_Difference_Error, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Networks, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(sampleSize * value_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_to, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastTo, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastTo, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(actor_weights_size + actor_bias_size)*4",
			/* = Snk = */       bo_Set_TargetActor, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "( actor_weights_size + actor_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastTo, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_weights_size + critic_bias_size)*4",
			/* = Snk = */       bo_Set_TargetCritic, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "( critic_weights_size + critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Fill_Buffer, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_BroadcastSampledNextState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastSampledNextState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_TargetActor_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastSampledNextState, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       bo_JoinTargetActionState, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	

	

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Fill_Buffer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(nbFireActor * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Actor_MLP
void ddpg_Actor_MLP(PiSDFVertex *bo_Actor_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     10);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Actor_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_ACTOR_MLP_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_ACTOR_MLP_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_ACTOR_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_ACTOR_MLP_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_Actor_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Actor_MLP_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Actor_MLP_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_Actor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_ACTOR_MLP_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_Actor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_ACTOR_MLP_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Fill_Buffer
void ddpg_Fill_Buffer(PiSDFVertex *bo_Fill_Buffer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    32,
		/*Params*/   7,
		/*InputIf*/  8,
		/*OutputIf*/ 8,
		/*Config*/   0,
		/*Body*/     17);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Fill_Buffer, graph);

	/* === Parameters === */

	PiSDFParam *param_sampleSize = Spider::addInheritedParam(graph, "sampleSize", 0);
	PiSDFParam *param_bufferSize = Spider::addInheritedParam(graph, "bufferSize", 1);
	PiSDFParam *param_state_space_size = Spider::addInheritedParam(graph, "state_space_size", 2);
	PiSDFParam *param_action_space_size = Spider::addInheritedParam(graph, "action_space_size", 3);
	PiSDFParam *param_nbFill = Spider::addInheritedParam(graph, "nbFill", 4);
	PiSDFParam *param_nbFilled = Spider::addStaticDependentParam(graph, "nbFilled", "bufferSize - nbFill", {param_nbFill, param_bufferSize});
	PiSDFParam *param_nbSaved = Spider::addStaticDependentParam(graph, "nbSaved", "bufferSize - sampleSize", {param_bufferSize, param_sampleSize});

	/* === Vertices === */

	PiSDFVertex* if_reward = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_reward",
		/*InParam*/ 1);
	Spider::addInParam(if_reward, 0, param_nbFill);

	PiSDFVertex* if_action = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_action",
		/*InParam*/ 2);
	Spider::addInParam(if_action, 0, param_action_space_size);
	Spider::addInParam(if_action, 1, param_nbFill);

	PiSDFVertex* if_state = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_state",
		/*InParam*/ 2);
	Spider::addInParam(if_state, 0, param_state_space_size);
	Spider::addInParam(if_state, 1, param_nbFill);

	PiSDFVertex* if_next_state = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_state",
		/*InParam*/ 2);
	Spider::addInParam(if_next_state, 0, param_state_space_size);
	Spider::addInParam(if_next_state, 1, param_nbFill);

	PiSDFVertex* if_reward_save = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_reward_save",
		/*InParam*/ 1);
	Spider::addInParam(if_reward_save, 0, param_nbSaved);

	PiSDFVertex* if_action_save = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_action_save",
		/*InParam*/ 2);
	Spider::addInParam(if_action_save, 0, param_action_space_size);
	Spider::addInParam(if_action_save, 1, param_nbSaved);

	PiSDFVertex* if_state_save = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_state_save",
		/*InParam*/ 2);
	Spider::addInParam(if_state_save, 0, param_state_space_size);
	Spider::addInParam(if_state_save, 1, param_nbSaved);

	PiSDFVertex* if_next_state_save = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_state_save",
		/*InParam*/ 2);
	Spider::addInParam(if_next_state_save, 0, param_state_space_size);
	Spider::addInParam(if_next_state_save, 1, param_nbSaved);

	PiSDFVertex* if_reward_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_reward_out",
		/*InParam*/ 1);
	Spider::addInParam(if_reward_out, 0, param_sampleSize);

	PiSDFVertex* if_action_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_action_out",
		/*InParam*/ 2);
	Spider::addInParam(if_action_out, 0, param_action_space_size);
	Spider::addInParam(if_action_out, 1, param_sampleSize);

	PiSDFVertex* if_state_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_state_out",
		/*InParam*/ 2);
	Spider::addInParam(if_state_out, 0, param_state_space_size);
	Spider::addInParam(if_state_out, 1, param_sampleSize);

	PiSDFVertex* if_next_state_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_state_out",
		/*InParam*/ 2);
	Spider::addInParam(if_next_state_out, 0, param_state_space_size);
	Spider::addInParam(if_next_state_out, 1, param_sampleSize);

	PiSDFVertex* if_reward_toSave = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_reward_toSave",
		/*InParam*/ 1);
	Spider::addInParam(if_reward_toSave, 0, param_nbSaved);

	PiSDFVertex* if_action_toSave = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_action_toSave",
		/*InParam*/ 2);
	Spider::addInParam(if_action_toSave, 0, param_action_space_size);
	Spider::addInParam(if_action_toSave, 1, param_nbSaved);

	PiSDFVertex* if_state_toSave = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_state_toSave",
		/*InParam*/ 2);
	Spider::addInParam(if_state_toSave, 0, param_state_space_size);
	Spider::addInParam(if_state_toSave, 1, param_nbSaved);

	PiSDFVertex* if_next_state_toSave = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_state_toSave",
		/*InParam*/ 2);
	Spider::addInParam(if_next_state_toSave, 0, param_state_space_size);
	Spider::addInParam(if_next_state_toSave, 1, param_nbSaved);

	PiSDFVertex* bo_JoinReward = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinReward",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinReward, 0, param_nbFill);
	Spider::addInParam(bo_JoinReward, 1, param_nbFilled);

	PiSDFVertex* bo_JoinAction = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinAction",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinAction, 0, param_action_space_size);
	Spider::addInParam(bo_JoinAction, 1, param_nbFill);
	Spider::addInParam(bo_JoinAction, 2, param_nbFilled);

	PiSDFVertex* bo_JoinState = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinState",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinState, 0, param_state_space_size);
	Spider::addInParam(bo_JoinState, 1, param_nbFill);
	Spider::addInParam(bo_JoinState, 2, param_nbFilled);

	PiSDFVertex* bo_JoinNextState = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinNextState",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinNextState, 0, param_nbFilled);
	Spider::addInParam(bo_JoinNextState, 1, param_nbFill);
	Spider::addInParam(bo_JoinNextState, 2, param_state_space_size);

	PiSDFVertex* bo_Shuffle = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Shuffle",
		/*FctId*/   DDPG_FILL_BUFFER_SHUFFLE_FCT,
		/*InData*/  4,
		/*OutData*/ 4,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Shuffle, 0, param_state_space_size);
	Spider::addInParam(bo_Shuffle, 1, param_bufferSize);
	Spider::addInParam(bo_Shuffle, 2, param_action_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Shuffle);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Shuffle, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkReward = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkReward",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkReward, 0, param_sampleSize);
	Spider::addInParam(bo_ForkReward, 1, param_nbSaved);

	PiSDFVertex* bo_ForkAction = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkAction",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkAction, 0, param_sampleSize);
	Spider::addInParam(bo_ForkAction, 1, param_action_space_size);
	Spider::addInParam(bo_ForkAction, 2, param_nbSaved);

	PiSDFVertex* bo_ForkState = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkState",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkState, 0, param_sampleSize);
	Spider::addInParam(bo_ForkState, 1, param_state_space_size);
	Spider::addInParam(bo_ForkState, 2, param_nbSaved);

	PiSDFVertex* bo_ForkNextState = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkNextState",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkNextState, 0, param_sampleSize);
	Spider::addInParam(bo_ForkNextState, 1, param_state_space_size);
	Spider::addInParam(bo_ForkNextState, 2, param_nbSaved);

	PiSDFVertex* bo_ForkStateSave = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkStateSave",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkStateSave, 0, param_state_space_size);
	Spider::addInParam(bo_ForkStateSave, 1, param_nbFilled);
	Spider::addInParam(bo_ForkStateSave, 2, param_nbSaved);

	PiSDFVertex* bo_EndStateSave = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "EndStateSave",
		/*FctId*/   DDPG_FILL_BUFFER_ENDSTATESAVE_FCT,
		/*InData*/  1,
		/*OutData*/ 0,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_EndStateSave, 0, param_state_space_size);
	Spider::addInParam(bo_EndStateSave, 1, param_nbFilled);
	Spider::addInParam(bo_EndStateSave, 2, param_nbSaved);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_EndStateSave);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_EndStateSave, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkNextStateSave = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkNextStateSave",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkNextStateSave, 0, param_state_space_size);
	Spider::addInParam(bo_ForkNextStateSave, 1, param_nbFilled);
	Spider::addInParam(bo_ForkNextStateSave, 2, param_nbSaved);

	PiSDFVertex* bo_EndNextStateSave = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "EndNextStateSave",
		/*FctId*/   DDPG_FILL_BUFFER_ENDNEXTSTATESAVE_FCT,
		/*InData*/  1,
		/*OutData*/ 0,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_EndNextStateSave, 0, param_state_space_size);
	Spider::addInParam(bo_EndNextStateSave, 1, param_nbFilled);
	Spider::addInParam(bo_EndNextStateSave, 2, param_nbSaved);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_EndNextStateSave);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_EndNextStateSave, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkRewardSave = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkRewardSave",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkRewardSave, 0, param_nbFilled);
	Spider::addInParam(bo_ForkRewardSave, 1, param_nbSaved);

	PiSDFVertex* bo_EndRewardSave = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "EndRewardSave",
		/*FctId*/   DDPG_FILL_BUFFER_ENDREWARDSAVE_FCT,
		/*InData*/  1,
		/*OutData*/ 0,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_EndRewardSave, 0, param_nbFilled);
	Spider::addInParam(bo_EndRewardSave, 1, param_nbSaved);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_EndRewardSave);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_EndRewardSave, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_EndActionSave = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "EndActionSave",
		/*FctId*/   DDPG_FILL_BUFFER_ENDACTIONSAVE_FCT,
		/*InData*/  1,
		/*OutData*/ 0,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_EndActionSave, 0, param_nbFilled);
	Spider::addInParam(bo_EndActionSave, 1, param_nbSaved);
	Spider::addInParam(bo_EndActionSave, 2, param_action_space_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_EndActionSave);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_EndActionSave, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkActionSave = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkActionSave",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkActionSave, 0, param_nbFilled);
	Spider::addInParam(bo_ForkActionSave, 1, param_nbSaved);
	Spider::addInParam(bo_ForkActionSave, 2, param_action_space_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_reward, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFill * 1)*4",
			/* = Snk = */       bo_JoinReward, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbFill * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_state, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFill * state_space_size)*4",
			/* = Snk = */       bo_JoinState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbFill * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_state, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFill * state_space_size)*4",
			/* = Snk = */       bo_JoinNextState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbFill * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_action, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFill * action_space_size)*4",
			/* = Snk = */       bo_JoinAction, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbFill * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinAction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "((nbFill + nbFilled) * action_space_size)*4",
			/* = Snk = */       bo_Shuffle, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bufferSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinNextState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "((nbFill + nbFilled) * state_space_size)*4",
			/* = Snk = */       bo_Shuffle, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(bufferSize * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinReward, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "((nbFill + nbFilled) * 1)*4",
			/* = Snk = */       bo_Shuffle, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(bufferSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "((nbFill + nbFilled) * state_space_size)*4",
			/* = Snk = */       bo_Shuffle, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(bufferSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Shuffle, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bufferSize * 1)*4",
			/* = Snk = */       bo_ForkReward, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((sampleSize + nbSaved) * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Shuffle, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(bufferSize * action_space_size)*4",
			/* = Snk = */       bo_ForkAction, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((sampleSize + nbSaved) * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Shuffle, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(bufferSize * state_space_size)*4",
			/* = Snk = */       bo_ForkState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((sampleSize + nbSaved) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Shuffle, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(bufferSize * state_space_size)*4",
			/* = Snk = */       bo_ForkNextState, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((sampleSize + nbSaved) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkReward, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       if_reward_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkReward, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(nbSaved * 1)*4",
			/* = Snk = */       if_reward_toSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkAction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * action_space_size)*4",
			/* = Snk = */       if_action_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkAction, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(nbSaved * action_space_size)*4",
			/* = Snk = */       if_action_toSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       if_state_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkState, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(nbSaved * state_space_size)*4",
			/* = Snk = */       if_state_toSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkNextState, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * state_space_size)*4",
			/* = Snk = */       if_next_state_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(sampleSize * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkNextState, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(nbSaved * state_space_size)*4",
			/* = Snk = */       if_next_state_toSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_state_save, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbSaved * state_space_size)*4",
			/* = Snk = */       bo_ForkStateSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkStateSave, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFilled * state_space_size)*4",
			/* = Snk = */       bo_JoinState, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(nbFilled * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkStateSave, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "((nbSaved - nbFilled) * state_space_size)*4",
			/* = Snk = */       bo_EndStateSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((nbSaved - nbFilled) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkNextStateSave, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "((nbSaved - nbFilled) * state_space_size)*4",
			/* = Snk = */       bo_EndNextStateSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((nbSaved - nbFilled) * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_state_save, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbSaved * state_space_size)*4",
			/* = Snk = */       bo_ForkNextStateSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkNextStateSave, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFilled * state_space_size)*4",
			/* = Snk = */       bo_JoinNextState, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(nbFilled * state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkRewardSave, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "((nbSaved - nbFilled) * 1)*4",
			/* = Snk = */       bo_EndRewardSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((nbSaved - nbFilled) * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_reward_save, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbSaved * 1)*4",
			/* = Snk = */       bo_ForkRewardSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkRewardSave, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFilled * 1)*4",
			/* = Snk = */       bo_JoinReward, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(nbFilled * 1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkActionSave, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "((nbSaved - nbFilled) * action_space_size)*4",
			/* = Snk = */       bo_EndActionSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "((nbSaved - nbFilled) * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_action_save, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbSaved * action_space_size)*4",
			/* = Snk = */       bo_ForkActionSave, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(nbSaved * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkActionSave, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(nbFilled * action_space_size)*4",
			/* = Snk = */       bo_JoinAction, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(nbFilled * action_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: TargetActor_MLP
void ddpg_TargetActor_MLP(PiSDFVertex *bo_TargetActor_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     10);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_TargetActor_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_TARGETACTOR_MLP_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_TARGETACTOR_MLP_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_TARGETACTOR_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_TARGETACTOR_MLP_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_TargetActor_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_TargetActor_MLP_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_TargetActor_MLP_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_TargetActor_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_TargetActor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETACTOR_MLP_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_TargetActor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETACTOR_MLP_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: TargetCritic_MLP
void ddpg_TargetCritic_MLP(PiSDFVertex *bo_TargetCritic_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     10);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_TargetCritic_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_TargetCritic_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_TargetCritic_MLP_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_TargetCritic_MLP_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_TargetCritic_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_TargetCritic_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_TargetCritic_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_TARGETCRITIC_MLP_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Set_TargetActor
void ddpg_Set_TargetActor(PiSDFVertex *bo_Set_TargetActor){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    9,
		/*Params*/   2,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     3);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Set_TargetActor, graph);

	/* === Parameters === */

	PiSDFParam *param_weights_size = Spider::addInheritedParam(graph, "weights_size", 0);
	PiSDFParam *param_bias_size = Spider::addInheritedParam(graph, "bias_size", 1);

	/* === Vertices === */

	PiSDFVertex* if_weights_network = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_network",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_network, 0, param_weights_size);

	PiSDFVertex* if_weights_to_reach = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_to_reach",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_to_reach, 0, param_weights_size);

	PiSDFVertex* if_bias_network = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_network",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_network, 0, param_bias_size);

	PiSDFVertex* if_bias_to_reach = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_to_reach",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_to_reach, 0, param_bias_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_bias_size);

	PiSDFVertex* bo_SetWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "SetWeights",
		/*FctId*/   DDPG_SET_TARGETACTOR_SETWEIGHTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_SetWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_SetWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_SetBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "SetBias",
		/*FctId*/   DDPG_SET_TARGETACTOR_SETBIAS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_SetBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_SetBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_to = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_to",
		/*InParam*/ 2);
	Spider::addInParam(if_to, 0, param_weights_size);
	Spider::addInParam(if_to, 1, param_bias_size);

	PiSDFVertex* bo_ForkTo = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkTo",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkTo, 0, param_weights_size);
	Spider::addInParam(bo_ForkTo, 1, param_bias_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights_to_reach, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights_network, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_SetWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_to_reach, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_network, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_SetBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_to, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + bias_size)*4",
			/* = Snk = */       bo_ForkTo, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size + bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkTo, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkTo, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Set_TargetCritic
void ddpg_Set_TargetCritic(PiSDFVertex *bo_Set_TargetCritic){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    9,
		/*Params*/   2,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     3);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Set_TargetCritic, graph);

	/* === Parameters === */

	PiSDFParam *param_weights_size = Spider::addInheritedParam(graph, "weights_size", 0);
	PiSDFParam *param_bias_size = Spider::addInheritedParam(graph, "bias_size", 1);

	/* === Vertices === */

	PiSDFVertex* if_weights_network = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_network",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_network, 0, param_weights_size);

	PiSDFVertex* if_weights_to_reach = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_to_reach",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_to_reach, 0, param_weights_size);

	PiSDFVertex* if_bias_network = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_network",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_network, 0, param_bias_size);

	PiSDFVertex* if_bias_to_reach = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_to_reach",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_to_reach, 0, param_bias_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_bias_size);

	PiSDFVertex* bo_SetWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "SetWeights",
		/*FctId*/   DDPG_SET_TARGETCRITIC_SETWEIGHTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_SetWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_SetWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_SetBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "SetBias",
		/*FctId*/   DDPG_SET_TARGETCRITIC_SETBIAS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_SetBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_SetBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_to = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_to",
		/*InParam*/ 2);
	Spider::addInParam(if_to, 0, param_weights_size);
	Spider::addInParam(if_to, 1, param_bias_size);

	PiSDFVertex* bo_ForkTo = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkTo",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkTo, 0, param_weights_size);
	Spider::addInParam(bo_ForkTo, 1, param_bias_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights_to_reach, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights_network, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_SetWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_to_reach, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_network, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_SetBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_to, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + bias_size)*4",
			/* = Snk = */       bo_ForkTo, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size + bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkTo, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_SetBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkTo, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_SetWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Update_Networks
void ddpg_Update_Networks(PiSDFVertex *bo_Update_Networks){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    23,
		/*Params*/   11,
		/*InputIf*/  11,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     8);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Update_Networks, graph);

	/* === Parameters === */

	PiSDFParam *param_sampleSize = Spider::addInheritedParam(graph, "sampleSize", 0);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 1);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 2);
	PiSDFParam *param_critic_output_size = Spider::addInheritedParam(graph, "critic_output_size", 3);
	PiSDFParam *param_critic_input_size = Spider::addInheritedParam(graph, "critic_input_size", 4);
	PiSDFParam *param_actor_output_size = Spider::addInheritedParam(graph, "actor_output_size", 5);
	PiSDFParam *param_actor_input_size = Spider::addInheritedParam(graph, "actor_input_size", 6);
	PiSDFParam *param_critic_weights_size = Spider::addStaticDependentParam(graph, "critic_weights_size", "critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size", {param_critic_input_size, param_critic_output_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_critic_bias_size = Spider::addStaticDependentParam(graph, "critic_bias_size", "hidden_size_0 + hidden_size_1 + critic_output_size", {param_critic_output_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_actor_bias_size = Spider::addStaticDependentParam(graph, "actor_bias_size", "hidden_size_0 + hidden_size_1 + actor_output_size", {param_hidden_size_0, param_hidden_size_1, param_actor_output_size});
	PiSDFParam *param_actor_weights_size = Spider::addStaticDependentParam(graph, "actor_weights_size", "actor_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * actor_output_size", {param_actor_output_size, param_actor_input_size, param_hidden_size_0, param_hidden_size_1});

	/* === Vertices === */

	PiSDFVertex* if_actor_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_actor_input",
		/*InParam*/ 2);
	Spider::addInParam(if_actor_input, 0, param_actor_input_size);
	Spider::addInParam(if_actor_input, 1, param_sampleSize);

	PiSDFVertex* if_weights_critic = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_critic",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_critic, 0, param_critic_weights_size);

	PiSDFVertex* if_bias_critic = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_critic",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_critic, 0, param_critic_bias_size);

	PiSDFVertex* if_weights_actor = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_actor",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_actor, 0, param_actor_weights_size);

	PiSDFVertex* if_bias_actor = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_actor",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_actor, 0, param_actor_bias_size);

	PiSDFVertex* if_critic_target = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_critic_target",
		/*InParam*/ 2);
	Spider::addInParam(if_critic_target, 0, param_sampleSize);
	Spider::addInParam(if_critic_target, 1, param_critic_output_size);

	PiSDFVertex* if_critic_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_critic_input",
		/*InParam*/ 2);
	Spider::addInParam(if_critic_input, 0, param_sampleSize);
	Spider::addInParam(if_critic_input, 1, param_critic_input_size);

	PiSDFVertex* if_weights_critic_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_critic_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_critic_out, 0, param_critic_weights_size);

	PiSDFVertex* if_bias_critic_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_critic_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_critic_out, 0, param_critic_bias_size);

	PiSDFVertex* if_weights_actor_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_actor_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_actor_out, 0, param_actor_weights_size);

	PiSDFVertex* if_bias_actor_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_actor_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_actor_out, 0, param_actor_bias_size);

	PiSDFVertex* if_valid_critic = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid_critic",
		/*InParam*/ 1);
	Spider::addInParam(if_valid_critic, 0, param_sampleSize);

	PiSDFVertex* if_valid_actor = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid_actor",
		/*InParam*/ 1);
	Spider::addInParam(if_valid_actor, 0, param_sampleSize);

	PiSDFVertex* if_critic_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_critic_learning_rate",
		/*InParam*/ 1);
	Spider::addInParam(if_critic_learning_rate, 0, param_sampleSize);

	PiSDFVertex* if_actor_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_actor_learning_rate",
		/*InParam*/ 1);
	Spider::addInParam(if_actor_learning_rate, 0, param_sampleSize);

	PiSDFVertex* bo_BroadcastCriticWeights = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastCriticWeights",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastCriticWeights, 0, param_critic_weights_size);

	PiSDFVertex* bo_BroadcastCriticBias = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastCriticBias",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastCriticBias, 0, param_critic_bias_size);

	PiSDFVertex* bo_Update_Actor = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Update_Actor",
		/*FctId*/   -1,
		/*InData*/  7,
		/*OutData*/ 2,
		/*InParam*/ 6);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Update_Actor, 0, param_actor_input_size);
	Spider::addInParam(bo_Update_Actor, 1, param_hidden_size_1);
	Spider::addInParam(bo_Update_Actor, 2, param_actor_output_size);
	Spider::addInParam(bo_Update_Actor, 3, param_hidden_size_0);
	Spider::addInParam(bo_Update_Actor, 4, param_critic_output_size);
	Spider::addInParam(bo_Update_Actor, 5, param_critic_input_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor(bo_Update_Actor);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Update_Actor, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Update_Critic = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Update_Critic",
		/*FctId*/   -1,
		/*InData*/  6,
		/*OutData*/ 2,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Update_Critic, 0, param_critic_input_size);
	Spider::addInParam(bo_Update_Critic, 1, param_hidden_size_1);
	Spider::addInParam(bo_Update_Critic, 2, param_critic_output_size);
	Spider::addInParam(bo_Update_Critic, 3, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic(bo_Update_Critic);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Update_Critic, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Actor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(actor_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * actor_output_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(actor_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * actor_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_weights_size) * 4",
			/* = Setter = */     if_weights_actor,
			/* = Getter = */     if_weights_actor_out,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Actor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_output_size + hidden_size_1 + hidden_size_0)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(actor_output_size + hidden_size_1 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(actor_bias_size) * 4",
			/* = Setter = */     if_bias_actor,
			/* = Getter = */     if_bias_actor_out,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(critic_output_size + hidden_size_1 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size)*4",
			/* = Snk = */       bo_BroadcastCriticWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_weights_size) * 4",
			/* = Setter = */     if_weights_critic,
			/* = Getter = */     if_weights_critic_out,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Critic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_output_size + hidden_size_1 + hidden_size_0)*4",
			/* = Snk = */       bo_BroadcastCriticBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(critic_bias_size)*4",
			/* = Setter = */     if_bias_critic,
			/* = Getter = */     if_bias_critic_out,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid_actor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_actor_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * actor_input_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(actor_input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_critic_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * critic_input_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(critic_input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_critic_target, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * critic_output_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid_critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_actor_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_critic_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(sampleSize * 1)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(critic_output_size + hidden_size_1 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	

	

	

	

	

	

	

	
}

// Method building PiSDFGraph: Update_Actor
void ddpg_Update_Networks_Update_Actor(PiSDFVertex *bo_Update_Actor){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    82,
		/*Params*/   13,
		/*InputIf*/  7,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     38);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Update_Actor, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 1);
	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 2);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 3);
	PiSDFParam *param_critic_output_size = Spider::addInheritedParam(graph, "critic_output_size", 4);
	PiSDFParam *param_critic_input_size = Spider::addInheritedParam(graph, "critic_input_size", 5);
	PiSDFParam *param_bias_size = Spider::addStaticDependentParam(graph, "bias_size", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_1, param_output_size, param_hidden_size_0});
	PiSDFParam *param_hidden_weights_size_1 = Spider::addStaticDependentParam(graph, "hidden_weights_size_1", "hidden_size_0 * hidden_size_1", {param_hidden_size_1, param_hidden_size_0});
	PiSDFParam *param_output_weights_size = Spider::addStaticDependentParam(graph, "output_weights_size", "hidden_size_1 * output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_hidden_weights_size_0 = Spider::addStaticDependentParam(graph, "hidden_weights_size_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_critic_bias_size = Spider::addStaticDependentParam(graph, "critic_bias_size", "hidden_size_0 + hidden_size_1 + critic_output_size", {param_critic_input_size, param_critic_output_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_critic_weights_size = Spider::addStaticDependentParam(graph, "critic_weights_size", "critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size", {param_critic_input_size, param_critic_output_size, param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "hidden_weights_size_0 + hidden_weights_size_1 + output_weights_size", {param_hidden_weights_size_0, param_hidden_weights_size_1, param_output_weights_size});

	/* === Vertices === */

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_bias_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_bias_size);

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 4);
	Spider::addInParam(bo_ForkWeights, 0, param_weights_size);
	Spider::addInParam(bo_ForkWeights, 1, param_hidden_weights_size_0);
	Spider::addInParam(bo_ForkWeights, 2, param_hidden_weights_size_1);
	Spider::addInParam(bo_ForkWeights, 3, param_output_weights_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 4);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);
	Spider::addInParam(bo_ForkBias, 2, param_bias_size);
	Spider::addInParam(bo_ForkBias, 3, param_hidden_size_0);

	PiSDFVertex* bo_JoinWeights = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinWeights",
		/*InData*/  3,
		/*InParam*/ 4);
	Spider::addInParam(bo_JoinWeights, 0, param_weights_size);
	Spider::addInParam(bo_JoinWeights, 1, param_hidden_weights_size_1);
	Spider::addInParam(bo_JoinWeights, 2, param_output_weights_size);
	Spider::addInParam(bo_JoinWeights, 3, param_hidden_weights_size_0);

	PiSDFVertex* bo_JoinBias = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinBias",
		/*InData*/  3,
		/*InParam*/ 4);
	Spider::addInParam(bo_JoinBias, 0, param_bias_size);
	Spider::addInParam(bo_JoinBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_JoinBias, 2, param_output_size);
	Spider::addInParam(bo_JoinBias, 3, param_hidden_size_0);

	PiSDFVertex* bo_BroadcastWeights = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights, 0, param_weights_size);

	PiSDFVertex* bo_BroadcastBias = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBias",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastBias, 0, param_bias_size);

	PiSDFVertex* bo_BroadcastInput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastInput",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastInput, 0, param_input_size);

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 7,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastWeights_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_output, 0, param_output_weights_size);

	PiSDFVertex* bo_JoinGradients_hidden_1 = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden_1",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden_1, 0, param_hidden_weights_size_1);
	Spider::addInParam(bo_JoinGradients_hidden_1, 1, param_hidden_size_1);

	PiSDFVertex* bo_JoinGradients_output = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_output",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_output, 0, param_hidden_size_1);
	Spider::addInParam(bo_JoinGradients_output, 1, param_output_size);

	PiSDFVertex* bo_BroadcastErrors_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastErrors_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastErrors_output, 0, param_output_size);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_gen_epsilon = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_epsilon",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GEN_EPSILON_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_epsilon);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_epsilon, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_adamBetas = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "adamBetas",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMBETAS_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_adamBetas);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_adamBetas, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 4,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastErrors_layer_1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastErrors_layer_1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastErrors_layer_1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastWeights_hidden_1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_hidden_1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_hidden_1, 0, param_hidden_weights_size_1);

	PiSDFVertex* bo_JoinGradients_hidden_0 = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden_0",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden_0, 0, param_hidden_weights_size_0);
	Spider::addInParam(bo_JoinGradients_hidden_0, 1, param_hidden_size_0);

	PiSDFVertex* if_weights_critic = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_critic",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_critic, 0, param_critic_weights_size);

	PiSDFVertex* if_bias_critic = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_critic",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_critic, 0, param_critic_bias_size);

	PiSDFVertex* bo_JoinCriticInput = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinCriticInput",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinCriticInput, 0, param_output_size);
	Spider::addInParam(bo_JoinCriticInput, 1, param_input_size);

	PiSDFVertex* bo_BroadcastCriticWeights = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastCriticWeights",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastCriticWeights, 0, param_critic_weights_size);

	PiSDFVertex* bo_BroadcastCriticBias = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastCriticBias",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastCriticBias, 0, param_critic_bias_size);

	PiSDFVertex* bo_AdamOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamOutput",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamOutput, 0, param_output_size);
	Spider::addInParam(bo_AdamOutput, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_AdamOutput(bo_AdamOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden_1",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden_1, 0, param_hidden_size_1);
	Spider::addInParam(bo_AdamHidden_1, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_AdamHidden_1(bo_AdamHidden_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 6,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_MLP, 0, param_output_size);
	Spider::addInParam(bo_MLP, 1, param_input_size);
	Spider::addInParam(bo_MLP, 2, param_hidden_size_0);
	Spider::addInParam(bo_MLP, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_MLP(bo_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden_1",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden_1, 0, param_hidden_size_1);
	Spider::addInParam(bo_GradientsHidden_1, 1, param_output_size);
	Spider::addInParam(bo_GradientsHidden_1, 2, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_GradientsHidden_1(bo_GradientsHidden_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsOutput",
		/*FctId*/   -1,
		/*InData*/  6,
		/*OutData*/ 2,
		/*InParam*/ 8);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsOutput, 0, param_output_size);
	Spider::addInParam(bo_GradientsOutput, 1, param_hidden_size_1);
	Spider::addInParam(bo_GradientsOutput, 2, param_hidden_size_0);
	Spider::addInParam(bo_GradientsOutput, 3, param_hidden_size_1);
	Spider::addInParam(bo_GradientsOutput, 4, param_critic_input_size);
	Spider::addInParam(bo_GradientsOutput, 5, param_critic_weights_size);
	Spider::addInParam(bo_GradientsOutput, 6, param_critic_bias_size);
	Spider::addInParam(bo_GradientsOutput, 7, param_critic_output_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_GradientsOutput(bo_GradientsOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden_0",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden_0, 0, param_hidden_size_0);
	Spider::addInParam(bo_GradientsHidden_0, 1, param_hidden_size_1);
	Spider::addInParam(bo_GradientsHidden_0, 2, param_input_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_GradientsHidden_0(bo_GradientsHidden_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden_0",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden_0, 0, param_hidden_size_0);
	Spider::addInParam(bo_AdamHidden_0, 1, param_input_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_AdamHidden_0(bo_AdamHidden_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Critic = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Critic",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Critic, 0, param_critic_output_size);
	Spider::addInParam(bo_Critic, 1, param_critic_input_size);
	Spider::addInParam(bo_Critic, 2, param_hidden_size_0);
	Spider::addInParam(bo_Critic, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_Critic(bo_Critic);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Critic, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_1 + hidden_size_1) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_1 + hidden_size_1) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(output_weights_size + output_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(output_weights_size + output_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_adamBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(4) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_0 + hidden_size_0) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_0 + hidden_size_0) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    5, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_BroadcastWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_BroadcastBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_BroadcastInput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_output, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_hidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 + hidden_weights_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastErrors_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_output, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_adamBetas, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_adamBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1)*4",
			/* = Snk = */       bo_JoinGradients_hidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_BroadcastErrors_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_JoinGradients_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_layer_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_hidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_hidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    5, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_BroadcastWeights_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_BroadcastWeights_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    6, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_JoinGradients_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size_0)*4",
			/* = Snk = */       bo_JoinGradients_hidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_hidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 + hidden_weights_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(input_size * hidden_size_0)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_JoinCriticInput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinCriticInput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinCriticInput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size + output_size)*4",
			/* = Snk = */       bo_Critic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_output_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights_critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_BroadcastCriticWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_BroadcastCriticBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Critic, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(critic_input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Critic, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + critic_output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastCriticBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamOutput
void ddpg_Update_Networks_Update_Actor_AdamOutput(PiSDFVertex *bo_AdamOutput){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamOutput, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamHidden_1
void ddpg_Update_Networks_Update_Actor_AdamHidden_1(PiSDFVertex *bo_AdamHidden_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden_1, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMHIDDEN_1_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMHIDDEN_1_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: MLP
void ddpg_Update_Networks_Update_Actor_MLP(PiSDFVertex *bo_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 6,
		/*Config*/   0,
		/*Body*/     15);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_raw_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_hidden_0 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden_0",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden_0, 0, param_hidden_size_0);

	PiSDFVertex* if_raw_hidden_0 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden_0",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden_0, 0, param_hidden_size_0);

	PiSDFVertex* if_hidden_1 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden_1",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden_1, 0, param_hidden_size_1);

	PiSDFVertex* if_raw_hidden_1 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden_1",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden_1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastRawOutput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawOutput",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawOutput, 0, param_output_size);

	PiSDFVertex* bo_BroadcastHidden1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastRawHidden1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastHidden0 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden0",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden0, 0, param_hidden_size_0);

	PiSDFVertex* bo_BroadcastRawHidden0 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden0",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden0, 0, param_hidden_size_0);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1+size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastRawOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       if_raw_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_BroadcastRawHidden1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       if_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       if_raw_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       if_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_BroadcastRawHidden0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       if_raw_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_Update_Networks_Update_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_Update_Networks_Update_Actor_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_MLP_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsHidden_1
void ddpg_Update_Networks_Update_Actor_GradientsHidden_1(PiSDFVertex *bo_GradientsHidden_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden_1, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_next_layer_size = Spider::addInheritedParam(graph, "next_layer_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);

	/* === Vertices === */

	PiSDFVertex* if_raw_hidden = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_layer_size);

	PiSDFVertex* if_next_layer_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_next_layer_weights, 0, param_next_layer_size);
	Spider::addInParam(if_next_layer_weights, 1, param_layer_size);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_input_size);
	Spider::addInParam(if_weights_gradient, 1, param_layer_size);

	PiSDFVertex* if_next_layer_errors = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_errors",
		/*InParam*/ 1);
	Spider::addInParam(if_next_layer_errors, 0, param_next_layer_size);

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_1_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_layer_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_layer_size);

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* bo_BackPropagated_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "BackPropagated_Error",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_1_BACKPROPAGATED_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_BackPropagated_Error, 0, param_layer_size);
	Spider::addInParam(bo_BackPropagated_Error, 1, param_next_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_BackPropagated_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_BackPropagated_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_1_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_errors, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size * layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size * next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BackPropagated_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsOutput
void ddpg_Update_Networks_Update_Actor_GradientsOutput(PiSDFVertex *bo_GradientsOutput){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    9,
		/*Params*/   8,
		/*InputIf*/  6,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     3);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsOutput, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_critic_input_size = Spider::addInheritedParam(graph, "critic_input_size", 4);
	PiSDFParam *param_critic_weights_size = Spider::addInheritedParam(graph, "critic_weights_size", 5);
	PiSDFParam *param_critic_bias_size = Spider::addInheritedParam(graph, "critic_bias_size", 6);
	PiSDFParam *param_critic_output_size = Spider::addInheritedParam(graph, "critic_output_size", 7);

	/* === Vertices === */

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_output_size);
	Spider::addInParam(if_weights_gradient, 1, param_input_size);

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSOUTPUT_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_output_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 7);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Derivative_Function, 0, param_output_size);
	Spider::addInParam(bo_Derivative_Function, 1, param_input_size);
	Spider::addInParam(bo_Derivative_Function, 2, param_hidden_size_0);
	Spider::addInParam(bo_Derivative_Function, 3, param_hidden_size_1);
	Spider::addInParam(bo_Derivative_Function, 4, param_critic_weights_size);
	Spider::addInParam(bo_Derivative_Function, 5, param_critic_bias_size);
	Spider::addInParam(bo_Derivative_Function, 6, param_critic_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_output_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_output_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_raw_output = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_output = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_critic_output_size);

	PiSDFVertex* if_critic_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_critic_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_critic_weights, 0, param_critic_weights_size);

	PiSDFVertex* if_critic_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_critic_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_critic_bias, 0, param_critic_bias_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "( input_size * output_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size  * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_critic_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(critic_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_critic_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(critic_bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsHidden_0
void ddpg_Update_Networks_Update_Actor_GradientsHidden_0(PiSDFVertex *bo_GradientsHidden_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden_0, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_next_layer_size = Spider::addInheritedParam(graph, "next_layer_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);

	/* === Vertices === */

	PiSDFVertex* if_raw_hidden = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_layer_size);

	PiSDFVertex* if_next_layer_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_next_layer_weights, 0, param_next_layer_size);
	Spider::addInParam(if_next_layer_weights, 1, param_layer_size);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_input_size);
	Spider::addInParam(if_weights_gradient, 1, param_layer_size);

	PiSDFVertex* if_next_layer_errors = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_errors",
		/*InParam*/ 1);
	Spider::addInParam(if_next_layer_errors, 0, param_next_layer_size);

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_0_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_layer_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_layer_size);

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* bo_BackPropagated_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "BackPropagated_Error",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_0_BACKPROPAGATED_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_BackPropagated_Error, 0, param_layer_size);
	Spider::addInParam(bo_BackPropagated_Error, 1, param_next_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_BackPropagated_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_BackPropagated_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_GRADIENTSHIDDEN_0_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_errors, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size * layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size * next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BackPropagated_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamHidden_0
void ddpg_Update_Networks_Update_Actor_AdamHidden_0(PiSDFVertex *bo_AdamHidden_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden_0, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMHIDDEN_0_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_ADAMHIDDEN_0_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Critic
void ddpg_Update_Networks_Update_Actor_Critic(PiSDFVertex *bo_Critic){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     10);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Critic, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_Critic_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_Update_Networks_Update_Actor_Critic_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_Update_Networks_Update_Actor_Critic_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_ACTOR_CRITIC_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Update_Critic
void ddpg_Update_Networks_Update_Critic(PiSDFVertex *bo_Update_Critic){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    74,
		/*Params*/   9,
		/*InputIf*/  6,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     34);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Update_Critic, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 1);
	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 2);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 3);
	PiSDFParam *param_bias_size = Spider::addStaticDependentParam(graph, "bias_size", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_1, param_output_size, param_hidden_size_0});
	PiSDFParam *param_hidden_weights_size_1 = Spider::addStaticDependentParam(graph, "hidden_weights_size_1", "hidden_size_0 * hidden_size_1", {param_hidden_size_1, param_hidden_size_0});
	PiSDFParam *param_output_weights_size = Spider::addStaticDependentParam(graph, "output_weights_size", "hidden_size_1 * output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_hidden_weights_size_0 = Spider::addStaticDependentParam(graph, "hidden_weights_size_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "hidden_weights_size_0 + hidden_weights_size_1 + output_weights_size", {param_hidden_weights_size_0, param_hidden_weights_size_1, param_output_weights_size});

	/* === Vertices === */

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_bias_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_bias_size);

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 4);
	Spider::addInParam(bo_ForkWeights, 0, param_weights_size);
	Spider::addInParam(bo_ForkWeights, 1, param_hidden_weights_size_0);
	Spider::addInParam(bo_ForkWeights, 2, param_hidden_weights_size_1);
	Spider::addInParam(bo_ForkWeights, 3, param_output_weights_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 4);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);
	Spider::addInParam(bo_ForkBias, 2, param_bias_size);
	Spider::addInParam(bo_ForkBias, 3, param_hidden_size_0);

	PiSDFVertex* bo_JoinWeights = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinWeights",
		/*InData*/  3,
		/*InParam*/ 4);
	Spider::addInParam(bo_JoinWeights, 0, param_weights_size);
	Spider::addInParam(bo_JoinWeights, 1, param_hidden_weights_size_1);
	Spider::addInParam(bo_JoinWeights, 2, param_output_weights_size);
	Spider::addInParam(bo_JoinWeights, 3, param_hidden_weights_size_0);

	PiSDFVertex* bo_JoinBias = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinBias",
		/*InData*/  3,
		/*InParam*/ 4);
	Spider::addInParam(bo_JoinBias, 0, param_bias_size);
	Spider::addInParam(bo_JoinBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_JoinBias, 2, param_output_size);
	Spider::addInParam(bo_JoinBias, 3, param_hidden_size_0);

	PiSDFVertex* bo_BroadcastWeights = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights, 0, param_weights_size);

	PiSDFVertex* bo_BroadcastBias = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBias",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastBias, 0, param_bias_size);

	PiSDFVertex* bo_BroadcastInput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastInput",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastInput, 0, param_input_size);

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 7,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastWeights_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_output, 0, param_output_weights_size);

	PiSDFVertex* bo_JoinGradients_hidden_1 = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden_1",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden_1, 0, param_hidden_weights_size_1);
	Spider::addInParam(bo_JoinGradients_hidden_1, 1, param_hidden_size_1);

	PiSDFVertex* bo_JoinGradients_output = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_output",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_output, 0, param_hidden_size_1);
	Spider::addInParam(bo_JoinGradients_output, 1, param_output_size);

	PiSDFVertex* bo_BroadcastErrors_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastErrors_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastErrors_output, 0, param_output_size);

	PiSDFVertex* if_targets = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_targets",
		/*InParam*/ 1);
	Spider::addInParam(if_targets, 0, param_output_size);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_gen_epsilon = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_epsilon",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GEN_EPSILON_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_epsilon);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_epsilon, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_adamBetas = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "adamBetas",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMBETAS_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_adamBetas);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_adamBetas, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 4,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastErrors_layer_1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastErrors_layer_1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastErrors_layer_1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastWeights_hidden_1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_hidden_1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_hidden_1, 0, param_hidden_weights_size_1);

	PiSDFVertex* bo_JoinGradients_hidden_0 = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden_0",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden_0, 0, param_hidden_weights_size_0);
	Spider::addInParam(bo_JoinGradients_hidden_0, 1, param_hidden_size_0);

	PiSDFVertex* bo_AdamOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamOutput",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamOutput, 0, param_output_size);
	Spider::addInParam(bo_AdamOutput, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_AdamOutput(bo_AdamOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden_1",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden_1, 0, param_hidden_size_1);
	Spider::addInParam(bo_AdamHidden_1, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_AdamHidden_1(bo_AdamHidden_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 6,
		/*InParam*/ 4);
	/* == Adding input parameters == */
	Spider::addInParam(bo_MLP, 0, param_output_size);
	Spider::addInParam(bo_MLP, 1, param_input_size);
	Spider::addInParam(bo_MLP, 2, param_hidden_size_0);
	Spider::addInParam(bo_MLP, 3, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_MLP(bo_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden_1",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden_1, 0, param_hidden_size_1);
	Spider::addInParam(bo_GradientsHidden_1, 1, param_output_size);
	Spider::addInParam(bo_GradientsHidden_1, 2, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_GradientsHidden_1(bo_GradientsHidden_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsOutput",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsOutput, 0, param_output_size);
	Spider::addInParam(bo_GradientsOutput, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_GradientsOutput(bo_GradientsOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden_0",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden_0, 0, param_hidden_size_0);
	Spider::addInParam(bo_GradientsHidden_0, 1, param_hidden_size_1);
	Spider::addInParam(bo_GradientsHidden_0, 2, param_input_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_GradientsHidden_0(bo_GradientsHidden_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden_0",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden_0, 0, param_hidden_size_0);
	Spider::addInParam(bo_AdamHidden_0, 1, param_input_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_AdamHidden_0(bo_AdamHidden_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_1 + hidden_size_1) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_1 + hidden_size_1) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(output_weights_size + output_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(output_weights_size + output_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_adamBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(4) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_0 + hidden_size_0) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size_0 + hidden_size_0) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    5, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0 * hidden_size_1 + hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_BroadcastWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_BroadcastBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(bias_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(bias_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_BroadcastInput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_output, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_hidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 + hidden_weights_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1 + hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size + output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastErrors_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_output, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_targets, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_gen_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_adamBetas, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_adamBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1)*4",
			/* = Snk = */       bo_JoinGradients_hidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_GradientsHidden_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_BroadcastErrors_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_JoinGradients_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastErrors_layer_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_hidden_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastWeights_hidden_1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    5, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_GradientsHidden_0, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_weights_size)*4",
			/* = Snk = */       bo_BroadcastWeights_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_weights_size_1)*4",
			/* = Snk = */       bo_BroadcastWeights_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_AdamHidden_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    8, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    6, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_JoinGradients_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size_0)*4",
			/* = Snk = */       bo_JoinGradients_hidden_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinGradients_hidden_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0 + hidden_weights_size_0)*4",
			/* = Snk = */       bo_AdamHidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * hidden_size_0 + hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(input_size * hidden_size_0)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_0 * hidden_size_1)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(hidden_size_1 * output_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_0, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden_1, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamOutput
void ddpg_Update_Networks_Update_Critic_AdamOutput(PiSDFVertex *bo_AdamOutput){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamOutput, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamHidden_1
void ddpg_Update_Networks_Update_Critic_AdamHidden_1(PiSDFVertex *bo_AdamHidden_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden_1, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMHIDDEN_1_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMHIDDEN_1_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: MLP
void ddpg_Update_Networks_Update_Critic_MLP(PiSDFVertex *bo_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   9,
		/*InputIf*/  3,
		/*OutputIf*/ 6,
		/*Config*/   0,
		/*Body*/     15);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_hidden_size_0 = Spider::addInheritedParam(graph, "hidden_size_0", 2);
	PiSDFParam *param_hidden_size_1 = Spider::addInheritedParam(graph, "hidden_size_1", 3);
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "hidden_size_1*output_size", {param_output_size, param_hidden_size_1});
	PiSDFParam *param_size_weights_hidden_0 = Spider::addStaticDependentParam(graph, "size_weights_hidden_0", "input_size * hidden_size_0", {param_hidden_size_0, param_input_size});
	PiSDFParam *param_size_weights_hidden_1 = Spider::addStaticDependentParam(graph, "size_weights_hidden_1", "hidden_size_0*hidden_size_1", {param_hidden_size_0, param_hidden_size_1});
	PiSDFParam *param_size_bias = Spider::addStaticDependentParam(graph, "size_bias", "hidden_size_0 + hidden_size_1 + output_size", {param_hidden_size_0, param_hidden_size_1, param_output_size});
	PiSDFParam *param_size_weights = Spider::addStaticDependentParam(graph, "size_weights", "size_weights_hidden_0 + size_weights_hidden_1 + size_weights_output", {param_size_weights_output, param_size_weights_hidden_1, param_size_weights_hidden_0});

	/* === Vertices === */

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_size_weights);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_size_bias);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size_0);
	Spider::addInParam(bo_ForkBias, 1, param_hidden_size_1);
	Spider::addInParam(bo_ForkBias, 2, param_output_size);

	PiSDFVertex* bo_activationFunction_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_0",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_ACTIVATIONFUNCTION_0_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_VALID_MLP_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_valid_mlp);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_valid_mlp, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 5,
		/*InParam*/ 2);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size_0);
	Spider::addInParam(bo_BroadCastValid, 1, param_hidden_size_1);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 3,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden_0);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_hidden_1);
	Spider::addInParam(bo_ForkWeights, 2, param_size_weights_output);

	PiSDFVertex* bo_activationFunction_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction_1",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_ACTIVATIONFUNCTION_1_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_raw_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_hidden_0 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden_0",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden_0, 0, param_hidden_size_0);

	PiSDFVertex* if_raw_hidden_0 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden_0",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden_0, 0, param_hidden_size_0);

	PiSDFVertex* if_hidden_1 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden_1",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden_1, 0, param_hidden_size_1);

	PiSDFVertex* if_raw_hidden_1 = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden_1",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden_1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastRawOutput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawOutput",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawOutput, 0, param_output_size);

	PiSDFVertex* bo_BroadcastHidden1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastRawHidden1 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden1",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden1, 0, param_hidden_size_1);

	PiSDFVertex* bo_BroadcastHidden0 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden0",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden0, 0, param_hidden_size_0);

	PiSDFVertex* bo_BroadcastRawHidden0 = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden0",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden0, 0, param_hidden_size_0);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size_1);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_0 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_0",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_0, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer_0, 1, param_hidden_size_0);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0(bo_Hidden_layer_0);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_0, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer_1 = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer_1",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer_1, 0, param_hidden_size_0);
	Spider::addInParam(bo_Hidden_layer_1, 1, param_hidden_size_1);
	/* == Generating subgraph definition == */
	ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1(bo_Hidden_layer_1);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer_1, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_bias)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0 + hidden_size_1 + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_valid_mlp, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_outputActivation, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden_0 + size_weights_hidden_1+size_weights_output)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden_0)*4",
			/* = Snk = */       bo_Hidden_layer_0, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(size_weights_hidden_1)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_0 * hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size_1 * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastRawOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawOutput, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_outputActivation, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       if_raw_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_BroadcastRawHidden1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden1, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       bo_activationFunction_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_Hidden_layer_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       if_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden1, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_1)*4",
			/* = Snk = */       if_raw_hidden_1, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       if_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer_0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_BroadcastRawHidden0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden0, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       bo_activationFunction_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden0, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size_0)*4",
			/* = Snk = */       if_raw_hidden_0, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size_0)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void ddpg_Update_Networks_Update_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Output_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_0
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_0(PiSDFVertex *bo_Hidden_layer_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_0, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_HIDDEN_LAYER_0_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Hidden_layer_1
void ddpg_Update_Networks_Update_Critic_MLP_Hidden_layer_1(PiSDFVertex *bo_Hidden_layer_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer_1, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_MLP_HIDDEN_LAYER_1_COMPUTENEURON_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_computeNeuron, 0, param_input_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_computeNeuron);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_computeNeuron, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 2);
	Spider::addInParam(if_input, 0, param_input_size);
	Spider::addInParam(if_input, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_input_size);
	Spider::addInParam(if_weights, 1, param_layer_size);

	PiSDFVertex* if_bias_values = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_values",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_values, 0, param_layer_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_computeNeuron, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       if_output, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias_values, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_computeNeuron, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsHidden_1
void ddpg_Update_Networks_Update_Critic_GradientsHidden_1(PiSDFVertex *bo_GradientsHidden_1){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden_1, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_next_layer_size = Spider::addInheritedParam(graph, "next_layer_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);

	/* === Vertices === */

	PiSDFVertex* if_raw_hidden = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_layer_size);

	PiSDFVertex* if_next_layer_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_next_layer_weights, 0, param_next_layer_size);
	Spider::addInParam(if_next_layer_weights, 1, param_layer_size);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_input_size);
	Spider::addInParam(if_weights_gradient, 1, param_layer_size);

	PiSDFVertex* if_next_layer_errors = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_errors",
		/*InParam*/ 1);
	Spider::addInParam(if_next_layer_errors, 0, param_next_layer_size);

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_1_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_layer_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_layer_size);

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* bo_BackPropagated_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "BackPropagated_Error",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_1_BACKPROPAGATED_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_BackPropagated_Error, 0, param_layer_size);
	Spider::addInParam(bo_BackPropagated_Error, 1, param_next_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_BackPropagated_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_BackPropagated_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_1_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_errors, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size * layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size * next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BackPropagated_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsOutput
void ddpg_Update_Networks_Update_Critic_GradientsOutput(PiSDFVertex *bo_GradientsOutput){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    12,
		/*Params*/   2,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsOutput, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);

	/* === Vertices === */

	PiSDFVertex* if_target = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_target",
		/*InParam*/ 1);
	Spider::addInParam(if_target, 0, param_output_size);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_output_size);
	Spider::addInParam(if_weights_gradient, 1, param_input_size);

	PiSDFVertex* bo_Output_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_Error",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSOUTPUT_OUTPUT_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_Error, 0, param_output_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Output_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSOUTPUT_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_output_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_output_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_output_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* if_raw_output = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_output = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_target, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_Error, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "( input_size * output_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size  * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Output_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Output_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_output, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: GradientsHidden_0
void ddpg_Update_Networks_Update_Critic_GradientsHidden_0(PiSDFVertex *bo_GradientsHidden_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden_0, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_next_layer_size = Spider::addInheritedParam(graph, "next_layer_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);

	/* === Vertices === */

	PiSDFVertex* if_raw_hidden = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_layer_size);

	PiSDFVertex* if_next_layer_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_next_layer_weights, 0, param_next_layer_size);
	Spider::addInParam(if_next_layer_weights, 1, param_layer_size);

	PiSDFVertex* if_inputs = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_inputs",
		/*InParam*/ 1);
	Spider::addInParam(if_inputs, 0, param_input_size);

	PiSDFVertex* if_weights_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_gradient",
		/*InParam*/ 2);
	Spider::addInParam(if_weights_gradient, 0, param_input_size);
	Spider::addInParam(if_weights_gradient, 1, param_layer_size);

	PiSDFVertex* if_next_layer_errors = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_next_layer_errors",
		/*InParam*/ 1);
	Spider::addInParam(if_next_layer_errors, 0, param_next_layer_size);

	PiSDFVertex* bo_Derivative_Function = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Derivative_Function",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_0_DERIVATIVE_FUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Derivative_Function);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Derivative_Function, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_bias_gradient = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_gradient",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_gradient, 0, param_layer_size);

	PiSDFVertex* bo_BroadcastError = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastError",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastError, 0, param_layer_size);

	PiSDFVertex* bo_BroadCastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadCastValid",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_layer_size);

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* bo_BackPropagated_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "BackPropagated_Error",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_0_BACKPROPAGATED_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_BackPropagated_Error, 0, param_layer_size);
	Spider::addInParam(bo_BackPropagated_Error, 1, param_next_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_BackPropagated_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_BackPropagated_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Gradients = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Gradients",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_GRADIENTSHIDDEN_0_GRADIENTS_FCT,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Gradients, 0, param_input_size);
	Spider::addInParam(bo_Gradients, 1, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Gradients);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Gradients, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadCastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Derivative_Function, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_errors, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_next_layer_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(next_layer_size * layer_size)*4",
			/* = Snk = */       bo_BackPropagated_Error, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size * next_layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BackPropagated_Error, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_BroadcastError, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * layer_size)*4",
			/* = Snk = */       if_weights_gradient, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastError, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadCastValid, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_inputs, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Gradients, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_raw_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_Derivative_Function, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamHidden_0
void ddpg_Update_Networks_Update_Critic_AdamHidden_0(PiSDFVertex *bo_AdamHidden_0){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden_0, graph);

	/* === Parameters === */

	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 0);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 1);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * layer_size", {param_input_size, param_layer_size});

	/* === Vertices === */

	PiSDFVertex* if_gradients = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_gradients",
		/*InParam*/ 2);
	Spider::addInParam(if_gradients, 0, param_weights_size);
	Spider::addInParam(if_gradients, 1, param_layer_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 1);
	Spider::addInParam(if_weights, 0, param_weights_size);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 1);
	Spider::addInParam(if_bias, 0, param_layer_size);

	PiSDFVertex* if_first_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments, 1, param_layer_size);

	PiSDFVertex* if_second_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_second_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_second_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_second_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_first_order_moments_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_first_order_moments_out",
		/*InParam*/ 2);
	Spider::addInParam(if_first_order_moments_out, 0, param_weights_size);
	Spider::addInParam(if_first_order_moments_out, 1, param_layer_size);

	PiSDFVertex* if_weights_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights_out",
		/*InParam*/ 1);
	Spider::addInParam(if_weights_out, 0, param_weights_size);

	PiSDFVertex* if_bias_out = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias_out",
		/*InParam*/ 1);
	Spider::addInParam(if_bias_out, 0, param_layer_size);

	PiSDFVertex* if_betas = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_betas",
		/*InParam*/ 0);

	PiSDFVertex* if_epsilon = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_epsilon",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeWeights = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeWeights",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMHIDDEN_0_OPTIMIZEWEIGHTS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeWeights, 0, param_weights_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeWeights);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeWeights, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* if_valid = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_valid",
		/*InParam*/ 0);

	PiSDFVertex* if_learning_rate = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_learning_rate",
		/*InParam*/ 0);

	PiSDFVertex* bo_optimizeBias = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "optimizeBias",
		/*FctId*/   DDPG_UPDATE_NETWORKS_UPDATE_CRITIC_ADAMHIDDEN_0_OPTIMIZEBIAS_FCT,
		/*InData*/  8,
		/*OutData*/ 3,
		/*InParam*/ 1);
	/* == Adding input parameters == */
	Spider::addInParam(bo_optimizeBias, 0, param_layer_size);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_optimizeBias);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_optimizeBias, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastValid = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastValid",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastEpsilon = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastEpsilon",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastLearningRate = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastLearningRate",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastBetas = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBetas",
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_ForkGradients = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkGradients",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkGradients, 0, param_layer_size);
	Spider::addInParam(bo_ForkGradients, 1, param_weights_size);

	PiSDFVertex* bo_ForkSecondOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkSecondOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkSecondOrder, 1, param_weights_size);

	PiSDFVertex* bo_ForkFirstOrder = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkFirstOrder",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_ForkFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinFirstOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinFirstOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinFirstOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinFirstOrder, 1, param_weights_size);

	PiSDFVertex* bo_JoinSecondOrder = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinSecondOrder",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinSecondOrder, 0, param_layer_size);
	Spider::addInParam(bo_JoinSecondOrder, 1, param_weights_size);


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       if_weights_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       if_bias_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_valid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastValid, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastValid, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastLearningRate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    7, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastLearningRate, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_epsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_BroadcastEpsilon, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastEpsilon, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(1)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastBetas, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_betas, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(4)*8",
			/* = Snk = */       bo_BroadcastBetas, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(4)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*4",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkGradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*4",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(layer_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_gradients, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*4",
			/* = Snk = */       bo_ForkGradients, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_first_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkFirstOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_second_order_moments, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       bo_ForkSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_optimizeBias, 
			/* = SnkPrt = */    5, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_ForkSecondOrder, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_optimizeWeights, 
			/* = SnkPrt = */    6, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinFirstOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size + layer_size)*8",
			/* = Snk = */       if_first_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_JoinSecondOrder, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size + weights_size)*8",
			/* = Snk = */       if_second_order_moments_out, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size + weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeBias, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(layer_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(layer_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinFirstOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_optimizeWeights, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(weights_size)*8",
			/* = Snk = */       bo_JoinSecondOrder, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(weights_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}
