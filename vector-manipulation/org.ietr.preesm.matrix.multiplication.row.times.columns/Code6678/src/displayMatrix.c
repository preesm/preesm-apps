/*
============================================================================
Name        : displayMatrix.h
Author      : Robert McNeill
Version		: 1.0
Description : Display resulting matrix from the multiplication
============================================================================
*/

#include "displayMatrix.h"
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>
#include <xdc/std.h>
#include <stdio.h>

void display (int rowsA, int columnsB, long *arrayC, double *startTime)
{
	int 				i, j = 0;
	Types_Timestamp64	endTime64;			// 64 bit timestamp
	Types_FreqHz		freq;				// Core frequency
	unsigned long long	endClockCycles;		// Storage for the ending clock cycles
	double				endTime, timeTaken;	// Storage for actual times

	Timestamp_get64(&endTime64);			// Take the finishing timestamp
	Timestamp_getFreq(&freq);				// Take the frequency
	endClockCycles = ((endTime64.hi*4294967296) + endTime64.lo);	// Calculate the ending clock cycles
	endTime = ((endClockCycles/(double)freq.lo));		// Convert to time
	timeTaken = endTime - *startTime;		// Calculate overall execution time

	printf ("\nResulting Array: \n");		// Information message

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsB; j++)
		{
			printf("%ld\t", *((arrayC+i*columnsB) + j));	// Print resulting array
		}
		printf("\n");
	}

	printf("\nMultiplication of %d square matrices took %fs and %llu clock cycles\n", rowsA , timeTaken, endClockCycles);
						// Display overall execution statistics
	exit(0);
}
