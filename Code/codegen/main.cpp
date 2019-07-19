/**
 * @file main.c
 * @generated by CPrinter
 * @date Fri Jul 19 09:20:01 CEST 2019
 *
 */
// no monitoring by default

#define _PREESM_NBTHREADS_ 1
#define _PREESM_MAIN_THREAD_ 0

// application dependent includes
#include "preesm_gen.h"

// Declare computation thread functions
void *computationThread_Core0(void *arg);

pthread_barrier_t iter_barrier;
int preesmStopThreads;


unsigned int launch(unsigned int core_id, pthread_t * thread, void *(*start_routine) (void *)) {

	// init pthread attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

#ifndef PREESM_NO_AFFINITY
#ifdef _WIN32
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	unsigned int numCPU = sysinfo.dwNumberOfProcessors;
#else
	unsigned int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
#endif

	// check CPU id is valid
	if (core_id >= numCPU) {
		// leave attribute uninitialized
		printf("** Warning: thread %d will not be set with specific core affinity \n   due to the lack of available dedicated cores.\n",core_id);
	} else {
#if defined __APPLE__ || defined _WIN32
		// NOT SUPPORTED
#else
		// init cpuset struct
		cpu_set_t cpuset;
		CPU_ZERO(&cpuset);
		CPU_SET(core_id, &cpuset);

		// set pthread affinity
		pthread_attr_setaffinity_np(&attr, sizeof(cpuset), &cpuset);
#endif
	}
#endif

	// create thread
	pthread_create(thread, &attr, start_routine, NULL);
	return 0;
}


int main(void) {
	// Set affinity of main thread to proper core ID
#ifndef PREESM_NO_AFFINITY
#if defined __APPLE__ || defined _WIN32
	// NOT SUPPORTED
#else
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(_PREESM_MAIN_THREAD_, &cpuset);
	sched_setaffinity(getpid(),  sizeof(cpuset), &cpuset);
#endif
#endif

	// Declaring thread pointers
	pthread_t coreThreads[_PREESM_NBTHREADS_];
	void *(*coreThreadComputations[_PREESM_NBTHREADS_])(void *) = {
		&computationThread_Core0
	};

#ifdef PREESM_VERBOSE
	printf("Launched main\n");
#endif

	// Creating a synchronization barrier
	preesmStopThreads = 0;
	pthread_barrier_init(&iter_barrier, NULL, _PREESM_NBTHREADS_);

	communicationInit();

	// Creating threads
	for (int i = 0; i < _PREESM_NBTHREADS_; i++) {
		if (i != _PREESM_MAIN_THREAD_) {
			if(launch(i,&coreThreads[i],coreThreadComputations[i])) {
				printf("Error: could not launch thread %d\n",i);
				return 1;
			}
		}
	}

	// run main operator code in this thread
	coreThreadComputations[_PREESM_MAIN_THREAD_](NULL);

	// Waiting for thread terminations
	for (int i = 0; i < _PREESM_NBTHREADS_; i++) {
		if (i != _PREESM_MAIN_THREAD_) {
			pthread_join(coreThreads[i], NULL);
		}
	}

	return 0;
}

