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
	static unsigned char yDisp[HEIGHT * WIDTH];
	static char coefficients[KERNEL_SIZE * KERNEL_SIZE];
	static unsigned char norm;
	unsigned int frameIndex = 1;

	// Init display
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readY(WIDTH, HEIGHT, y, u, v);

		// Set coefficients
		setCoefficients(coefficients, &norm);

		// Convolution
		convolution(WIDTH, HEIGHT, KERNEL_SIZE, BORDER_SIZE, coefficients,
				&norm, y, yDisp);

		// Display filtered image
		yuvDisplay(0, yDisp, u, v);

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
