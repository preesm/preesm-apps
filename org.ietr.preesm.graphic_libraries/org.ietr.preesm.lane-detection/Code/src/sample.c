#include "sample.h"

void subSample(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j, m, n;

	m = n = 0;
	for (j = 0; j < height; j += 2) {
		for (i = 0; i < width; i += 2) {
			output[n++] = input[m];
			m += 2;
		}
		m += width;
	}
}

void upSample(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j, m, n;

	m = n = 0;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			output[n] = output[n + 1] = output[n + width] =
					output[n + width + 1] = input[m++];
			n += 2;
		}
		n += 2 * width;
	}
}
