/*
	============================================================================
	Name        : x86.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C
	Description : main header for x86
	============================================================================
*/

#ifndef ARM_CORTEXA7_H
#define ARM_CORTEXA7_H

#include "ARM.h"

// GCC specific! Weak attribute makes function existence testable
void *computationThread_A7_Core0(void *arg) __attribute__((weak));
void *computationThread_A7_Core1(void *arg) __attribute__((weak));
void *computationThread_A7_Core2(void *arg) __attribute__((weak));
void *computationThread_A7_Core3(void *arg) __attribute__((weak));

// Testing whether core 0 executes code or not
void emptyLoop_A7_Core0() __attribute__((weak, used));

#endif
