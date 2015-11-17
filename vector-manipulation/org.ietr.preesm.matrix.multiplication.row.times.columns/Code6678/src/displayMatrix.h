/*32
============================================================================
Name        : displayMatrix.h
Author      : Robert McNeill
Version		: 1.0
Description : Display resulting matrix from the multiplication
============================================================================
*/

#ifndef DISPLAYMATRIX_H_
#define DISPLAYMATRIX_H_

/**
* Display resulting matrix from the multiplication
*
* @param rowsA
*        The number of rows in arrayC
* @param columnsB
*        The number of columns in arrayC
* @param arrayC
*        The resulting array from arrayA * arrayB
* @param startTime
*		 Contains the start time of the multiplication
*/

void display (int rowsA, int columnsB, long *arrayC, double *startTime);

#endif /* DISPLAYMATRIX_H_ */
