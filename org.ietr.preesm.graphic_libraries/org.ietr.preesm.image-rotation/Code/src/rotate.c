#include "rotate.h"

void rotateClockWise(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j, m, n;

	n = 0;
	for (i = 0; i < width; i++) {
		m = (height - 1) * width + i;
		for (j = 0; j < height; j++) {
			output[n++] = input[m];
			m -= width;
		}
	}
}

void rotateCounterClockWise(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j, m, n;

	n = 0;
	for (i = width - 1; i >= 0; i--) {
		m = i;
		for (j = 0; j < height; j++) {
			output[n++] = input[m];
			m += width;
		}
	}
}
