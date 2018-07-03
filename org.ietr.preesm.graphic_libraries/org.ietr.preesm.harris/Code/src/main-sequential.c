#include <stdlib.h>
#include <string.h>

#include "applicationParameters.h"
#include "yuvDisplay.h"
#include "yuvRead.h"
#include "yuvWrite.h"
#include "sobel2.h"
#include "harris.h"
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

	// Init display
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);

	// Open files
	initReadYUV(WIDTH, HEIGHT);
	initYUVWrite();

	unsigned int frameIndex = 1;
	while (!stopThreads) {
		// Read a frame
		readY(WIDTH, HEIGHT, y, u, v);

		// Apply Sobel filter
		sobel2(WIDTH, HEIGHT, y, gx, gy);

		// Apply Harris detector
		harris(WIDTH, HEIGHT, y, gx, gy, yDisp);

		// Display filtered image
		yuvDisplay(0, yDisp, u, v);

		// save it
		yuvWrite(WIDTH, HEIGHT, yDisp, u, v);

		// Md5 update
		MD5_Update(WIDTH * HEIGHT, yDisp);

		// Exit ?
		frameIndex++;
		if (frameIndex == NB_FRAME) {
			stopThreads++;
		}
	}

#ifdef VERBOSE
	printf("Exit program\n");
#endif
	yuvFinalize(0);
	endYUVWrite();

	return 0;
}
