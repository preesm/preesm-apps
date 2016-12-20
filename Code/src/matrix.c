/**
* Matrix and vectors related functions
*
* @file matrix.c
* @author kdesnos
* @date 2016.09.01
* @version 1.0
* @copyright CECILL-C
*/

#include <stdlib.h>
#include <math.h>

#include "matrix.h"

#define PI (3.141592653589793f)

void meanVector(const unsigned int nbVector, const coord * const vectors,
				coordf * const mean){
	long x = 0, y = 0;
	for (const coord * vec = vectors; vec < vectors + nbVector; vec++){
		x += vec->x;
		y += vec->y;
	}

	mean->x = x / (float)nbVector;
	mean->y = y / (float)nbVector;
}

void covarianceMatrix2D(const unsigned int nbVector, const coord * const vectors,
						const coordf * const mean, matrix * const sigma){

	coordf *temp = malloc(nbVector*sizeof(coordf));

	// Substract mean to all vectors
	for (unsigned int i = 0; i < nbVector; i++){
		(temp + i)->x = (vectors + i)->x - mean->x;
		(temp + i)->y = (vectors + i)->y - mean->y;
	}

	// Compute Sigma
	// sigma(row,col) = temp(row)' * temp(col)
	sigma->coeffs[0] = 0.0;
	sigma->coeffs[1] = 0.0;
	sigma->coeffs[2] = 0.0;
	sigma->coeffs[3] = 0.0;
	for (unsigned int c = 0; c < nbVector; c++){
		sigma->coeffs[0] += (temp + c)->x * (temp + c)->x;
		sigma->coeffs[1] += (temp + c)->x * (temp + c)->y;
		// sigma->coeffs[2] += equal to coeffs[1]
		sigma->coeffs[3] += (temp + c)->y * (temp + c)->y;
	}

	// mean
	sigma->coeffs[0] /= (nbVector - 1);
	sigma->coeffs[1] /= (nbVector - 1);
	sigma->coeffs[2] = sigma->coeffs[1];
	sigma->coeffs[3] /= (nbVector - 1);

	// free temp vectors
	free(temp);
}

void getProbabilities(const unsigned int nbVector, const coord * const vectors,
					  const coordf * const mean, matrix * const sigma, float * proba){
	// Compute sigma determinant and inverse
	float detSigma = sigma->coeffs[0] * sigma->coeffs[3] - sigma->coeffs[2] * sigma->coeffs[1];
	matrix invSigma;

	// If the multivariate gaussian can be computed.
	if (detSigma > 0.0f){
		inverseMatrix2D(sigma, &invSigma);

		// pre compute denominator
		const float divisor = 1.0f / sqrtf(4.0f * PI * PI * detSigma);

		// Loop over the vectors to compute probability
		for (unsigned int i = 0; i < nbVector; i++){
			const coord *vec = vectors + i;
			// Substract mean value
			float tX = vec->x - mean->x;
			float tY = vec->y - mean->y;

			// multiply by invSigma
			float sigmaTX = invSigma.coeffs[0] * tX + invSigma.coeffs[2] * tY;
			float sigmaTY = invSigma.coeffs[1] * tX + invSigma.coeffs[3] * tY;

			// Proba
			*(proba + i) = expf(-((tX*sigmaTX) + (tY*sigmaTY)) / 2) * divisor;
		}
	}
	// If the multivariata gaussian cannot be computed
	else {
		// Find the dimension of the two dimensions that has a null variance.
		const int dimension = (sigma->coeffs[0] == 0.0 && sigma->coeffs[3] == 0.0) ?
			0 : ((sigma->coeffs[0] == 0.0) ? 1 : 2);

		// compute the probabilities for the dimension with non zero variance (if any).
		if (dimension == 0){
			// all vectors are identical
			for (unsigned int i = 0; i < nbVector; i++){
				proba[i] = 1.0;
			}
		}
		else {
			// keep variance
			const float var = (dimension == 2) ? sigma->coeffs[0] : sigma->coeffs[3];
			// pre compute denominator
			const float divisor = 1.0f / (sqrtf(2.0f * PI) * var);

			// Loop over the vectors to compute probability
			for (unsigned int i = 0; i < nbVector; i++){
				float val = (dimension == 2) ? vectors[i].x - mean->x : vectors[i].y - mean->y;
				proba[i] = expf(-(val*val) / (2 * var))*divisor;
			}
		}
	}
}

inverseMatrix2D(const matrix * const mat, matrix * const invMat){
	float detMat = mat->coeffs[0] * mat->coeffs[3] - mat->coeffs[2] * mat->coeffs[1];

	invMat->coeffs[0] = mat->coeffs[3] / detMat;
	invMat->coeffs[1] = -mat->coeffs[1] / detMat;
	invMat->coeffs[2] = -mat->coeffs[2] / detMat;
	invMat->coeffs[3] = mat->coeffs[0] / detMat;
}