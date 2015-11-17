/*
============================================================================
Name        : generateMatrices.c
Author      : Robert McNeill
Version		: 1.0
Description : Generate matrices to be multiplied by the TI device
============================================================================
*/

#ifndef GENERATEMATRICES_H_
#define GENERATEMATRICES_H_

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
*        Pointer to where the generated arrayA should be stored
* @param arrayB
*        Pointer to where the generated arrayB should be stored
* @param startTime
*        Pointer to where the starting time should be stored - used in profiling
*/

void generate (int rowsA, int columnsA, int rowsB, int columnsB, long *arrayA, long *arrayB, double *startTime);
#endif /* GENERATEMATRICES_H_ */
