#include <stdio.h>
#include "subsample.h"

void subsample(int width, int height, unsigned char *input, unsigned char *output) {
	int i, j, k;

	k = 0;
	for (i = 0; i < height / 2; i++) {
		for (j = 0; j < width / 2; j++) {
			output[k++] = input[2 * i * width + 2 * j];
		}
	}
}
