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

void generate (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, double *startTime)
{
	// !!! TODO: add checking around the matrices size

	printf("\n\nCross core multiplication beginning of %d square matrices\n", rowsA);

	int 				generationCount = 1;
	Types_Timestamp64	startTime64;
	Types_FreqHz		freq;

	unsigned int generateEndTime;
	int i, j = 0;

	for (i = 0; i < rowsA; i++)			// Generate array A
	{
		for (j = 0; j < columnsA; j++)
		{
			*(arrayA+((i*columnsA) + j)) = (generationCount);
		}
		generationCount++;
	}

	generationCount = 1;

	for (i = 0; i < rowsB; i++)			// Generate array B
	{
		for (j = 0; j < columnsB; j++)
		{
			*(arrayB+((i*columnsB) + j)) = (generationCount);
		}
		generationCount++;
	}

	Timestamp_getFreq(&freq);
	Timestamp_get64(&startTime64);
	*startTime = ((startTime64.lo/(double)freq.lo));
}
