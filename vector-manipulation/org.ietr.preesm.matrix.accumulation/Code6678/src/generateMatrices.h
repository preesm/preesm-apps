/*
============================================================================
Name        : generateMatrices.h
Author      : Robert McNeill
Description : Generate matrices to be multiplied by the TI device
============================================================================
*/

#ifndef GENERATEMATRICES_H_
#define GENERATEMATRICES_H_

/**
* Generate the matrices to be multiplied by the 8 cores.
*
* @param rows
*        The number of rows in startArray
* @param columns
*        The number of columns in startArray
*/

void generate (int rows, int columns, long *startArray, double *startTime, long *countIn, long *countOut);
#endif /* GENERATEMATRICES_H_ */
