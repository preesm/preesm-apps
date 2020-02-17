#include "ipm.h"
#include <stdio.h>

void ipm(int width, int height, int x11, int x12, int x21, int x22, int y1,
		int y2, unsigned char *input, unsigned char *output) {
	int frame_w1 = x12 - x11;
	int frame_w2 = x22 - x21;
	int frame_h = y2 - y1;

	int k = 0;
	memset(output, 0, (size_t) (width * height));
	for (int j = 0; j < height; j++) {
		int x_set = (x11 + (j * (x21 - x11)) / height) +
		            (y1 + (j * frame_h) / height) * width);
		int frame_w = frame_w1 + (j * (frame_w2 - frame_w1)) / height;
		for (int i = 0; i < width; i++) {
			output[k++] = input[x_set + (i * frame_w) / width];
		}
	}
}

void ipmReverse(int width, int height, int x11, int x12, int x21, int x22, int y1,
		int y2, unsigned char *input, unsigned char *output) {
	int frame_w1 = x12 - x11;
	int frame_w2 = x22 - x21;
	int frame_h = y2 - y1;
	int k = 0;
	memset(output, 0, (size_t) (width * height));
	for (int j = 0; j < height; ++j) {
		int x_set = (x11 + (j * (x21 - x11)) / height) +
		            (y1 + (j * frame_h) / height) * width);
		int frame_w = frame_w1 + (j * (frame_w2 - frame_w1)) / height;
		for (int i = 0; i < width; ++i) {
			output[x_set + (i * frame_w) / width] = input[k++];
		}
	}
}
