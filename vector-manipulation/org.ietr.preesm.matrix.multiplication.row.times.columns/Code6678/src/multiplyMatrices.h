/*
============================================================================
Name        : multiplyMatrices.c
Author      : Robert McNeill
Version		: 1.0
Description : Multiplies the 2 matrices generated in generateMatrices.c
			  This is the function that is parallelised across the 8 cores.
============================================================================
*/

#ifndef MULTIPLYMATRICES_H_
#define MULTIPLYMATRICES_H_

/**
* Generate the matrices to be multiplied by the 8 cores.
*
* @param rowsA
*        The number of rows in arrayA
* @param columnsA
*        The number of columns in arrayA
* @param rowsB
*        The number of rows in arrayB
* @param columnsB
*        The number of columns in arrayB
* @param arrayA
*        Input arrayA
* @param arrayB
*        Input arrayB
* @param output
* 		 Output for the resultant multiplication
*/

void multiply (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, long *output);
#endif /* MULTIPLYMATRICES_H_ */
