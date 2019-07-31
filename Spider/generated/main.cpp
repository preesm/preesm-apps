/**
 * @file main.cpp
 * @generated by class org.preesm.codegen.xtend.spider.SpiderMainFilePrinter
 * @date Wed Jul 31 14:16:40 CEST 2019
 *
 */

/* Spider library include */
#include <spider.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <string.h>

/* Include your files here */
#include "buffer.h"

#include "../generated/ddpg.h"

#define NB_ITERATION 10000

#define STACK_IS_DYNAMIC (1)

#if STACK_IS_DYNAMIC == (1)

static char* archiStack;
static char* lrtStack;
static char* pisdfStack;
static char* srdagStack;
static char* transfoStack;

#else

#define ARCHI_SIZE 		128	*1024	*NB_LRT
#define LRT_SIZE 		16	*1024	*NB_LRT
#define PISDF_SIZE 		4	*1024*1024
#define SRDAG_SIZE 		8	*1024*1024 *100
#define TRANSFO_SIZE 	1	*1024*1024 *20

static char archiStack[ARCHI_SIZE];
static char lrtStack[LRT_SIZE];
static char pisdfStack[PISDF_SIZE];
static char srdagStack[SRDAG_SIZE];
static char transfoStack[TRANSFO_SIZE];

#endif

int preesmStopThreads;

int main(int argc, char* argv[]){
	SpiderConfig cfg;
	ExecutionStat stat;

	/* == Setting memory info == */
	cfg.memAllocType = MEMALLOC_DUMMY;
	cfg.memAllocStart = 0;
	cfg.memAllocSize = SH_MEM_SIZE;

	/* == Setting scheduler == */
	cfg.schedulerType = SCHEDULER_LIST;

	/* == Declaring stacks == */
	SpiderStackConfig stackConfig;
	stackConfig.archiStack.name = "ArchiStack";
	stackConfig.archiStack.start = archiStack;
	stackConfig.lrtStack.name = "LrtStack";
	stackConfig.lrtStack.start = lrtStack;
	stackConfig.pisdfStack.name = "PiSDFStack";
	stackConfig.pisdfStack.start = pisdfStack;
	stackConfig.srdagStack.name = "SrdagStack";
	stackConfig.srdagStack.start = srdagStack;
	stackConfig.transfoStack.name = "TransfoStack";
	stackConfig.transfoStack.start = transfoStack;


#if STACK_IS_DYNAMIC == 1
	stackConfig.archiStack.type = StackType::DYNAMIC;
	stackConfig.lrtStack.type = StackType::DYNAMIC;
	stackConfig.pisdfStack.type = StackType::DYNAMIC;
	stackConfig.srdagStack.type = StackType::DYNAMIC;
	stackConfig.transfoStack.type = StackType::DYNAMIC;
#else
	stackConfig.archiStack.type = StackType::STATIC;
	stackConfig.archiStack.size = ARCHI_SIZE;
	stackConfig.lrtStack.type = StackType::STATIC;
	stackConfig.lrtStack.size = LRT_SIZE;
	stackConfig.pisdfStack.type = StackType::STATIC;
	stackConfig.pisdfStack.size = PISDF_SIZE;
	stackConfig.srdagStack.type = StackType::STATIC;
	stackConfig.srdagStack.size = SRDAG_SIZE;
	stackConfig.transfoStack.type = StackType::STATIC;
	stackConfig.transfoStack.size = TRANSFO_SIZE;
#endif

	/* == Setting graph PiSDF graph == */
	cfg.fcts = ddpg_fcts;
	cfg.nLrtFcts = N_FCT_DDPG;

	/* == Verbosity of spider output == */
	cfg.verbose = false;
	/* == Enables output trace of spider == */
	cfg.traceEnabled = false;
	/* == Enables graph optimizations (may impact performance) == */
	cfg.useGraphOptim = true;

	/* == Papify instrumentation == */
	cfg.usePapify = false;

	try {
		/* == Spider stacks init == */
		Spider::initStacks(stackConfig);

		/* == Spider Archi init == */
		initArchi();

		/* == Spider initialisation == */
		Spider::init(cfg, stackConfig);

		/* == Actor initializations of vertex ddpg/Fill_Buffer/Shuffle == */
		initBuffer();

		/* == PiSDF graph construction == */
		init_ddpg();

		/* == Reserving memory for persistent delays == */
		Spider::initReservedMemory();

		fprintf(stderr, "INFO: Application execution -- START\n");

		/* == Main loop, exception handling can be removed to increase performance == */
		for(int i=0; i<NB_ITERATION && !preesmStopThreads; i++){
			/* == Compute the SR-DAG, scheduling and executing the main graph == */
			Spider::iterate();

			/* == Printing Gantt == */
			if (cfg.traceEnabled) {
				Spider::printGantt("gantt.pgantt", "gantt_tex.dat", &stat);
				fprintf(stderr, "INFO: Total execution time:       %lf ms\n",  (stat.execTime + stat.schedTime) / 1000000.);
				fprintf(stderr, "INFO: Application execution time: %lf ms\n",  stat.execTime / 1000000.);
				fprintf(stderr, "INFO: SPIDER overhead time:       %lf ms\n",  stat.schedTime / 1000000.);
			}
		}

		fprintf(stderr, "INFO: Application execution -- FINISHED\n");

		/* == Cleaning everything spider related == */
		Spider::clean();

		/* == Free memory buffer(s) of the Archi == */
		freeArchi();

	} catch(std::exception &e) {
		fprintf(stderr, "%s\n", e.what());
	}

	return 0;
}


