#include <stdlib.h>
#include <string.h>

#include "applicationParameters.h"
#include "yuvDisplay.h"
#include "yuvRead.h"
#include "gaussian.h"
#include "md5.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int stopThreads = 0;

int main(int argc, char** argv) {
	// Declarations
	static unsigned char y[HEIGHT * WIDTH], u[HEIGHT * WIDTH / 4], v[HEIGHT
			* WIDTH / 4];
	static unsigned char yFiltered[HEIGHT * WIDTH];
	static unsigned char yDisp[HEIGHT * WIDTH / 4], uDisp[HEIGHT * WIDTH / 16],
			vDisp[HEIGHT * WIDTH / 16];
	unsigned int frameIndex = 1;
	int scale = 2;

	// Init display
	yuvDisplayInit(0, DISPLAY_W / scale, DISPLAY_H / scale, scale);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readYUV(WIDTH, HEIGHT, y, u, v);

		// Apply Gaussian filter
		gaussian(WIDTH, HEIGHT, y, yFiltered);

		// Sampling
		subsample(WIDTH, HEIGHT, yFiltered, yDisp);
		subsample(WIDTH / 2, HEIGHT / 2, u, uDisp);
		subsample(WIDTH / 2, HEIGHT / 2, v, vDisp);

		// Display sampled image
		yuvDisplay(0, yDisp, uDisp, vDisp);

		// MD5 check
		MD5_Update(WIDTH * HEIGHT / 4, yDisp);

		// Exit ?
		frameIndex++;
		if (frameIndex == NB_FRAME) {
			stopThreads++;
		}
	}

	yuvFinalize(0);

#ifdef VERBOSE
	printf("Exit program\n");
#endif

	return 0;
}
