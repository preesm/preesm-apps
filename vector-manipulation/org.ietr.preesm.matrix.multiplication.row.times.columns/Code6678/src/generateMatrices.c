/*
============================================================================
Name        : generateMatrices.c
Author      : Robert McNeill
Version		: 1.0
Description : Generate matrices to be multiplied by the TI device
============================================================================
*/

#include "generateMatrices.h"
#include <stdio.h>

#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

void generate (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, double *startTime)
{
	printf("\n\nCross Core Multiplication Beginning\n");	// Print information message

	int generationCount = 1;		// Used in generation of the arrays
	int i, j = 0;					// Used to count rows and columns of the arrays
	Types_Timestamp64	startTime64;	// 64 bit timestamp
	Types_FreqHz		freq;			// frequency of cores

	for (i = 0; i < rowsA; i++)			// Generate array A
	{
		for (j = 0; j < columnsA; j++)
		{
			*((arrayA+i*columnsA) + j) = (generationCount);		// Initialise arrayA
		}
		generationCount++;
	}

	generationCount = 1;

	for (i = 0; i < rowsB; i++)			// Generate array B
	{
		for (j = 0; j < columnsB; j++)
		{
			*((arrayB+i*columnsB) + j) = (generationCount);		// Initialise arrayB
		}
		generationCount++;
	}

	Timestamp_getFreq(&freq);		// Get the frequency of the cores
	Timestamp_get64(&startTime64);	// Get the starting timestamp
	*startTime = ((startTime64.lo/(double)freq.lo));	// Calculate a time in seconds for use in timestamping
}
