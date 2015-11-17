/*
============================================================================
Name        : transposeMatrix.c
Author      : Robert McNeill
Description :
============================================================================
*/

#ifndef TRANSPOSEMATRIX_H_
#define TRANSPOSEMATRIX_H_

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

void transpose (int rowsA, int columnsA, int depthA, int *input, int *output);
#endif /* TRANSPOSEMATRIX_H_ */
