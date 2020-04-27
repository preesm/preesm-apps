#include "laneFilter.h"

void laneFilter(int width, int height, IN unsigned char *input,
		OUT unsigned char *output) {
	int i, j, k;

	k = 0;
	for (i = 0; i < width; i++) {
		if (input[k] > THD && input[k + width] > THD) {
			output[k++] = 255;
		} else {
			output[k++] = 0;
		}
	}

	for (j = 1; j < height - 1; j++) {
		for (i = 0; i < width; i++) {
			if (input[k] > THD && input[k - width] > THD
					&& input[k + width] > THD) {
				output[k++] = 255;
			} else {
				output[k++] = 0;
			}
		}
	}

	for (i = 0; i < width; i++) {
		if (input[k] > THD && input[k - width] > THD) {
			output[k++] = 255;
		} else {
			output[k++] = 0;
		}
	}
}
