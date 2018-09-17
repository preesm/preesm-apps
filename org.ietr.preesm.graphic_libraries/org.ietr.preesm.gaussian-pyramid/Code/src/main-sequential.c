#include <stdlib.h>
#include <string.h>

#include "preesm.h"
#include "applicationParameters.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int stopThreads = 0;

extern int nbDisplay;
extern int display_h;
extern int display_w;

int main(int argc, char** argv) {
	// Declarations
	static unsigned char y[HEIGHT * WIDTH], u[HEIGHT * WIDTH / 4], v[HEIGHT
			* WIDTH / 4];
	static unsigned char yFiltered[HEIGHT * WIDTH];
	static unsigned char ySub[HEIGHT * WIDTH / 4], uSub[HEIGHT * WIDTH / 16],
			vSub[HEIGHT * WIDTH / 16];
	static unsigned char yDisp[HEIGHT * WIDTH], uDisp[HEIGHT * WIDTH],
			vDisp[HEIGHT * WIDTH];
	unsigned int frameIndex = 1;

	// Init display
	yuvDisplayInit(0, 1, WIDTH, HEIGHT, WIDTH, HEIGHT);
	// Init read
	initReadYUV(WIDTH, HEIGHT);

	while (!stopThreads) {
		// Read a frame
		readYUV(WIDTH, HEIGHT, y, u, v);

		// Apply Gaussian filter
		gaussian(WIDTH, HEIGHT, y, yFiltered);

		// Sub-Sampling
		subsample(WIDTH, HEIGHT, yFiltered, ySub);
		subsample(WIDTH / 2, HEIGHT / 2, u, uSub);
		subsample(WIDTH / 2, HEIGHT / 2, v, vSub);

		// Up-Sampling
		upsample(WIDTH / 2, HEIGHT / 2, ySub, yDisp);
		upsample(WIDTH / 4, HEIGHT / 4, uSub, uDisp);
		upsample(WIDTH / 4, HEIGHT / 4, vSub, vDisp);

		// Display sampled image
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
