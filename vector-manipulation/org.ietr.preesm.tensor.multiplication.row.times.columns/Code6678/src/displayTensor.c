/*
============================================================================
Name        : displayMatrix.h
Author      : Robert McNeill
Description : Display resulting matrix from the multiplication
============================================================================
*/

#include "displayTensor.h"
#include <stdio.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

void display (int rowsA, int columnsB, int depthA, long *arrayC, double *startTime)
{
	long i, j, k = 0;
	Types_Timestamp64	endTime64;
	Types_FreqHz		freq;
	unsigned long long	endClockCycles;
	double				endTime, timeTaken;

	Timestamp_get64(&endTime64);
	Timestamp_getFreq(&freq);
	endClockCycles = ((endTime64.hi*4294967296) + endTime64.lo);
	endTime = ((endClockCycles/(double)freq.lo));
	timeTaken = endTime - *startTime;
/*
	printf("Resulting array:\n");
	for (i = 0; i < depthA; i++)			// Print result of multiplication
	{
		printf("Depth: %i\n", i);
		for (j = 0; j < rowsA; j++)
		{
			for (k = 0; k < columnsB; k++)
			{
				printf("%d\t", *((arrayC+i*rowsA*columnsB+j*rowsA) + k));
			}
			printf("\n");
		}
		printf("\n");
	}
*/
	printf("\nMultiplication of %d square matrices of depth %d took %fs\n", rowsA, depthA, timeTaken);

	exit(0);
}
