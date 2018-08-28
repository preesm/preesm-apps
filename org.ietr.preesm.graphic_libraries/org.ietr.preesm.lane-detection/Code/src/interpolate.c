#include "interpolate.h"

void interpolate(int width, int height, unsigned char *input,
		unsigned char *output) {
	int i, j, k;
	int res;

	for (j = 0; j < height; j++) {
		output[k] = input[k + 1];
		k++;
		for (i = 1; i < width - 1; i++) {
			res = (((int) input[k - 1]) + ((int) input[k + 1])) / 2;
			output[k++] = (unsigned char) res;
		}
		output[k] = input[k - 1];
		k++;
	}
}
