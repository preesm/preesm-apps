#include "upsample.h"

void upsample(int width, int height, unsigned char *input,
		unsigned char *output) {
	int output_w = width * 2;
	int a = 0;
	int b = output_w;
	int i, j, k;

	k = 0;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			output[a] = output[a + 1] = output[b] = output[b + 1] = input[k++];
			a += 2;
			b += 2;
		}
		a += output_w;
		b += output_w;
	}
}
