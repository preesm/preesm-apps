/*
============================================================================
Name        : tranposeMatrix.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "transposeMatrix.h"
#include <stdio.h>

void transpose (int rowsA, int columnsA, int *input, int *output)
{
	int i, j, k;

	//printf("Array transpose started\n");

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsA; j++)
		{
			*(output+((j*columnsA) + i)) = *(input+((i*columnsA) + j));
		}
	}

	//printf("Array transpose finished\n");
}
