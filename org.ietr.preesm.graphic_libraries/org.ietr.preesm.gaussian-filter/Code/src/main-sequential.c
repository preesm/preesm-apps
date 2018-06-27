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
	static char gx[HEIGHT * WIDTH], gy[HEIGHT * WIDTH];
	static unsigned char yDisp[HEIGHT * WIDTH];
	unsigned int frameIndex = 1;

	// Init display
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readYUV(WIDTH, HEIGHT, y, u, v);

		// Apply Gaussian filter
		gaussian(WIDTH, HEIGHT, y, yDisp);

		// Display filtered image
		yuvDisplay(0, yDisp, u, v);

		// MD5 check
		MD5_Update(WIDTH * HEIGHT, yDisp);

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
