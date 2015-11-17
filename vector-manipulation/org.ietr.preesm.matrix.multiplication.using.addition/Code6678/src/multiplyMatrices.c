/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "multiplyMatrices.h"
#include <xdc/runtime/Timestamp.h>
#include <stdio.h>


void multiply (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, long *output)
{
	int i, j, k;

	//printf("Array multiplication started\n");

	for (i = 0; i < (rowsA*columnsB); i++)
	{
		*(output+i) = 0;
	}

	for (i = 0; i < columnsB; i++)
	{
		for (j = 0; j < rowsA; j++)
		{
			for (k = 0; k < columnsB/8; k++)
			{
				*(output+((j*columnsB) + i)) = *(output+((j*columnsB) + i)) + ((*(arrayA+((k*rowsA) + j))) * (*(arrayB+((k*columnsB) + i))));
			}
		}
	}

	//printf("Array multiplication finished\n");
}
