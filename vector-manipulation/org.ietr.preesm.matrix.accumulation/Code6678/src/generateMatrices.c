/*
============================================================================
Name        : generateMatrices.c
Author      : Robert McNeill
Description : Generate matrices to be multiplied by the TI device
============================================================================
*/

#include "generateMatrices.h"
#include <stdio.h>

#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

void generate (int rows, int columns, long *startArray, double *startTime, long *countIn, long *countOut)
{
	// !!! TODO: add checking around the matrices size

	if (*countIn == 0)
	{
		printf("\n\nCross Core Accumulation Beginning\n");
	}

	int i, j, k = 0;
	Types_Timestamp64	startTime64;
	Types_FreqHz		freq;

	for (i = 0; i < rows; i++)			// Generate array A
	{
		for (j = 0; j < columns; j++)
		{
			*((startArray+i*columns) + j) = 1;
		}
	}

	if (*countIn == 0)
	{
		Timestamp_getFreq(&freq);
		Timestamp_get64(&startTime64);
		*startTime = ((startTime64.lo/(double)freq.lo));
	}

	*countOut = *countIn + 1;
}
