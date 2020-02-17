#include "interpolate.h"

void interpolate(int width, int height, unsigned char *input, unsigned char *output) {
	int k = 0;
	for (int j = 0; j < height; j++) {
		output[k] = input[k + 1];
		k++;
		for (int i = 1; i < width - 1; i++) {
			int res = (((int) input[k - 1]) + ((int) input[k + 1])) / 2;
			output[k++] = (unsigned char) res;
		}
		output[k] = input[k - 1];
		k++;
	}
}
