/*
 ============================================================================
 Name        : filter.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <string.h>
#include <stdio.h>
#include "filter.h"

void filter(int width, int height, int filterSize, int borderSize,
		char *coefficients, unsigned char *norm, unsigned char *input,
		unsigned char *output) {
	int i, j, k;
	int a, b, c;
	int res;

	k = 0;
	for (i = 0; i < borderSize * width; i++) {
		output[k++] = 0;
	}

	// apply the filter
	for (j = 0; j < height - 2 * borderSize; j++) {
		for (i = 0; i < borderSize; i++) {
			output[k++] = 0;
		}
		for (i = 0; i < width - 2 * borderSize; i++) {
			res = 0;
			c = 0;
			for (a = 0; a < filterSize; a++) {
				for (b = 0; b < filterSize; b++) {
					res += input[(j + a) * width + i + b] * coefficients[c++];
				}
			}
			res /= (*norm);
			output[k++] = res;
		}
		for (i = 0; i < borderSize; i++) {
			output[k++] = 0;
		}
	}

	for (i = 0; i < borderSize * width; i++) {
		output[k++] = 0;
	}
}
