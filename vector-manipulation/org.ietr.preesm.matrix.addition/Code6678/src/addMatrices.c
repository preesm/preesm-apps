/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "addMatrices.h"
#include <stdio.h>


void add (int rowsA, int columnsA, long *arrayA, long *arrayB, long *arrayC)
{
	int i, k , j;

	for (i = 0; i < rowsA/8; i++)
	{
		for (j = 0; j < columnsA; j++)
		{
			*((arrayC+i*columnsA) + j) = (*((arrayA+i*columnsA) + j) + *((arrayB+i*columnsA) + j));
		}
	}
}
