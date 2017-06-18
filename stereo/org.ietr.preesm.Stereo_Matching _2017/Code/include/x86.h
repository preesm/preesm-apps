/*
	============================================================================
	Name        : x86.h
	Author      : kdesnos
	Version     :
	Copyright   :
	Description :
	============================================================================
*/

#ifndef X86_H
#define X86_H

#define VERBOSE
#define LOOP_SIZE 1

#ifdef _WIN32
#include <windows.h>
#include <pthread.h>
#else
// For Linux
// Pthread barriers are defined in POSIX 2001 version
// For the 1990 revision compliance the defined value of _POSIX_VERSION should be 1.
// For the 1995 revision compliance the defined value of _POSIX_VERSION should be 199506L.
// For the 2001 revision compliance the defined value of _POSIX_VERSION should be 200112L.
#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 600
#include <pthread.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <string.h>
#include <semaphore.h>

#include "communication.h"
#include "fifo.h"
#include "dump.h"
#include "clock.h"

#include "load_images_PREESM.h"
#include "census_PREESM_parallel.h"
#include "bp1d_PREESM.h"
#include "save_image_PREESM.h"
#include "image.h"
#include "split_merge.h"
#include "mux.h"
#include "wta_selection_parallel.h"
#include "sad_cost_parallel.h"
#include "no_aggregation.h"
#include "bfa_aggregation_parallel.h"



typedef unsigned char uchar;

void *computationThread_Core0(void *arg);
void *computationThread_Core1(void *arg);
void *computationThread_Core2(void *arg);
void *computationThread_Core3(void *arg);
void *computationThread_Core4(void *arg);
void *computationThread_Core5(void *arg);
void *computationThread_Core6(void *arg);
void *computationThread_Core7(void *arg);
void *computationThread_Core8(void *arg);
void *computationThread_Core9(void *arg);
void *computationThread_Core10(void *arg);
void *computationThread_Core11(void *arg);

clock_t t1;

#endif
