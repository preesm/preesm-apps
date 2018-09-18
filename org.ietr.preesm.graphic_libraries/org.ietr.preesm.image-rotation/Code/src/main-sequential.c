#include <stdlib.h>
#include <string.h>

#include "applicationParameters.h"
#include "preesm.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int stopThreads = 0;

int main(int argc, char **argv) {
	// Declarations
	static unsigned char y[HEIGHT * WIDTH], u[HEIGHT * WIDTH / 4], v[HEIGHT
			* WIDTH / 4];
	static unsigned char yRotated[HEIGHT * WIDTH], uRotated[HEIGHT * WIDTH / 4],
			vRotated[HEIGHT * WIDTH / 4];
	static unsigned char yDisp[HEIGHT * WIDTH], uDisp[HEIGHT * WIDTH / 4],
			vDisp[HEIGHT * WIDTH / 4];
	unsigned int frameIndex = 1;

	// Init display
	yuvDisplayInit(0,WIDTH, HEIGHT, WIDTH, HEIGHT);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readYUV(WIDTH, HEIGHT, y, u, v);

		// Rotate Y
		rotateClockWise(WIDTH, HEIGHT, y, yRotated);
		rotateClockWise(HEIGHT, WIDTH, yRotated, yDisp);

		// Rotate U
		rotateClockWise(WIDTH / 2, HEIGHT / 2, u, uRotated);
		rotateClockWise(HEIGHT / 2, WIDTH / 2, uRotated, uDisp);

		// Rotate V
		rotateClockWise(WIDTH / 2, HEIGHT / 2, v, vRotated);
		rotateClockWise(HEIGHT / 2, WIDTH / 2, vRotated, vDisp);

		// Display filtered image
		yuvDisplay(0, yDisp, uDisp, vDisp);

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
