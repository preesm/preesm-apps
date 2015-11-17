/*
============================================================================
Name        : displayMatrix.h
Author      : Robert McNeill
Description : Display resulting matrix from the multiplication
============================================================================
*/

#include "displayMatrix.h"
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>
#include <stdio.h>

void display (int rowsA, int columnsB, long *arrayC, double *startTime)
{
	int 				i, j = 0;
	Types_Timestamp64	endTime64;
	Types_FreqHz		freq;
	unsigned long long	endClockCycles;
	double				endTime, timeTaken;

	Timestamp_get64(&endTime64);
	Timestamp_getFreq(&freq);
	endClockCycles = ((endTime64.hi * 4294967296) + endTime64.lo);
	endTime = (endClockCycles/(double)freq.lo);
	timeTaken = endTime - *startTime;

/*
	printf ("\nResulting Array: \n");

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsB; j++)
		{
			printf("%ld\t", *(arrayC+((i*columnsB) + j)));
		}
		printf("\n");
	}
*/

	printf("\nMultiplication of %d square matrices took %fs and %llu clock cycles\n", rowsA, timeTaken, endClockCycles);

	exit(0);
}
