/*
 ============================================================================
 Name        : splitMerge.c
 Author      : kdesnos
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <string.h>
#include <stdlib.h>

#include "splitMerge.h"

void split(int nbSlice, int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, destIndex, srcIndex;
	int sliceSize = width * height / nbSlice;
	int copySize = sliceSize + 4 * width;

	if (nbSlice <= 1) {
		memcpy(output, input, sliceSize);
	} else {
		// First slice
		memcpy(output, input, sliceSize + 4 * width);
		destIndex = copySize;
		srcIndex = sliceSize;

		// Slices other than first and last
		for (i = 1; i < nbSlice - 1; i++) {
			memcpy(output + destIndex, input + srcIndex - 2 * width, copySize);
			destIndex += copySize;
			srcIndex += sliceSize;
		}

		// Last slice
		memcpy(output + destIndex, input + srcIndex - 4 * width, copySize);
	}
}

void merge(int nbSlice, int width, int height, unsigned char *input,
		unsigned char *output) {
	int i;
	int sliceHeight = height / nbSlice;
	int destSliceSize = width * sliceHeight;
	int srcSliceSize = width * (sliceHeight + 4);

	unsigned char *destIndex = output;
	unsigned char *srcIndex = input;

	if (nbSlice <= 1) {
		memcpy(destIndex, srcIndex, destSliceSize - 2 * width);
		memset(destIndex + destSliceSize - 2 * width, 0, 2 * width);
		return;
	}

	memcpy(destIndex, srcIndex, destSliceSize);

	for (i = 1; i < nbSlice - 1; i++) {
		destIndex += destSliceSize;
		srcIndex += srcSliceSize;
		memcpy(destIndex, srcIndex + 2 * width, destSliceSize);
	}

	destIndex += destSliceSize;
	srcIndex += srcSliceSize;
	memcpy(destIndex, srcIndex + 4 * width, destSliceSize);

}
