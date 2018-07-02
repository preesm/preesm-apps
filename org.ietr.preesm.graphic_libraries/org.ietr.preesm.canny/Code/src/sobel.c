/*
 ============================================================================
 Name        : sobel.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <string.h>
#include <stdlib.h>

#include "sobel2.h"

void sobel2(int width, int height, unsigned char *input, char *output_x,
		char *output_y) {
	int i, j, k;

	memset(output_x, 0, width);
	memset(output_y, 0, width);
	k = width;
	// Apply the filter
	for (j = 1; j < height - 1; j++) {
		output_x[k] = 0;
		output_y[k] = 0;
		k++;
		for (i = 1; i < width - 1; i++) {
			int gx = -input[(j - 1) * width + i - 1]
					- 2 * input[j * width + i - 1]
					- input[(j + 1) * width + i - 1]
					+ input[(j - 1) * width + i + 1]
					+ 2 * input[j * width + i + 1]
					+ input[(j + 1) * width + i + 1];
			int gy = -input[(j - 1) * width + i - 1]
					- 2 * input[(j - 1) * width + i]
					- input[(j - 1) * width + i + 1]
					+ input[(j + 1) * width + i - 1]
					+ 2 * input[(j + 1) * width + i]
					+ input[(j + 1) * width + i + 1];

			output_x[k] = gx;
			output_y[k] = gy;
			k++;
		}
		output_x[k] = 0;
		output_y[k] = 0;
		k++;
	}
	memset(output_x + k, 0, width);
	memset(output_y + k, 0, width);
}

