/*
============================================================================
Name        : tranposeMatrix.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "sumResults.h"
#include <stdio.h>

void sum (int rowsA, int columnsB, int *input, int *output)
{
	int i, j, k;

	//printf("Array sum started\n");

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsB; j++)
		{
			for (k = 0; k < 8; k++)				//BELOW SECTION WRONG
			{
				if (k == 0)
				{
					*(output+((i*columnsB) + j)) = *(input+(i*columnsB + j));
				}
				else
				{
					*(output+((i*columnsB) + j)) = (*(output+((i*columnsB + j))) + *(input+(((i*columnsB) + (k*rowsA*columnsB)) + j)));
				}
			}
		}
	}

	//printf("Array sum finished\n");
}
