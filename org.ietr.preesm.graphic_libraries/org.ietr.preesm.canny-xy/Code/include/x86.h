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
#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 600
#include <pthread.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <semaphore.h>

#include "communication.h"
#include "fifo.h"
#include "dump.h"
#include "md5.h"

#include "yuvRead.h"
#include "yuvDisplay.h"
#include "sobel2.h"
#include "splitMerge2.h"
#include "canny.h"

typedef unsigned char uchar;

#endif
