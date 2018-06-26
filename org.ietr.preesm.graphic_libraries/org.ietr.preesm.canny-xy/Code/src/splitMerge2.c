/*
 ============================================================================
 Name        : splitMerge.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "splitMerge2.h"

void split2(int width, int height, int nbColumn, int nbSlice,
		unsigned char *input, unsigned char *output) {
	int i, j;

	int sliceSize = height / nbSlice;
	int columnSize = width / nbColumn;

	unsigned char *destIndex = output;
	unsigned char *srcIndex = input;

	// First column

	// First line: zero padding
	memset(destIndex, '0', columnSize + 2);
	destIndex += (columnSize + 2);

	for (j = 0; j < height; j++) {
		// Left column: zero padding
		memset(destIndex, '0', 1);
		memcpy(destIndex + 1, srcIndex, columnSize);

		/**
		 * If there are more than one column, the right column
		 * is the left column of the neighbor block; otherwise,
		 * zero padding at the right column.
		 */
		if (nbColumn > 1) {
			memcpy(destIndex + columnSize + 1, srcIndex + columnSize, 1);
		} else {
			memset(destIndex + columnSize + 1, '0', 1);
		}
		destIndex += (columnSize + 2);

		/**
		 * At the last line of each block, two additional lines
		 * are inserted for the filters: one for the current block
		 * and another for the next block.
		 */
		if (j < (height - 1) && (j + 1) % sliceSize == 0) {
			memset(destIndex, '0', 1);
			memcpy(destIndex + 1, srcIndex + width, columnSize);
			memset(destIndex + columnSize + 2, '0', 1);
			memcpy(destIndex + columnSize + 3, srcIndex, columnSize);
			if (nbColumn > 1) {
				memcpy(destIndex + columnSize + 1,
						srcIndex + width + columnSize, 1);
				memcpy(destIndex + columnSize + columnSize + 3,
						srcIndex + columnSize, 1);
			} else {
				memset(destIndex + columnSize + 1, '0', 1);
				memset(destIndex + columnSize + columnSize + 3, '0', 1);
			}
			destIndex += (columnSize + 2) * 2;
		}
		srcIndex += width;
	}
	// Last line: zero padding
	memset(destIndex, '0', columnSize + 2);
	destIndex += (columnSize + 2);

	// Middle columns (if there are more than two columns)
	for (i = 1; i < nbColumn - 1; i++) {
		srcIndex = input + i * columnSize;
		// First line: zero padding
		memset(destIndex, '0', columnSize + 2);
		destIndex += (columnSize + 2);

		for (j = 0; j < height; j++) {
			memcpy(destIndex, srcIndex - 1, columnSize + 2);
			destIndex += (columnSize + 2);

			if (j < (height - 1) && (j + 1) % sliceSize == 0) {
				memcpy(destIndex, srcIndex + width - 1, columnSize + 2);
				destIndex += (columnSize + 2);
				memcpy(destIndex, srcIndex - 1, columnSize + 2);
				destIndex += (columnSize + 2);
			}
			srcIndex += width;
		}
		// Last line: zero padding
		memset(destIndex, '0', columnSize + 2);
		destIndex += (columnSize + 2);
	}

	// Last column
	if (nbColumn > 1) {
		srcIndex = input + width - columnSize;
		// First line: zero padding
		memset(destIndex, '0', columnSize + 2);
		destIndex += (columnSize + 2);

		for (j = 0; j < height; j++) {
			memcpy(destIndex, srcIndex - 1, columnSize + 1);
			memset(destIndex + columnSize + 1, '0', 1);
			destIndex += (columnSize + 2);

			if (j < (height - 1) && (j + 1) % sliceSize == 0) {
				memcpy(destIndex, srcIndex + width - 1, columnSize + 1);
				memset(destIndex + columnSize + 1, '0', 1);
				destIndex += (columnSize + 2);
				memcpy(destIndex, srcIndex - 1, columnSize + 1);
				memset(destIndex + columnSize + 1, '0', 1);
				destIndex += (columnSize + 2);
			}
			srcIndex += width;
		}

		// Last line: zero padding
		memset(destIndex, '0', columnSize + 2);
		destIndex += (columnSize + 2);
	}
}

void merge2(int width, int height, int nbColumn, int nbSlice,
		unsigned char *input, unsigned char *output) {
	int i, j;

	int sliceSize = height / nbSlice;
	int columnSize = width / nbColumn;

	unsigned char *srcIndex = input;
	unsigned char *destIndex;

	for (i = 0; i < nbColumn; i++) {
		// First line: zero padding
		srcIndex += (columnSize + 2);
		destIndex = output + i * columnSize;

		for (j = 0; j < height; j++) {
			memcpy(destIndex, srcIndex + 1, columnSize);
			srcIndex += (columnSize + 2);
			destIndex += width;
			if ((j + 1) % sliceSize == 0 && j < (height - 1)) {
				srcIndex += (columnSize + 2) * 2;
			}
		}
		// Last line: zero padding
		srcIndex += (columnSize + 2);
	}
}
