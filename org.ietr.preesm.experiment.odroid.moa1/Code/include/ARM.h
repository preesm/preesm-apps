/*
	============================================================================
	Name        : x86.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C
	Description : main header for x86
	============================================================================
*/

#ifndef ARM_H
#define ARM_H

// For Linux
// Pthread barriers are defined in POSIX 2001 version
// For the 1990 revision compliance the defined value of _POSIX_VERSION should be 1.
// For the 1995 revision compliance the defined value of _POSIX_VERSION should be 199506L.
// For the 2001 revision compliance the defined value of _POSIX_VERSION should be 200112L.
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <semaphore.h>

#include "communication.h"
#include "fifo.h"
#include "dump.h"

#include "testcom.h"

typedef unsigned char uchar;


// Stopping the main loop after N iterations
#define LOOP_SIZE 1000

#endif
