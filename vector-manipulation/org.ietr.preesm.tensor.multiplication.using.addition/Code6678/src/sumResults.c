/*
============================================================================
Name        : tranposeMatrix.c
Author      : Robert McNeill
Description :
============================================================================
*/

#include "sumResults.h"
#include <stdio.h>

void sum (int rowsA, int columnsB, int depthA, long *input, long *output)
{
	int i, j, k;

	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < columnsB; j++)
		{
			for (k = 0; k < 8; k++)
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
}
