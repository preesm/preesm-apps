/*
	============================================================================
	Name        : main.c
	Author      : kdesnos mpelcat
	Version     : 1.0
	Copyright   : CECILL-C
	Description : Launching the threads of the application on ARM and forcing them
                      to different cores
	============================================================================
*/

// Includes for setting core affinity
#define _GNU_SOURCE
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <sched.h>

#include <unistd.h>
#include "ARM_CortexA7.h"
#include "ARM_CortexA15.h"

pthread_barrier_t iter_barrier;
int stopThreads;

// setting a setting core affinity
int set_affinity_to_core(pthread_t* thread, int core_id) {
   int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
   if (core_id < 0 || core_id >= num_cores)
      printf("Wrong core number %d\n", core_id);

   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id, &cpuset);

   return pthread_setaffinity_np(*thread, sizeof(cpu_set_t), &cpuset);
}

int main(void)
{
    int nb_threads = 0; // number of active threads set by Preesm

    // Declaring thread pointers
    pthread_t threadCore0;
    pthread_t threadCore1;
    pthread_t threadCore2;
    pthread_t threadCore3;
    pthread_t threadCore4;
    pthread_t threadCore5;
    pthread_t threadCore6;
    pthread_t threadCore7;

    printf("Launched main\n");

    // computing the number of active threads set by Preesm
    if(computationThread_A7_Core0 && !emptyLoop_A7_Core0){
        nb_threads++;
    }
    if(computationThread_A7_Core1){
        nb_threads++;
    }
    if(computationThread_A7_Core2){
        nb_threads++;
    }
    if(computationThread_A7_Core3){
        nb_threads++;
    }
    if(computationThread_A15_Core4){
        nb_threads++;
    }
    if(computationThread_A15_Core5){
        nb_threads++;
    }
    if(computationThread_A15_Core6){
        nb_threads++;
    }
    if(computationThread_A15_Core7){
        nb_threads++;
    }

    // Creating a synchronization barrier
    pthread_barrier_init(&iter_barrier, NULL, nb_threads);

    communicationInit();

    // Creating threads A7 cluster
    if(computationThread_A7_Core0  && !emptyLoop_A7_Core0){
      pthread_create(&threadCore0, NULL, computationThread_A7_Core0, NULL);
      set_affinity_to_core(&threadCore0,0);
    }
    if(computationThread_A7_Core1){
      pthread_create(&threadCore1, NULL, computationThread_A7_Core1, NULL);
      set_affinity_to_core(&threadCore1,1);
    }
    if(computationThread_A7_Core2){
      pthread_create(&threadCore2, NULL, computationThread_A7_Core2, NULL);
      set_affinity_to_core(&threadCore2,2);
    }
    if(computationThread_A7_Core3){
      pthread_create(&threadCore3, NULL, computationThread_A7_Core3, NULL);
      set_affinity_to_core(&threadCore3,3);
    }

    // Creating threads A15 cluster
    if(computationThread_A15_Core4){
      pthread_create(&threadCore4, NULL, computationThread_A15_Core4, NULL);
      set_affinity_to_core(&threadCore4,4);
    }
    if(computationThread_A15_Core5){
      pthread_create(&threadCore5, NULL, computationThread_A15_Core5, NULL);
      set_affinity_to_core(&threadCore5,5);
    }
    if(computationThread_A15_Core6){
      pthread_create(&threadCore6, NULL, computationThread_A15_Core6, NULL);
      set_affinity_to_core(&threadCore6,6);
    }
    if(computationThread_A15_Core7){
      pthread_create(&threadCore7, NULL, computationThread_A15_Core7, NULL);
      set_affinity_to_core(&threadCore7,7);
    }

// Waiting for thread terminations
    if(computationThread_A7_Core0 && !emptyLoop_A7_Core0){
    	pthread_join(threadCore0,NULL);
    }
    if(computationThread_A7_Core1){
    	pthread_join(threadCore1,NULL);
    }
    if(computationThread_A7_Core2){
    	pthread_join(threadCore2,NULL);
    }
    if(computationThread_A7_Core3){
    	pthread_join(threadCore3,NULL);
    }
    if(computationThread_A15_Core4){
    	pthread_join(threadCore4,NULL);
    }
    if(computationThread_A15_Core5){
    	pthread_join(threadCore5,NULL);
    }
    if(computationThread_A15_Core6){
    	pthread_join(threadCore6,NULL);
    }
    if(computationThread_A15_Core7){
    	pthread_join(threadCore7,NULL);
    }

    printf("Finished main\n");
    exit(0);
}
