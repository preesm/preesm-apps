/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Version		: 1.0
Description : Multiplies the 2 matrices generated in generateMatrices.c
			  This is the function that is parallelised across the 8 cores.
============================================================================
*/

#include "multiplyMatrices.h"
#include <xdc/runtime/Timestamp.h>
#include <xdc/std.h>
#include <stdio.h>


void multiply (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, long *output)
{
	int i, j, k;

	for (i = 0; i < (rowsA/8*columnsB); i++)
	{
		*(output+i) = 0;						// Initialise the output array
	}

	for (i = 0; i < (rowsA/8); i++)
	{
		for (j = 0; j < columnsB; j++)
		{
			for (k = 0; k < columnsA; k++)
			{										// Perform the row x columns multiplication
				*((output+i*columnsB) + j) = ((*((output+i*columnsB) + j)) + ((*((arrayA+i*columnsA) + k)) * (*((arrayB+k*columnsB) + j))));
			}
		}
	}
}
