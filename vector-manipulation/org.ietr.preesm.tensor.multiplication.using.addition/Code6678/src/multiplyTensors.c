/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "multiplyTensors.h"
#include <xdc/runtime/Timestamp.h>
#include <stdio.h>


void multiply (int rowsA, int columnsA, int depthA, int rowsB, int columnsB, int depthB, int *arrayA, int *arrayB, long *arrayC)
{
	int i, j, k;

	for (i = 0; i < columnsB; i++)
	{
		for (j = 0; j < rowsA; j++)
		{
			for (k = 0; k < columnsB/8; k++)
			{
				if (k == 0)
				{
					*(arrayC+((j*columnsB) + i)) = ((*(arrayA+((k*rowsA) + j))) * (*(arrayB+((k*columnsB) + i))));
				}
				else
				{
					*(arrayC+((j*columnsB) + i)) = *(arrayC+((j*columnsB) + i)) + ((*(arrayA+((k*rowsA) + j))) * (*(arrayB+((k*columnsB) + i))));
				}
			}
		}
	}
}
