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
	
#ifdef _WIN32
#include <windows.h>
#include <pthread.h>
#else
// For Linux
// Pthread barriers are defined in POSIX 2001 version
// For the 1990 revision compliance the defined value of _POSIX_VERSION should be 1.
// For the 1995 revision compliance the defined value of _POSIX_VERSION should be 199506L.
// For the 2001 revision compliance the defined value of _POSIX_VERSION should be 200112L.
#if ((defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 600) || \
     !defined _XOPEN_SOURCE)
#define _XOPEN_SOURCE 600
#endif
#if !defined _POSIX_C_SOURCE
#if (defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 700)
#define _POSIX_C_SOURCE 200112L
#elif (defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 800)
#define _POSIX_C_SOURCE 200809L
#endif
#endif
#include <pthread.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <semaphore.h>

#include "communication.h"
#include "fifo.h"
#include "dump.h"

#include "yuvRead.h"
#include "yuvDisplay.h"
#include "sobel.h"
#include "splitMerge.h"
#include "morph.h"

typedef unsigned char uchar;

#endif
