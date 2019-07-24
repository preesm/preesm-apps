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

#include "training.h"

void training(PiSDFVertex *bo_training, Param action_space_size = 3, Param actor_hidden_size = 20, Param critic_hidden_size = 20, Param state_angular_size = 3, Param state_space_size = 5, Param value_space_size = 1, Param x_target = 3, Param y_target = 4);
void training_Critic_MLP_Next(PiSDFVertex *bo_Critic_MLP_Next);
void training_Critic_MLP_Next_Output_layer(PiSDFVertex *bo_Output_layer);
void training_Critic_MLP_Next_Hidden_layer(PiSDFVertex *bo_Hidden_layer);
void training_Critic_MLP(PiSDFVertex *bo_Critic_MLP);
void training_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void training_Critic_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer);
void training_Actor_MLP(PiSDFVertex *bo_Actor_MLP);
void training_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void training_Actor_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer);
void training_Update_Critic(PiSDFVertex *bo_Update_Critic);
void training_Update_Critic_AdamOutput(PiSDFVertex *bo_AdamOutput);
void training_Update_Critic_AdamHidden(PiSDFVertex *bo_AdamHidden);
void training_Update_Critic_MLP(PiSDFVertex *bo_MLP);
void training_Update_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void training_Update_Critic_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer);
void training_Update_Critic_GradientsHidden(PiSDFVertex *bo_GradientsHidden);
void training_Update_Critic_GradientsOutput(PiSDFVertex *bo_GradientsOutput);
void training_Update_Actor(PiSDFVertex *bo_Update_Actor);
void training_Update_Actor_AdamOutput(PiSDFVertex *bo_AdamOutput);
void training_Update_Actor_AdamHidden(PiSDFVertex *bo_AdamHidden);
void training_Update_Actor_MLP(PiSDFVertex *bo_MLP);
void training_Update_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer);
void training_Update_Actor_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer);
void training_Update_Actor_GradientsHidden(PiSDFVertex *bo_GradientsHidden);
void training_Update_Actor_GradientsOutput(PiSDFVertex *bo_GradientsOutput);

/**
 * This is the method you need to call to build a complete PiSDF graph.
 */
void init_training(Param action_space_size, Param actor_hidden_size, Param critic_hidden_size, Param state_angular_size, Param state_space_size, Param value_space_size, Param x_target, Param y_target){
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
	training(topVertex, action_space_size, actor_hidden_size, critic_hidden_size, state_angular_size, state_space_size, value_space_size, x_target, y_target);

	/* Setting main application graph */
	Spider::setGraph(topGraph);
}

// Method building PiSDFGraph: training
void training(PiSDFVertex *bo_training, Param action_space_size, Param actor_hidden_size, Param critic_hidden_size, Param state_angular_size, Param state_space_size, Param value_space_size, Param x_target, Param y_target){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    38,
		/*Params*/   12,
		/*InputIf*/  0,
		/*OutputIf*/ 0,
		/*Config*/   0,
		/*Body*/     31);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_training, graph);

	/* === Parameters === */

	PiSDFParam *param_action_space_size = Spider::addStaticParam(graph, "action_space_size", action_space_size);
	PiSDFParam *param_state_angular_size = Spider::addStaticParam(graph, "state_angular_size", state_angular_size);
	PiSDFParam *param_state_space_size = Spider::addStaticParam(graph, "state_space_size", state_space_size);
	PiSDFParam *param_value_space_size = Spider::addStaticParam(graph, "value_space_size", value_space_size);
	PiSDFParam *param_critic_hidden_size = Spider::addStaticParam(graph, "critic_hidden_size", critic_hidden_size);
	PiSDFParam *param_actor_hidden_size = Spider::addStaticParam(graph, "actor_hidden_size", actor_hidden_size);
	PiSDFParam *param_x_target = Spider::addStaticParam(graph, "x_target", x_target);
	PiSDFParam *param_y_target = Spider::addStaticParam(graph, "y_target", y_target);
	PiSDFParam *param_critic_weights_size = Spider::addStaticDependentParam(graph, "critic_weights_size", "state_space_size * critic_hidden_size + critic_hidden_size * value_space_size", {param_critic_hidden_size, param_state_space_size, param_value_space_size});
	PiSDFParam *param_critic_bias_size = Spider::addStaticDependentParam(graph, "critic_bias_size", "critic_hidden_size + value_space_size", {param_critic_hidden_size, param_value_space_size});
	PiSDFParam *param_actor_weights_size = Spider::addStaticDependentParam(graph, "actor_weights_size", "state_space_size * actor_hidden_size + actor_hidden_size * action_space_size", {param_actor_hidden_size, param_action_space_size, param_state_space_size});
	PiSDFParam *param_actor_bias_size = Spider::addStaticDependentParam(graph, "actor_bias_size", "action_space_size + actor_hidden_size", {param_actor_hidden_size, param_action_space_size});

	/* === Vertices === */

	PiSDFVertex* bo_Environment = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Environment",
		/*FctId*/   TRAINING_ENVIRONMENT_FCT,
		/*InData*/  2,
		/*OutData*/ 3,
		/*InParam*/ 5);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Environment, 0, param_state_space_size);
	Spider::addInParam(bo_Environment, 1, param_action_space_size);
	Spider::addInParam(bo_Environment, 2, param_state_angular_size);
	Spider::addInParam(bo_Environment, 3, param_x_target);
	Spider::addInParam(bo_Environment, 4, param_y_target);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Environment);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Environment, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastStateFeature = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastStateFeature",
		/*OutData*/ 5,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastStateFeature, 0, param_state_space_size);

	PiSDFVertex* bo_Temporal_Difference_Error = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Temporal_Difference_Error",
		/*FctId*/   TRAINING_TEMPORAL_DIFFERENCE_ERROR_FCT,
		/*InData*/  4,
		/*OutData*/ 2,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_Temporal_Difference_Error);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Temporal_Difference_Error, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastWeightsCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeightsCritic",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeightsCritic, 0, param_critic_weights_size);

	PiSDFVertex* bo_BroadcastBiasCritic = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasCritic",
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastBiasCritic, 0, param_critic_bias_size);

	PiSDFVertex* bo_GaussianPolicy = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GaussianPolicy",
		/*FctId*/   TRAINING_GAUSSIANPOLICY_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeightsActor, 0, param_actor_weights_size);

	PiSDFVertex* bo_BroadcastBiasActor = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastBiasActor",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastBiasActor, 0, param_actor_bias_size);

	PiSDFVertex* bo_valid_actor = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_actor",
		/*FctId*/   TRAINING_VALID_ACTOR_FCT,
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
		/*FctId*/   TRAINING_VALID_CRITIC_FCT,
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
		/*FctId*/   TRAINING_GEN_GAMMA_FCT,
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
		/*FctId*/   TRAINING_GEN_SIGMA_FCT,
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
		/*FctId*/   TRAINING_GEN_ACTOR_LEARNING_RATE_FCT,
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
		/*FctId*/   TRAINING_GEN_CRITIC_LEARNING_RATE_FCT,
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
		/*FctId*/   TRAINING_CLIPACTION_FCT,
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
		/*FctId*/   TRAINING_GEN_ENVIRONMENT_LIMITS_FCT,
		/*InData*/  0,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_gen_environment_limits);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_gen_environment_limits, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Critic_MLP_Next = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Critic_MLP_Next",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Critic_MLP_Next, 0, param_value_space_size);
	Spider::addInParam(bo_Critic_MLP_Next, 1, param_critic_hidden_size);
	Spider::addInParam(bo_Critic_MLP_Next, 2, param_state_space_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP_Next(bo_Critic_MLP_Next);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Critic_MLP_Next, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Critic_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Critic_MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Critic_MLP, 0, param_value_space_size);
	Spider::addInParam(bo_Critic_MLP, 1, param_critic_hidden_size);
	Spider::addInParam(bo_Critic_MLP, 2, param_state_space_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP(bo_Critic_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Critic_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Actor_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Actor_MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 1,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Actor_MLP, 0, param_action_space_size);
	Spider::addInParam(bo_Actor_MLP, 1, param_actor_hidden_size);
	Spider::addInParam(bo_Actor_MLP, 2, param_state_space_size);
	/* == Generating subgraph definition == */
	training_Actor_MLP(bo_Actor_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Actor_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Update_Critic = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Update_Critic",
		/*FctId*/   -1,
		/*InData*/  6,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Update_Critic, 0, param_state_space_size);
	Spider::addInParam(bo_Update_Critic, 1, param_critic_hidden_size);
	Spider::addInParam(bo_Update_Critic, 2, param_value_space_size);
	/* == Generating subgraph definition == */
	training_Update_Critic(bo_Update_Critic);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Update_Critic, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Update_Actor = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Update_Actor",
		/*FctId*/   -1,
		/*InData*/  6,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Update_Actor, 0, param_state_space_size);
	Spider::addInParam(bo_Update_Actor, 1, param_actor_hidden_size);
	Spider::addInParam(bo_Update_Actor, 2, param_action_space_size);
	/* == Generating subgraph definition == */
	training_Update_Actor(bo_Update_Actor);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Update_Actor, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Environment, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(state_angular_size)*4",
			/* = Snk = */       bo_Environment, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_angular_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_angular_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Critic_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    4, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size * critic_hidden_size + critic_hidden_size * value_space_size)*4",
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
			/* = Src = */       bo_Update_Critic, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(critic_hidden_size + value_space_size)*4",
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
			/* = Src = */       bo_BroadcastStateFeature, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(state_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(state_space_size) * 4",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Update_Actor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size * actor_hidden_size + actor_hidden_size * action_space_size)*4",
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
			/* = Src = */       bo_Update_Actor, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_hidden_size + action_space_size)*4",
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
			/* = Src = */       bo_Environment, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_BroadcastStateFeature, 
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
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(state_space_size)*4",
			/* = Snk = */       bo_Critic_MLP_Next, 
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
			/* = Src = */       bo_Critic_MLP_Next, 
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
			/* = Src = */       bo_Environment, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(1)*4",
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
			/* = Src = */       bo_Critic_MLP, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(value_space_size)*4",
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(value_space_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    4, 
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
			/* = Src = */       bo_valid_actor, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
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
			/* = Src = */       bo_valid_critic, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
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
			/* = Src = */       bo_gen_gamma, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Temporal_Difference_Error, 
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
			/* = Src = */       bo_gen_actor_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Update_Actor, 
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
			/* = Src = */       bo_gen_critic_learning_rate, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(action_space_size + actor_hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(actor_bias_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(actor_hidden_size + action_space_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Update_Actor, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size * actor_hidden_size + actor_hidden_size * action_space_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(actor_weights_size)*4",
			/* = Snk = */       bo_Actor_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_space_size * actor_hidden_size + actor_hidden_size * action_space_size)*4");
		Spider::addDelay(
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
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(critic_weights_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(state_space_size * critic_hidden_size + critic_hidden_size * value_space_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Critic_MLP, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_space_size * critic_hidden_size  + critic_hidden_size * value_space_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Critic_MLP_Next, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(state_space_size* critic_hidden_size  + critic_hidden_size * value_space_size)*4");
		Spider::addDelay(
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
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(critic_bias_size)*4",
			/* = Snk = */       bo_Update_Critic, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(value_space_size + critic_hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Critic_MLP, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(critic_hidden_size + value_space_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Critic_MLP_Next, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(critic_hidden_size + value_space_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Critic_MLP_Next
void training_Critic_MLP_Next(PiSDFVertex *bo_Critic_MLP_Next){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    15,
		/*Params*/   5,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     8);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Critic_MLP_Next, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);
	PiSDFParam *param_size_weights_hidden = Spider::addStaticDependentParam(graph, "size_weights_hidden", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "output_size * hidden_size", {param_output_size, param_hidden_size});

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
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_size_weights_hidden);
	Spider::addInParam(if_weights, 1, param_size_weights_output);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 2);
	Spider::addInParam(if_bias, 0, param_hidden_size);
	Spider::addInParam(if_bias, 1, param_output_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);

	PiSDFVertex* bo_activationFunction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction",
		/*FctId*/   TRAINING_CRITIC_MLP_NEXT_ACTIVATIONFUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   TRAINING_CRITIC_MLP_NEXT_VALID_MLP_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   TRAINING_CRITIC_MLP_NEXT_OUTPUTACTIVATION_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_output);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP_Next_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP_Next_Hidden_layer(bo_Hidden_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + output_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       bo_activationFunction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Prod Expr = */ "(size_weights_hidden + size_weights_output)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden + size_weights_output)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_hidden)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void training_Critic_MLP_Next_Output_layer(PiSDFVertex *bo_Output_layer){
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
		/*FctId*/   TRAINING_CRITIC_MLP_NEXT_OUTPUT_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Hidden_layer
void training_Critic_MLP_Next_Hidden_layer(PiSDFVertex *bo_Hidden_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   TRAINING_CRITIC_MLP_NEXT_HIDDEN_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Critic_MLP
void training_Critic_MLP(PiSDFVertex *bo_Critic_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    15,
		/*Params*/   5,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     8);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Critic_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);
	PiSDFParam *param_size_weights_hidden = Spider::addStaticDependentParam(graph, "size_weights_hidden", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "output_size * hidden_size", {param_output_size, param_hidden_size});

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
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_size_weights_hidden);
	Spider::addInParam(if_weights, 1, param_size_weights_output);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 2);
	Spider::addInParam(if_bias, 0, param_hidden_size);
	Spider::addInParam(if_bias, 1, param_output_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);

	PiSDFVertex* bo_activationFunction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction",
		/*FctId*/   TRAINING_CRITIC_MLP_ACTIVATIONFUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   TRAINING_CRITIC_MLP_VALID_MLP_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   TRAINING_CRITIC_MLP_OUTPUTACTIVATION_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_output);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Critic_MLP_Hidden_layer(bo_Hidden_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + output_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       bo_activationFunction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Prod Expr = */ "(size_weights_hidden + size_weights_output)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden + size_weights_output)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_hidden)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void training_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
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
		/*FctId*/   TRAINING_CRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Hidden_layer
void training_Critic_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   TRAINING_CRITIC_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Actor_MLP
void training_Actor_MLP(PiSDFVertex *bo_Actor_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    15,
		/*Params*/   5,
		/*InputIf*/  3,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     8);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Actor_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);
	PiSDFParam *param_size_weights_hidden = Spider::addStaticDependentParam(graph, "size_weights_hidden", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "output_size * hidden_size", {param_output_size, param_hidden_size});

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
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_size_weights_hidden);
	Spider::addInParam(if_weights, 1, param_size_weights_output);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 2);
	Spider::addInParam(if_bias, 0, param_hidden_size);
	Spider::addInParam(if_bias, 1, param_output_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);

	PiSDFVertex* bo_activationFunction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction",
		/*FctId*/   TRAINING_ACTOR_MLP_ACTIVATIONFUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   TRAINING_ACTOR_MLP_VALID_MLP_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   TRAINING_ACTOR_MLP_OUTPUTACTIVATION_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_output);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	training_Actor_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Actor_MLP_Hidden_layer(bo_Hidden_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + output_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       bo_activationFunction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Prod Expr = */ "(size_weights_hidden + size_weights_output)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden + size_weights_output)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_hidden)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void training_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
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
		/*FctId*/   TRAINING_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Hidden_layer
void training_Actor_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   TRAINING_ACTOR_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT,
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
void training_Update_Critic(PiSDFVertex *bo_Update_Critic){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    54,
		/*Params*/   7,
		/*InputIf*/  6,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     27);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Update_Critic, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 2);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * hidden_size + hidden_size * output_size", {param_hidden_size, param_input_size, param_output_size});
	PiSDFParam *param_bias_size = Spider::addStaticDependentParam(graph, "bias_size", "hidden_size + output_size", {param_hidden_size, param_output_size});
	PiSDFParam *param_hidden_weights_size = Spider::addStaticDependentParam(graph, "hidden_weights_size", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_output_weights_size = Spider::addStaticDependentParam(graph, "output_weights_size", "hidden_size * output_size", {param_output_size, param_hidden_size});

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
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_hidden_weights_size);
	Spider::addInParam(bo_ForkWeights, 1, param_output_weights_size);
	Spider::addInParam(bo_ForkWeights, 2, param_weights_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);
	Spider::addInParam(bo_ForkBias, 2, param_bias_size);

	PiSDFVertex* bo_JoinWeights = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinWeights",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinWeights, 0, param_weights_size);
	Spider::addInParam(bo_JoinWeights, 1, param_hidden_weights_size);
	Spider::addInParam(bo_JoinWeights, 2, param_output_weights_size);

	PiSDFVertex* bo_JoinBias = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinBias",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinBias, 0, param_bias_size);
	Spider::addInParam(bo_JoinBias, 1, param_hidden_size);
	Spider::addInParam(bo_JoinBias, 2, param_output_size);

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
		/*OutData*/ 5,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastWeights_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_output, 0, param_output_weights_size);

	PiSDFVertex* bo_JoinGradients_hidden = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden, 0, param_hidden_weights_size);
	Spider::addInParam(bo_JoinGradients_hidden, 1, param_hidden_size);

	PiSDFVertex* bo_JoinGradients_output = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_output",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_output, 0, param_hidden_size);
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
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_gen_epsilon = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_epsilon",
		/*FctId*/   TRAINING_UPDATE_CRITIC_GEN_EPSILON_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_adamBetas = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "adamBetas",
		/*FctId*/   TRAINING_UPDATE_CRITIC_ADAMBETAS_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_AdamOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamOutput",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamOutput, 0, param_output_size);
	Spider::addInParam(bo_AdamOutput, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_AdamOutput(bo_AdamOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden, 0, param_hidden_size);
	Spider::addInParam(bo_AdamHidden, 1, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_AdamHidden(bo_AdamHidden);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 4,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_MLP, 0, param_output_size);
	Spider::addInParam(bo_MLP, 1, param_hidden_size);
	Spider::addInParam(bo_MLP, 2, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_MLP(bo_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden, 0, param_hidden_size);
	Spider::addInParam(bo_GradientsHidden, 1, param_output_size);
	Spider::addInParam(bo_GradientsHidden, 2, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_GradientsHidden(bo_GradientsHidden);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsOutput",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsOutput, 0, param_output_size);
	Spider::addInParam(bo_GradientsOutput, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_GradientsOutput(bo_GradientsOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size + hidden_size)*8",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size + hidden_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size * hidden_size + hidden_size)*8",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size + hidden_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*8");
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
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*8");
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
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(input_size * hidden_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    1, 
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
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinBias, 
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
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    3, 
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
			/* = SrcPrt = */    0, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_GradientsHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_GradientsHidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_JoinGradients_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + hidden_weights_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Src = */       bo_GradientsHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size)*4",
			/* = Snk = */       bo_JoinGradients_hidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_JoinGradients_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamOutput
void training_Update_Critic_AdamOutput(PiSDFVertex *bo_AdamOutput){
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_ADAMOUTPUT_OPTIMIZEBIAS_FCT,
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

// Method building PiSDFGraph: AdamHidden
void training_Update_Critic_AdamHidden(PiSDFVertex *bo_AdamHidden){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden, graph);

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
		/*FctId*/   TRAINING_UPDATE_CRITIC_ADAMHIDDEN_OPTIMIZEWEIGHTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_ADAMHIDDEN_OPTIMIZEBIAS_FCT,
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
void training_Update_Critic_MLP(PiSDFVertex *bo_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   5,
		/*InputIf*/  3,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);
	PiSDFParam *param_size_weights_hidden = Spider::addStaticDependentParam(graph, "size_weights_hidden", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "output_size * hidden_size", {param_output_size, param_hidden_size});

	/* === Vertices === */

	PiSDFVertex* if_raw_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_size_weights_hidden);
	Spider::addInParam(if_weights, 1, param_size_weights_output);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 2);
	Spider::addInParam(if_bias, 0, param_hidden_size);
	Spider::addInParam(if_bias, 1, param_output_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);

	PiSDFVertex* bo_activationFunction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction",
		/*FctId*/   TRAINING_UPDATE_CRITIC_MLP_ACTIVATIONFUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   TRAINING_UPDATE_CRITIC_MLP_VALID_MLP_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size);

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_output);

	PiSDFVertex* if_raw_hidden = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_hidden_size);

	PiSDFVertex* if_hidden = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden, 0, param_hidden_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* bo_BroadcastRawOutput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawOutput",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawOutput, 0, param_output_size);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   TRAINING_UPDATE_CRITIC_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastRawHidden = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden, 0, param_hidden_size);

	PiSDFVertex* bo_BroadcastHidden = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden, 0, param_hidden_size);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Critic_MLP_Hidden_layer(bo_Hidden_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + output_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden + size_weights_output)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden + size_weights_output)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_hidden)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_BroadcastRawHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       if_raw_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_BroadcastRawHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       bo_BroadcastHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       if_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void training_Update_Critic_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Hidden_layer
void training_Update_Critic_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   TRAINING_UPDATE_CRITIC_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: GradientsHidden
void training_Update_Critic_GradientsHidden(PiSDFVertex *bo_GradientsHidden){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden, graph);

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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_DERIVATIVE_FUNCTION_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_BACKPROPAGATED_ERROR_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSHIDDEN_GRADIENTS_FCT,
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
void training_Update_Critic_GradientsOutput(PiSDFVertex *bo_GradientsOutput){
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_OUTPUT_ERROR_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_GRADIENTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_CRITIC_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT,
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

// Method building PiSDFGraph: Update_Actor
void training_Update_Actor(PiSDFVertex *bo_Update_Actor){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    54,
		/*Params*/   7,
		/*InputIf*/  6,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     27);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Update_Actor, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 2);
	PiSDFParam *param_weights_size = Spider::addStaticDependentParam(graph, "weights_size", "input_size * hidden_size + hidden_size * output_size", {param_hidden_size, param_input_size, param_output_size});
	PiSDFParam *param_bias_size = Spider::addStaticDependentParam(graph, "bias_size", "hidden_size + output_size", {param_hidden_size, param_output_size});
	PiSDFParam *param_hidden_weights_size = Spider::addStaticDependentParam(graph, "hidden_weights_size", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_output_weights_size = Spider::addStaticDependentParam(graph, "output_weights_size", "hidden_size * output_size", {param_output_size, param_hidden_size});

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
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkWeights, 0, param_hidden_weights_size);
	Spider::addInParam(bo_ForkWeights, 1, param_output_weights_size);
	Spider::addInParam(bo_ForkWeights, 2, param_weights_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 3);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);
	Spider::addInParam(bo_ForkBias, 2, param_bias_size);

	PiSDFVertex* bo_JoinWeights = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinWeights",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinWeights, 0, param_weights_size);
	Spider::addInParam(bo_JoinWeights, 1, param_hidden_weights_size);
	Spider::addInParam(bo_JoinWeights, 2, param_output_weights_size);

	PiSDFVertex* bo_JoinBias = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinBias",
		/*InData*/  2,
		/*InParam*/ 3);
	Spider::addInParam(bo_JoinBias, 0, param_bias_size);
	Spider::addInParam(bo_JoinBias, 1, param_hidden_size);
	Spider::addInParam(bo_JoinBias, 2, param_output_size);

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
		/*OutData*/ 5,
		/*InParam*/ 0);

	PiSDFVertex* bo_BroadcastWeights_output = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastWeights_output",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastWeights_output, 0, param_output_weights_size);

	PiSDFVertex* bo_JoinGradients_hidden = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_hidden",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_hidden, 0, param_hidden_weights_size);
	Spider::addInParam(bo_JoinGradients_hidden, 1, param_hidden_size);

	PiSDFVertex* bo_JoinGradients_output = Spider::addJoinVertex(
		/*Graph*/   graph,
		/*Name*/    "JoinGradients_output",
		/*InData*/  2,
		/*InParam*/ 2);
	Spider::addInParam(bo_JoinGradients_output, 0, param_hidden_size);
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
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_gen_epsilon = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "gen_epsilon",
		/*FctId*/   TRAINING_UPDATE_ACTOR_GEN_EPSILON_FCT,
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
		/*OutData*/ 2,
		/*InParam*/ 0);

	PiSDFVertex* bo_adamBetas = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "adamBetas",
		/*FctId*/   TRAINING_UPDATE_ACTOR_ADAMBETAS_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 0);

	PiSDFVertex* bo_AdamOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamOutput",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamOutput, 0, param_output_size);
	Spider::addInParam(bo_AdamOutput, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_AdamOutput(bo_AdamOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_AdamHidden = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "AdamHidden",
		/*FctId*/   -1,
		/*InData*/  9,
		/*OutData*/ 4,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_AdamHidden, 0, param_hidden_size);
	Spider::addInParam(bo_AdamHidden, 1, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_AdamHidden(bo_AdamHidden);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_AdamHidden, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_MLP = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "MLP",
		/*FctId*/   -1,
		/*InData*/  3,
		/*OutData*/ 4,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_MLP, 0, param_output_size);
	Spider::addInParam(bo_MLP, 1, param_hidden_size);
	Spider::addInParam(bo_MLP, 2, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_MLP(bo_MLP);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_MLP, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsHidden = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsHidden",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 3);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsHidden, 0, param_hidden_size);
	Spider::addInParam(bo_GradientsHidden, 1, param_output_size);
	Spider::addInParam(bo_GradientsHidden, 2, param_input_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_GradientsHidden(bo_GradientsHidden);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsHidden, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_GradientsOutput = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "GradientsOutput",
		/*FctId*/   -1,
		/*InData*/  5,
		/*OutData*/ 2,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_GradientsOutput, 0, param_output_size);
	Spider::addInParam(bo_GradientsOutput, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_GradientsOutput(bo_GradientsOutput);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_GradientsOutput, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size + hidden_size)*8",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size + hidden_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size * hidden_size + hidden_size)*8",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*8");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "(hidden_weights_size + hidden_size) * 8",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ true);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    3, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*8");
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
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*8",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    4, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*8");
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
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    2, 
			/* = Prod Expr = */ "(input_size * hidden_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_AdamHidden, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_JoinBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size)*4",
			/* = Snk = */       bo_JoinWeights, 
			/* = SnkPrt = */    1, 
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
			/* = Src = */       bo_AdamOutput, 
			/* = SrcPrt = */    3, 
			/* = Prod Expr = */ "(output_size)*4",
			/* = Snk = */       bo_JoinBias, 
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
			/* = Src = */       bo_MLP, 
			/* = SrcPrt = */    3, 
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
			/* = SrcPrt = */    0, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_GradientsHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_GradientsOutput, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_ForkWeights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_weights_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Src = */       bo_BroadcastInput, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_GradientsHidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_JoinGradients_hidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + hidden_weights_size)*4",
			/* = Snk = */       bo_AdamHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(input_size * hidden_size + hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size)*4",
			/* = Snk = */       bo_JoinGradients_output, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(hidden_size * output_size + output_size)*4",
			/* = Snk = */       bo_AdamOutput, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size * output_size + output_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_GradientsHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Snk = */       bo_AdamHidden, 
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
			/* = Src = */       bo_GradientsHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size * hidden_size)*4",
			/* = Snk = */       bo_JoinGradients_hidden, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_weights_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_GradientsHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_JoinGradients_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: AdamOutput
void training_Update_Actor_AdamOutput(PiSDFVertex *bo_AdamOutput){
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEWEIGHTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_ADAMOUTPUT_OPTIMIZEBIAS_FCT,
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

// Method building PiSDFGraph: AdamHidden
void training_Update_Actor_AdamHidden(PiSDFVertex *bo_AdamHidden){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    31,
		/*Params*/   3,
		/*InputIf*/  9,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_AdamHidden, graph);

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
		/*FctId*/   TRAINING_UPDATE_ACTOR_ADAMHIDDEN_OPTIMIZEWEIGHTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_ADAMHIDDEN_OPTIMIZEBIAS_FCT,
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
void training_Update_Actor_MLP(PiSDFVertex *bo_MLP){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    21,
		/*Params*/   5,
		/*InputIf*/  3,
		/*OutputIf*/ 4,
		/*Config*/   0,
		/*Body*/     11);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_MLP, graph);

	/* === Parameters === */

	PiSDFParam *param_output_size = Spider::addInheritedParam(graph, "output_size", 0);
	PiSDFParam *param_hidden_size = Spider::addInheritedParam(graph, "hidden_size", 1);
	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 2);
	PiSDFParam *param_size_weights_hidden = Spider::addStaticDependentParam(graph, "size_weights_hidden", "input_size * hidden_size", {param_hidden_size, param_input_size});
	PiSDFParam *param_size_weights_output = Spider::addStaticDependentParam(graph, "size_weights_output", "output_size * hidden_size", {param_output_size, param_hidden_size});

	/* === Vertices === */

	PiSDFVertex* if_raw_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_output",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_output, 0, param_output_size);

	PiSDFVertex* if_input = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_input",
		/*InParam*/ 1);
	Spider::addInParam(if_input, 0, param_input_size);

	PiSDFVertex* if_weights = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_weights",
		/*InParam*/ 2);
	Spider::addInParam(if_weights, 0, param_size_weights_hidden);
	Spider::addInParam(if_weights, 1, param_size_weights_output);

	PiSDFVertex* if_bias = Spider::addInputIf(
		/*Graph*/   graph,
		/*Name*/    "if_bias",
		/*InParam*/ 2);
	Spider::addInParam(if_bias, 0, param_hidden_size);
	Spider::addInParam(if_bias, 1, param_output_size);

	PiSDFVertex* bo_ForkBias = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkBias",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkBias, 0, param_hidden_size);
	Spider::addInParam(bo_ForkBias, 1, param_output_size);

	PiSDFVertex* bo_activationFunction = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "activationFunction",
		/*FctId*/   TRAINING_UPDATE_ACTOR_MLP_ACTIVATIONFUNCTION_FCT,
		/*InData*/  2,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_activationFunction);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_activationFunction, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_valid_mlp = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "valid_mlp",
		/*FctId*/   TRAINING_UPDATE_ACTOR_MLP_VALID_MLP_FCT,
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
		/*OutData*/ 3,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadCastValid, 0, param_hidden_size);

	PiSDFVertex* bo_ForkWeights = Spider::addForkVertex(
		/*Graph*/   graph,
		/*Name*/    "ForkWeights",
		/*OutData*/ 2,
		/*InParam*/ 2);
	Spider::addInParam(bo_ForkWeights, 0, param_size_weights_hidden);
	Spider::addInParam(bo_ForkWeights, 1, param_size_weights_output);

	PiSDFVertex* if_raw_hidden = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_raw_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_raw_hidden, 0, param_hidden_size);

	PiSDFVertex* if_hidden = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_hidden",
		/*InParam*/ 1);
	Spider::addInParam(if_hidden, 0, param_hidden_size);

	PiSDFVertex* if_output = Spider::addOutputIf(
		/*Graph*/   graph,
		/*Name*/    "if_output",
		/*InParam*/ 1);
	Spider::addInParam(if_output, 0, param_output_size);

	PiSDFVertex* bo_BroadcastRawOutput = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawOutput",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawOutput, 0, param_output_size);

	PiSDFVertex* bo_outputActivation = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "outputActivation",
		/*FctId*/   TRAINING_UPDATE_ACTOR_MLP_OUTPUTACTIVATION_FCT,
		/*InData*/  1,
		/*OutData*/ 1,
		/*InParam*/ 0);
	/* == Setting execution constraints == */
	Spider::isExecutableOnAllPE(bo_outputActivation);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_outputActivation, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_BroadcastRawHidden = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastRawHidden",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastRawHidden, 0, param_hidden_size);

	PiSDFVertex* bo_BroadcastHidden = Spider::addBroadcastVertex(
		/*Graph*/   graph,
		/*Name*/    "BroadcastHidden",
		/*OutData*/ 2,
		/*InParam*/ 1);
	Spider::addInParam(bo_BroadcastHidden, 0, param_hidden_size);

	PiSDFVertex* bo_Output_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Output_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Output_layer, 0, param_hidden_size);
	Spider::addInParam(bo_Output_layer, 1, param_output_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_MLP_Output_layer(bo_Output_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Output_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");

	PiSDFVertex* bo_Hidden_layer = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "Hidden_layer",
		/*FctId*/   -1,
		/*InData*/  4,
		/*OutData*/ 1,
		/*InParam*/ 2);
	/* == Adding input parameters == */
	Spider::addInParam(bo_Hidden_layer, 0, param_input_size);
	Spider::addInParam(bo_Hidden_layer, 1, param_hidden_size);
	/* == Generating subgraph definition == */
	training_Update_Actor_MLP_Hidden_layer(bo_Hidden_layer);
	/* == Setting timing on corresponding PEs == */
	Spider::setTimingOnType(bo_Hidden_layer, static_cast<std::uint32_t>(PEType::CORE_TYPE_X86), "100");


	/* === Edges === */

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       if_input, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(input_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = Src = */       bo_ForkBias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    2, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
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
			/* = Src = */       if_bias, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size + output_size)*4",
			/* = Snk = */       bo_ForkBias, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size + output_size)*4");
		Spider::addDelay(
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
			/* = Snk = */       bo_Hidden_layer, 
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
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       if_weights, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(size_weights_hidden + size_weights_output)*4",
			/* = Snk = */       bo_ForkWeights, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(size_weights_hidden + size_weights_output)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_hidden)*4",
			/* = Snk = */       bo_Hidden_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(input_size * hidden_size)*4");
		Spider::addDelay(
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
			/* = Prod Expr = */ "(size_weights_output)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    1, 
			/* = Cons Expr = */ "(hidden_size * output_size)*4");
		Spider::addDelay(
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
			/* = Src = */       bo_BroadcastRawHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       if_raw_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_Hidden_layer, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_BroadcastRawHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastRawHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_activationFunction, 
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
			/* = Src = */       bo_BroadcastHidden, 
			/* = SrcPrt = */    1, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       if_hidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_activationFunction, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(1)*4",
			/* = Snk = */       bo_BroadcastHidden, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}

	{
		auto *edge = Spider::addEdge(
			/* = Graph = */     graph,
			/* = Src = */       bo_BroadcastHidden, 
			/* = SrcPrt = */    0, 
			/* = Prod Expr = */ "(hidden_size)*4",
			/* = Snk = */       bo_Output_layer, 
			/* = SnkPrt = */    0, 
			/* = Cons Expr = */ "(hidden_size)*4");
		Spider::addDelay(
			/* = Edge = */       edge,
			/* = Delay Expr = */ "0",
			/* = Setter = */     nullptr,
			/* = Getter = */     nullptr,
			/* = Persistent = */ false);
	}
}

// Method building PiSDFGraph: Output_layer
void training_Update_Actor_MLP_Output_layer(PiSDFVertex *bo_Output_layer){
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_MLP_OUTPUT_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: Hidden_layer
void training_Update_Actor_MLP_Hidden_layer(PiSDFVertex *bo_Hidden_layer){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    5,
		/*Params*/   2,
		/*InputIf*/  4,
		/*OutputIf*/ 1,
		/*Config*/   0,
		/*Body*/     1);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_Hidden_layer, graph);

	/* === Parameters === */

	PiSDFParam *param_input_size = Spider::addInheritedParam(graph, "input_size", 0);
	PiSDFParam *param_layer_size = Spider::addInheritedParam(graph, "layer_size", 1);

	/* === Vertices === */

	PiSDFVertex* bo_computeNeuron = Spider::addBodyVertex(
		/*Graph*/   graph,
		/*Name*/    "computeNeuron",
		/*FctId*/   TRAINING_UPDATE_ACTOR_MLP_HIDDEN_LAYER_COMPUTENEURON_FCT,
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

// Method building PiSDFGraph: GradientsHidden
void training_Update_Actor_GradientsHidden(PiSDFVertex *bo_GradientsHidden){
	PiSDFGraph* graph = Spider::createGraph(
		/*Edges*/    13,
		/*Params*/   3,
		/*InputIf*/  5,
		/*OutputIf*/ 2,
		/*Config*/   0,
		/*Body*/     5);

	/* == Linking subgraph to its parent == */
	Spider::addSubGraph(bo_GradientsHidden, graph);

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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_DERIVATIVE_FUNCTION_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_BACKPROPAGATED_ERROR_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSHIDDEN_GRADIENTS_FCT,
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
void training_Update_Actor_GradientsOutput(PiSDFVertex *bo_GradientsOutput){
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_OUTPUT_ERROR_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_GRADIENTS_FCT,
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
		/*FctId*/   TRAINING_UPDATE_ACTOR_GRADIENTSOUTPUT_DERIVATIVE_FUNCTION_FCT,
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
