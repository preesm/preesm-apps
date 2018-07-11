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

void split(int nbSlice, int width, int height, int borderSize,
		unsigned char *input, unsigned char *output) {
	int i, destIndex, srcIndex;
	int sliceSize = width * height / nbSlice;
	int copySize = sliceSize + 2 * borderSize * width;

	if (nbSlice <= 1) {
		memcpy(output, input, sliceSize);
	} else {
		// First slice
		memcpy(output, input, copySize);
		destIndex = copySize;
		srcIndex = sliceSize;

		// Slices other than first and last
		for (i = 1; i < nbSlice - 1; i++) {
			memcpy(output + destIndex, input + srcIndex - borderSize * width,
					copySize);
			destIndex += copySize;
			srcIndex += sliceSize;
		}

		// Last slice
		memcpy(output + destIndex, input + srcIndex - 2 * borderSize * width,
				copySize);
	}
}

void merge(int nbSlice, int width, int height, int borderSize,
		unsigned char *input, unsigned char *output) {
	int i;
	int sliceHeight = height / nbSlice;
	int destSliceSize = width * sliceHeight;
	int srcSliceSize = width * (sliceHeight + 2 * borderSize);

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
		memcpy(destIndex, srcIndex + borderSize * width, destSliceSize);
	}

	destIndex += destSliceSize;
	srcIndex += srcSliceSize;
	memcpy(destIndex, srcIndex + 2 * borderSize * width, destSliceSize);

}

void copyWithoutBorder(int nbSlice, int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, index;
	int sliceSize = width * height / nbSlice;

	index = 0;
	for (i = 0; i < nbSlice; i++) {
		memcpy(output + index, input + index, sliceSize);
		index += sliceSize;
	}
}

void split2(int width, int height, int nbColumn, int nbSlice, int borderSize,
		unsigned char *input, unsigned char *output) {
	int i, j, k;

	int sliceHeight = height / nbSlice;
	int columnWidth = width / nbColumn;
	int destColumnWidth = columnWidth + 2 * borderSize;
	int sliceSize = sliceHeight * width;

	unsigned char *destIndex = output;
	unsigned char *srcIndex = input;

	// If there is only one column
	if (nbColumn <= 1) {
		split(nbSlice, width, height, borderSize, input, output);
		return;
	}

	for (k = 0; k < nbColumn; k++) {
		srcIndex = input + k * columnWidth - borderSize;
		if (k == 0) {
			srcIndex += borderSize;
		}
		if (k == nbColumn - 1) {
			srcIndex -= borderSize;
		}

		// First slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + i * width, destColumnWidth);
			destIndex += destColumnWidth;
		}

		if (nbSlice > 1) {
			// Two extra lines
			for (i = sliceHeight; i < sliceHeight + 2 * borderSize; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
			// Middle slices
			for (j = 1; j < nbSlice - 1; j++) {
				srcIndex += sliceSize;
				for (i = -borderSize; i < sliceHeight + borderSize; i++) {
					memcpy(destIndex, srcIndex + i * width, destColumnWidth);
					destIndex += destColumnWidth;
				}
			}
			srcIndex += sliceSize;
			// Last slice
			for (i = -2 * borderSize; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex + i * width, destColumnWidth);
				destIndex += destColumnWidth;
			}
		}
	}
}

void merge2(int width, int height, int nbColumn, int nbSlice, int borderSize,
		unsigned char *input, unsigned char *output) {
	int i, j, k;

	int sliceHeight = height / nbSlice;
	int columnWidth = width / nbColumn;
	int srcColumnWidth = columnWidth + 2 * borderSize;
	int startIndex = 0;

	unsigned char *srcIndex = input;
	unsigned char *destIndex = output;

	if (nbColumn <= 1) {
		merge(nbSlice, width, height, borderSize, input, output);
		return;
	}

	for (k = 0; k < nbColumn; k++) {
		if (k == 0) {
			startIndex = 0;
		} else if (k > 0 && k < nbColumn - 1) {
			startIndex = borderSize;
		} else {
			startIndex = 2 * borderSize;
		}

		destIndex = output + k * columnWidth;

		// First slice
		for (i = 0; i < sliceHeight; i++) {
			memcpy(destIndex, srcIndex + startIndex, columnWidth);
			destIndex += width;
			srcIndex += srcColumnWidth;
		}
		if (nbSlice > 1) {
			srcIndex += 3 * borderSize * srcColumnWidth;
			// Middle slices
			for (j = 1; j < nbSlice - 1; j++) {
				for (i = 0; i < sliceHeight; i++) {
					memcpy(destIndex, srcIndex + startIndex, columnWidth);
					destIndex += width;
					srcIndex += srcColumnWidth;
				}
				srcIndex += 2 * borderSize * srcColumnWidth;
			}
			srcIndex += borderSize * srcColumnWidth;
			// Last slice
			for (i = 0; i < sliceHeight; i++) {
				memcpy(destIndex, srcIndex + startIndex, columnWidth);
				destIndex += width;
				srcIndex += srcColumnWidth;
			}
		}
	}
}

void copy2WithoutBorder(int width, int height, int nbColumn, int nbSlice,
		unsigned char *input, unsigned char *output) {
	int i, j;
	int columnWidth = width / nbColumn;
	unsigned char *srcIndex;
	unsigned char *destIndex;

	for (i = 0; i < nbColumn; i++) {
		srcIndex = input + i * columnWidth;
		destIndex = output + i * columnWidth;
		for (j = 0; j < nbSlice; j++) {
			memcpy(destIndex, srcIndex, columnWidth);
			srcIndex += width;
			destIndex += width;
		}
	}
}

