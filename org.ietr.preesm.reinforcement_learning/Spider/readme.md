# Run the workflow on preesm to generate the main.c and the coreX.c files in the codegen folder
# On the corresponding core files and before the main loop of the thread, add the following inits:

// This inits the environment of the system.
// Names of the fifos might change so look for the sizes, the first one must be size of "8 * sizeof(char)" and the second one "12 * sizeof(char)"
envInit((float*)FIFO_Head_broadcastState_end__0, (float*)FIFO_Head_Environment_end_st__0);


//This inits the weights and bias of the Actor MLP 
//Again the names might change so the sizes are respectively
// "240*sizeof(char)", "80*sizeof(char)", "80*sizeof(char)", "4*sizeof(char)"
weightGenInit(0, (float*)FIFO_Head_Actor_MLP_weights___0, (float*)FIFO_Head_Actor_MLP_weights___1);
weightGenInit(1, (float*)FIFO_Head_Actor_MLP_weights___2, (float*)FIFO_Head_Actor_MLP_weights___3);
