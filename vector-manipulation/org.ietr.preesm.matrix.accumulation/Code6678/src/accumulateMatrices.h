/*
============================================================================
Name        : addMatrices.c
Author      : Robert McNeill
Description :
============================================================================
*/

#ifndef ADDMATRICES_H_
#define ADDMATRICES_H_

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
*/

void add (int rows, int columns, long *runningTotal, long *inputArray, long *output);
#endif /* ADDMATRICES_H_ */
