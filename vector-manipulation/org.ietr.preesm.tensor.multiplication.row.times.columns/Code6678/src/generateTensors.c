/*
============================================================================
Name        : generateMatrices.c
Author      : Robert McNeill
Description : Generate matrices to be multiplied by the TI device
============================================================================
*/

#include "generateTensors.h"
#include <stdio.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

void generate (int rowsA, int columnsA, int depthA, int rowsB, int columnsB, int depthB, int *arrayA, int *arrayB, double *startTime)
{
	long generationCount = 1;
	int i, j, k = 0;

	Types_Timestamp64	startTime64;
	Types_FreqHz		freq;

	printf("\n\nCross Core Multiplication Beginning\n");


	for (i = 0; i < depthA; i++)			// Generate array A
	{
		for (j = 0; j < rowsA; j++)
		{
			for (k = 0; k < columnsA; k++)
			{
				*((arrayA+i*rowsA*columnsA+j*rowsA) + k) = generationCount;
			}
			generationCount++;
		}
		generationCount = 1;
	}

	for (i = 0; i < depthB; i++)			// Generate array B
	{
		for (j = 0; j < rowsB; j++)
		{
			for (k = 0; k < columnsB; k++)
			{
				*((arrayB+i*rowsB*columnsB+j*rowsB) + k) = generationCount;
			}
			generationCount++;
		}
		generationCount = 1;
	}

	Timestamp_getFreq(&freq);
	Timestamp_get64(&startTime64);
	*startTime = ((startTime64.lo/(double)freq.lo));
}
