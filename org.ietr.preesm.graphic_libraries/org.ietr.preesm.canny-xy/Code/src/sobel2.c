/*
 ============================================================================
 Name        : sobel.c
 Author      : kdesnos
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
	int i, j;

	// Apply the filter
	for (j = 1; j < height - 1; j++) {
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

			output_x[j * width + i] = gx;
			output_y[j * width + i] = gy;
		}
	}

	// Fill the left and right sides
	for (j = 0; j < height; j++) {
		output_x[j * width] = output_y[j * width] = 0;
		output_x[(j + 1) * width - 1] = output_y[(j + 1) * width - 1] = 0;
	}
}
