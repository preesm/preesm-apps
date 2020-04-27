#include <stdlib.h>
#include <string.h>

#include "preesm.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int preesmStopThreads = 0;

int main(int argc, char** argv) {
    (void) (argc);
    (void) (argv);
    // Declarations
    static unsigned char y[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char u[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char v[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
	static unsigned char yDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
	unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    while (!preesmStopThreads) {
        // Read a frame
        readYUV(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

		// Apply Gaussian filter
		gaussian(VIDEO_WIDTH, VIDEO_HEIGHT, y, yDisp);

		// Display filtered image
		yuvDisplay(0, yDisp, u, v);

		// Exit ?
		frameIndex++;
		if (frameIndex == VIDEO_FRAME_COUNT) {
            preesmStopThreads++;
		}
	}

	yuvFinalize(0);

#ifdef VERBOSE
	printf("Exit program\n");
#endif

	return 0;
}
