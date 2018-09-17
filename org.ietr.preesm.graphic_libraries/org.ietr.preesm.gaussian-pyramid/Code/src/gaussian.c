/*
 ============================================================================
 Name        : gaussian.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <string.h>
#include <stdio.h>
#include "gaussian.h"

void gaussian(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j;
	int a, b, c;
	int res;

	// apply the filter
	for (j = 1; j < height - 1; j++) {
		a = (j - 1) * width;
		b = a + width;
		c = b + width;
		for (i = 1; i < width - 1; i++) {
			res = input[a + i - 1] + 2 * input[a + i] + input[a + i + 1]
					+ 2 * input[b + i - 1] + 4 * input[b + i]
					+ 2 * input[b + i + 1] + input[c + i - 1] + 2 * input[c + i]
					+ input[c + i + 1];
			res /= 16;
			output[b + i] = res;
		}
	}
}
