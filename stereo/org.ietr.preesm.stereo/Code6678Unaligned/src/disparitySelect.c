/*
 ============================================================================
 Name        : disparitySelect.c
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C, IETR, INSA Rennes
 Description : Iterative selection of the disparity with the lowest cost for
 each pixel in order to construct the depth map.
 ============================================================================
 */

#include "utils.h"
#include "disparitySelect.h"
#include <string.h>

#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)<(y))?(y):(x))

void disparitySelect(int height, int width, int nbDisparities, int scale,
		unsigned char *disparity, float *aggregatedDisparity,
		float *bestCostFeed, unsigned char *currentResult,
		unsigned char *result, float *backBestCost) {
	int i, j;
	int nIter;

	// Special processng for the first iteration
	if (LOAD_INT(bestCostFeed+height*width) == 0) {
		// Copy the input aggregated disparity in the feedback
		memcpy((char*) backBestCost, (char*) aggregatedDisparity,
				height * width * sizeof(float));
		// Fill the result map with minDisparity
		memset(result, 0, height * width * sizeof(char));
	} else {
		// For all other iterations
		// Scan the pixels of the aggregated disparity
		for (j = 0; j < height; j++) {
			for (i = 0; i < width; i++) {
				float cost;
				// If the cost of the aggregated disparity is lower, keep the new
				// disparity as the best, else, keep te current.
				result[j * width + i] =
						(LOAD_FLOAT(&aggregatedDisparity[j*width+i])
								< LOAD_FLOAT(&bestCostFeed[j*width+i])) ?
								scale * (*disparity) :
								currentResult[j * width + i];
				cost =
						min(LOAD_FLOAT(&aggregatedDisparity[j*width+i]),LOAD_FLOAT(&bestCostFeed[j*width+i]));
				STORE_FLOAT(&backBestCost[j*width+i], &cost);

			}
		}
	}
	nIter = (LOAD_INT(bestCostFeed+height*width) + 1) % nbDisparities;
	STORE_INT(backBestCost+height*width, &nIter);
}
