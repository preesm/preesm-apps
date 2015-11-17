/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "accumulateMatrices.h"
#include <stdio.h>


void add (int rows, int columns, long *runningTotal, long *inputArray, long *output)
{
	int i, k , j;

	for (i = 0; i < rows/8; i++)
	{
		for (j = 0; j < columns; j++)
		{
			*((output+i*columns) + j) = (*((runningTotal+i*columns) + j) + *((inputArray+i*columns) + j));
		}
	}
}
