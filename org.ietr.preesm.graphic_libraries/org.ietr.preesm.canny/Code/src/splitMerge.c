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
#include <stdio.h>
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
		memcpy(destIndex, srcIndex, destSliceSize);
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

void split2(int width, int height, int nbColumn, int nbSlice,
		unsigned char *input, unsigned char *output) {
	int i, j, k;

	int sliceHeight = height / nbSlice;
	int columnWidth = width / nbColumn;
	int destColumnWidth = columnWidth + 4;
	int sliceSize = sliceHeight * width;

	unsigned char *destIndex = output;
	unsigned char *srcIndex = input;

	// If there is only one column
	if (nbColumn <= 1) {
		split(nbSlice, width, height, input, output);
		return;
	}

	// First column

	// First slice
	for (i = 0; i < sliceHeight; i++) {
		memcpy(destIndex, srcIndex + i * width, destColumnWidth);
		destIndex += destColumnWidth;
	}

	if (nbSlice > 1) {
		// Four extra lines
		for (i = sliceHeight; i < sliceHeight + 4; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}
		// Middle slices
		for (j = 1; j < nbSlice - 1; j++) {
			srcIndex += sliceSize;
			for (i = -2; i < sliceHeight + 2; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
		}
		srcIndex += sliceSize;
		// Last slice
		for (i = -4; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}
	}

	// Middle columns
	for (k = 1; k < nbColumn - 1; k++) {
		srcIndex = input + k * columnWidth - 2;
		// First slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}
		if (nbSlice > 1) {
			// Four extra lines
			for (i = sliceHeight; i < sliceHeight + 4; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
			// Middle slices
			for (j = 1; j < nbSlice - 1; j++) {
				srcIndex += sliceSize;
				for (i = -2; i < sliceHeight + 2; i++) {
					memcpy(destIndex, srcIndex + i * width, destColumnWidth);
					destIndex += destColumnWidth;
				}
			}
			srcIndex += sliceSize;
			// Last slice
			for (i = -4; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
		}
	}

	// Last column
	srcIndex = input + width - destColumnWidth;
	// First slice
	for (i = 0; i < sliceHeight; i++) {
		memcpy(destIndex, srcIndex + i * width, destColumnWidth);
		destIndex += destColumnWidth;
	}
	if (nbSlice > 1) {
		// Four extra lines
		for (i = sliceHeight; i < sliceHeight + 4; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}
		// Middle slices
		for (j = 1; j < nbSlice - 1; j++) {
			srcIndex += sliceSize;
			for (i = -2; i < sliceHeight + 2; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
		}
		srcIndex += sliceSize;
		// Last slice
		for (i = -4; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}
	}
}

void merge2(int width, int height, int nbColumn, int nbSlice,
		unsigned char *input, unsigned char *output) {
	int i, j, k;

	int sliceHeight = height / nbSlice;
	int columnWidth = width / nbColumn;
	int srcColumnWidth = columnWidth + 4;

	unsigned char *srcIndex = input;
	unsigned char *destIndex = output;

	if (nbColumn <= 1) {
		merge(nbSlice, width, height, input, output);
		return;
	}

	// First column

	// First slice
	for (i = 0; i < sliceHeight; i++) {
		memcpy(destIndex, srcIndex, columnWidth);
		destIndex += width;
		srcIndex += srcColumnWidth;
	}
	if (nbSlice > 1) {
		srcIndex += 6 * srcColumnWidth;
		// Middle slices
		for (j = 1; j < nbSlice - 1; j++) {
			for (i = 0; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex, columnWidth);
				destIndex += width;
				srcIndex += srcColumnWidth;
			}
			srcIndex += 4 * srcColumnWidth;
		}
		srcIndex += 2 * srcColumnWidth;
		// Last slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex, columnWidth);
			destIndex += width;
			srcIndex += srcColumnWidth;
		}
	}

	// Middle columns
	for (k = 1; k < nbColumn - 1; k++) {
		destIndex = output + k * columnWidth;
		// First slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + 2, columnWidth);
			destIndex += width;
			srcIndex += srcColumnWidth;
		}
		if (nbSlice > 1) {
			srcIndex += 6 * srcColumnWidth;

			// Middle slices
			for (j = 1; j < nbSlice - 1; j++) {
				for (i = 0; i < sliceHeight; i++) {
					memcpy(destIndex, srcIndex + 2, columnWidth);
					destIndex += width;
					srcIndex += srcColumnWidth;
				}
				srcIndex += 4 * srcColumnWidth;
			}
			srcIndex += 2 * srcColumnWidth;
			// Last slice
			for (i = 0; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex + 2, columnWidth);
				destIndex += width;
				srcIndex += srcColumnWidth;
			}
		}
	}

	// Last column
	destIndex = output + width - columnWidth;
	// First slice
	for (i = 0; i < sliceHeight; i++) {
		memcpy(destIndex, srcIndex + 4, columnWidth);
		destIndex += width;
		srcIndex += srcColumnWidth;
	}

	if (nbSlice > 1) {
		srcIndex += 6 * srcColumnWidth;
		// Middle slices
		for (j = 1; j < nbSlice - 1; j++) {
			for (i = 0; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex + 4, columnWidth);
				destIndex += width;
				srcIndex += srcColumnWidth;
			}
			srcIndex += 4 * srcColumnWidth;
		}
		srcIndex += 2 * srcColumnWidth;
		// Last slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + 4, columnWidth);
			destIndex += width;
			srcIndex += srcColumnWidth;
		}
	}
}

