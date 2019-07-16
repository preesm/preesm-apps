/*
	============================================================================
	Name        : dump.c
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C
	Description : Function called by code generated by the Instrumented C
                  Printer of Preesm
	============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dump.h"

#define ceil(x) (((x) - (double)((int)((x)))) < 0.5 ? ((int)((x)) + 1):(int)((x)+0.5))

#ifdef _WIN32
#include <windows.h>
#define GET_CLOCK(clock_t) { \
    LARGE_INTEGER now; \
    QueryPerformanceCounter(&now); \
    clock_t = now.QuadPart; \
}
#define GET_ELAPSED_US(elapsed, clock_start, clock_end) { \
    (elapsed) = (clock_start) - (clock_end); \
    (elapsed) *= 1000000; \
    LARGE_INTEGER frequency; \
    QueryPerformanceFrequency(&frequency); \
    (elapsed) /= frequency.QuadPart; \
}
#elif defined(__GNUC__) && !defined(__MACH__)
#include <unistd.h>
#include <time.h>
#define GET_CLOCK(clock_t) { \
    struct timespec clock; \
    clock_gettime(CLOCK_MONOTONIC, &clock); \
    (clock_t) = (uint64_t)(clock.tv_sec * 1e9) + clock.tv_nsec; \
}
#define GET_ELAPSED_US(elapsed, clock_start, clock_end) { \
    (elapsed) = (clock_start) - (clock_end); \
    (elapsed) /= 1000; \
}
#else // Undefined or Unsupported platform, thus no assumption is made on available hardware
#define GET_CLOCK(clock_t) { clock_t = 0; }
#define GET_ELAPSED_US(elapsed, clock_start, clock_end) { (elapsed) = 0; }
#endif

static FILE *ptfile;
static int *bckupNbExec;

void dumpTime(int id, uint64_t* dumpBuffer) {
    GET_CLOCK(dumpBuffer[id]);
}

void initNbExec(int* nbExec, int nbDump){
    int i = 0;

	bckupNbExec = malloc(nbDump*sizeof(int));
	memset(bckupNbExec,0,nbDump*sizeof(int));

//    if((ptfile = fopen(DUMP_FILE, "a+")) == NULL )
//    {
//        fprintf(stderr,"ERROR: Cannot open dump file '%s'\n", DUMP_FILE);
//        system("PAUSE");
//        exit(1);
//    }

    // Go to the end:
//    fseek (ptfile , 0 , SEEK_END);

    //printf(";;");
    for(i=1; i<nbDump; i++){
        *(nbExec+i) = 1;
        fprintf(stderr,"%d;\n",i);
    }
//    fprintf(ptfile,"\n");
//    fflush(ptfile);
}

void writeTime(uint64_t* dumpBuffer, int nbDump, int* nbExec){
    static int stable = 1;
    int i ;
    int changed = 0;
	int nbNotReady = 0;
    if(stable != 0) {
        printf("--\n");
        for(i=1;i< nbDump;i++){
            float nbEx = (float)(*(nbExec+i));
            uint64_t elapsed_us;
            GET_ELAPSED_US(elapsed_us, dumpBuffer[i], dumpBuffer[i - 1]);
            float res;
            nbEx = (nbEx != 0.f)? 1.f/nbEx : 0.f;
            res = (float)(elapsed_us) * nbEx; // Gives time in us
            fprintf(stderr,"%.2f - %lu;\n", res, elapsed_us);
        }
//        fprintf(stderr,"\n");
    } else {
        for(i = nbDump - 1;i > 0; i--){
            int nbExecBefore;
            GET_ELAPSED_US(dumpBuffer[i], dumpBuffer[i], dumpBuffer[i - 1]);
            // We consider that all measures below 10 ms are not precise enough
            nbExecBefore = *(nbExec+i);
            if(dumpBuffer[i] / 1000 < 10 && (*(nbExec+i)) != 0) {
                *(nbExec+i) = ceil((*(nbExec+i) * 1.5));
                if(*(nbExec+i) > 131072) {
                    *(nbExec+i) = 131072;
                }
            }
            if(dumpBuffer[i] < 0){
                *(nbExec+i) = 0;
            }
            if(nbExecBefore != *(nbExec+i)){
                changed |= 1;
				nbNotReady++;
			} else {
				if(*(nbExec+i)!=0){
				    bckupNbExec[i] = *(nbExec+i);
				}
			}
        }
		printf("Ready: %d/%d\n",nbDump-nbNotReady,nbDump);
        if(changed == 0) {
            stable = 1;
			memcpy(nbExec,bckupNbExec,nbDump*sizeof(int));
			free(bckupNbExec);
            for(i=1;i<nbDump;i++){
                fprintf(stderr,"%d;\n",*(nbExec+i));
            }
//            fprintf(ptfile,"\n");
//            fflush(ptfile);
        }
    }
}
