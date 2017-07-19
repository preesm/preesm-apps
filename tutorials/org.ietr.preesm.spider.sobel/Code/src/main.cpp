/****************************************************************************
 * Copyright or © or Copr. IETR/INSA (2013): Julien Heulot, Yaset Oliva,    *
 * Maxime Pelcat, Jean-François Nezan, Jean-Christophe Prevotet             *
 *                                                                          *
 * [jheulot,yoliva,mpelcat,jnezan,jprevote]@insa-rennes.fr                  *
 *                                                                          *
 * This software is a computer program whose purpose is to execute          *
 * parallel applications.                                                   *
 *                                                                          *
 * This software is governed by the CeCILL-C license under French law and   *
 * abiding by the rules of distribution of free software.  You can  use,    *
 * modify and/ or redistribute the software under the terms of the CeCILL-C *
 * license as circulated by CEA, CNRS and INRIA at the following URL        *
 * "http://www.cecill.info".                                                *
 *                                                                          *
 * As a counterpart to the access to the source code and  rights to copy,   *
 * modify and redistribute granted by the license, users are provided only  *
 * with a limited warranty  and the software's author,  the holder of the   *
 * economic rights,  and the successive licensors  have only  limited       *
 * liability.                                                               *
 *                                                                          *
 * In this respect, the user's attention is drawn to the risks associated   *
 * with loading,  using,  modifying and/or developing or reproducing the    *
 * software by the user in light of its specific status of free software,   *
 * that may mean  that it is complicated to manipulate,  and  that  also    *
 * therefore means  that it is reserved for developers  and  experienced    *
 * professionals having in-depth computer knowledge. Users are therefore    *
 * encouraged to load and test the software's suitability as regards their  *
 * requirements in conditions enabling the security of their systems and/or *
 * data to be ensured and,  more generally, to use and operate it in the    *
 * same conditions as regards security.                                     *
 *                                                                          *
 * The fact that you are presently reading this means that you have had     *
 * knowledge of the CeCILL-C license and that you accept its terms.         *
 ****************************************************************************/

#include <spider.h>

#include <stdio.h>
#include <stdlib.h>

/* Include your files here */



#include "../generated/top_display.h"
#include "nbSliceSetter.h"
#include "yuvRead.h"
#include "yuvDisplay.h"

#define SH_MEM_SIZE 0x04000000

#define NB_LRT 8

#define NB_ITERATION 100000

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

int stopThreads;

int main(int argc, char* argv[]){
	SpiderConfig cfg;
	ExecutionStat stat;

	// Setting memory info
	cfg.memAllocType = MEMALLOC_DUMMY;
	cfg.memAllocStart = (void*)0;
	cfg.memAllocSize = SH_MEM_SIZE;


	// Setting scheduler
	cfg.schedulerType = SCHEDULER_LIST;


	// Declaring stacks
	cfg.archiStack.name = "ArchiStack";
	cfg.archiStack.start = archiStack;

	cfg.lrtStack.name = "LrtStack";
	cfg.lrtStack.start = lrtStack;

	cfg.pisdfStack.name = "PiSDFStack";
	cfg.pisdfStack.start = pisdfStack;

	cfg.srdagStack.name = "SrdagStack";
	cfg.srdagStack.start = srdagStack;

	cfg.transfoStack.name = "TransfoStack";
	cfg.transfoStack.start = transfoStack;


#if STACK_IS_DYNAMIC == 1

	cfg.archiStack.type = STACK_DYNAMIC;

	cfg.lrtStack.type = STACK_DYNAMIC;
	
	cfg.pisdfStack.type = STACK_DYNAMIC;
	
	cfg.srdagStack.type = STACK_DYNAMIC;
	
	cfg.transfoStack.type = STACK_DYNAMIC;

#else
	cfg.archiStack.type = STACK_STATIC;
	cfg.archiStack.size = ARCHI_SIZE;

	cfg.lrtStack.type = STACK_STATIC;
	cfg.lrtStack.size = LRT_SIZE;

	cfg.pisdfStack.type = STACK_STATIC;
	cfg.pisdfStack.size = PISDF_SIZE;

	cfg.srdagStack.type = STACK_STATIC;
	cfg.srdagStack.size = SRDAG_SIZE;

	cfg.transfoStack.type = STACK_STATIC;
	cfg.transfoStack.size = TRANSFO_SIZE;
#endif

	// Setting desired number of LRT/thread
	cfg.platform.nLrt = NB_LRT;

	// Setting size of shared mem
	cfg.platform.shMemSize = SH_MEM_SIZE;

	// Setting graph PiSDF graph
	cfg.platform.fcts = top_display_fcts;
	cfg.platform.nLrtFcts = N_FCT_TOP_DISPLAY;

	cfg.verbose = false;
	cfg.traceEnabled = false;
	cfg.useGraphOptim = true;
	cfg.useActorPrecedence = true;

	// Spider initialisation
	Spider::init(cfg);

	
	/* Actor initialisation here if needed */
	initNbSliceSetter(DISPLAY_H);
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);
	initReadYUV(DISPLAY_W, DISPLAY_H);




	// PiSDF graph construction
	init_top_display();

	printf("Start\n");
		
	// Main loop, exeption handling can be removed to increase performance
	try{
	//int i=1;{
	for(int i=0; i<NB_ITERATION; i++){
		//printf("NStep = %d\n", i);

		Spider::iterate();

		// Printing Gantt
		if (cfg.traceEnabled) Spider::printGantt("stereo.pgantt", "stereo_tex.dat", &stat);

	}
	}catch(const char* s){
		printf("Exception : %s\n", s);
	}

	printf("finished\n");

	// PiSDF graph destruction
	free_top_display();

	Spider::clean();

	/* Actor finalisation here if needed */




	return 0;
}
