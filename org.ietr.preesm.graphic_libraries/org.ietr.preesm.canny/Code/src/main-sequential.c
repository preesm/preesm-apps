#include <stdlib.h>
#include <string.h>

#include "applicationParameters.h"
#include "preesm.h"

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
	unsigned int frameIndex = 1;

	// Init display
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readY(WIDTH, HEIGHT, y, u, v);

		// Apply Sobel filter
		sobel2(WIDTH, HEIGHT, y, gx, gy);

		// Apply Harris detector
		canny(WIDTH, HEIGHT, gx, gy, y);

		// Display filtered image
		yuvDisplay(0, y, u, v);

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
