/*
	============================================================================
	Name        : x86.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C
	Description : main header for x86
	============================================================================
*/

#ifndef ARM_CORTEXA15_H
#define ARM_CORTEXA15_H

#include "ARM.h"

// GCC specific! Week attribute makes function existence testable
void *computationThread_A15_Core4(void *arg) __attribute__((weak));
void *computationThread_A15_Core5(void *arg) __attribute__((weak));
void *computationThread_A15_Core6(void *arg) __attribute__((weak));
void *computationThread_A15_Core7(void *arg) __attribute__((weak));

#endif
