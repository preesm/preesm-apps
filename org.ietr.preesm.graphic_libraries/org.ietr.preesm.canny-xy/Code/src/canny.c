/*
 ============================================================================
 Name        : canny.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "canny.h"

void canny(int width, int height, char *gx, char *gy, unsigned char *output) {
	int i, j, k;
	int current, neighbour1, neighbour2;
	int current_x, current_y;
	char neighbour1_x, neighbour1_y;
	char neighbour2_x, neighbour2_y;
	double arg;
	double t1 = PI / 8;
	double t2 = 3 * t1;
	double t3 = 5 * t1;
	double t4 = 7 * t1;

	k = 0;
	// Apply the filter
	for (i = 0; i < width; i++) {
		output[k++] = 0;
	}
	for (j = 1; j < height - 1; j++) {
		output[k++] = 0;
		for (i = 1; i < width - 1; i++) {
			current_x = gx[k];
			current_y = gy[k];

			current = current_x * current_x + current_y * current_y;
			arg = atan2(current_y, current_x);

			if ((arg >= -t1 && arg < t1) || arg >= t4 || arg < -t4) {
				neighbour1_x = gx[k - width];
				neighbour1_y = gy[k - width];
				neighbour2_x = gx[k + width];
				neighbour2_y = gy[k + width];
			} else if ((arg >= t1 && arg < t2) || (arg >= -t4 && arg < -t3)) {
				neighbour1_x = gx[k - width - 1];
				neighbour1_y = gy[k - width - 1];
				neighbour2_x = gx[k + width + 1];
				neighbour2_y = gy[k + width + 1];
			} else if ((arg >= -t3 && arg < -t2) || (arg >= t2 && arg < t3)) {
				neighbour1_x = gx[k - 1];
				neighbour1_y = gy[k - 1];
				neighbour2_x = gx[k + 1];
				neighbour2_y = gy[k + 1];
			} else {
				neighbour1_x = gx[k - width + 1];
				neighbour1_y = gy[k - width + 1];
				neighbour2_x = gx[k + width - 1];
				neighbour2_y = gy[k + width - 1];
			}

			neighbour1 = neighbour1_x * neighbour1_x
					+ neighbour1_y * neighbour1_y;
			neighbour2 = neighbour2_x * neighbour2_x
					+ neighbour2_y * neighbour2_y;

			if (current > neighbour1&& current > neighbour2
			&& current > LOW_THRESHOLD && current < HIGH_THRESHOLD) {
				output[k] = 255;
			} else {
				output[k] = 0;
			}

			k++;
		}
		output[k++] = 0;
	}
	for (i = 0; i < width; i++) {
		output[k++] = 0;
	}
}
