/*
============================================================================
Name        : tranposeMatrix.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "transposeTensor.h"
#include <stdio.h>

void transpose (int rowsA, int columnsA, int depthA, int *input, int *output)
{
	int i, j, k;

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsA; j++)
		{
			*(output+((j*columnsA) + i)) = *(input+((i*columnsA) + j));
		}
	}
}
