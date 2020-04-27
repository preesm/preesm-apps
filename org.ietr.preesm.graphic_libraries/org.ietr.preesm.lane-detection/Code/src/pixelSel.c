#include "pixelSel.h"

void pixelSel(int width, int height, unsigned char *laneY,
		unsigned char *imageY, unsigned char *imageU, unsigned char *imageV,
		unsigned char *y, unsigned char *u, unsigned char *v) {
	int i, j, k;

	k = 0;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			if (laneY[k]) {
				y[k] = 76;
				u[k] = 84;
				v[k] = 255;
			} else {
				y[k] = imageY[k];
				u[k] = imageU[k];
				v[k] = imageV[k];
			}
			k++;
		}
	}
}
