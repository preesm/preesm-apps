#include <stdlib.h>
#include <string.h>

#include "preesm.h"

#ifdef VERBOSE

#include <stdio.h>

#endif

/**
 * Filter size
 */
#define FILTER_SIZE	3

/**
 * Border size
 */
#define BORDER_SIZE 1

int preesmStopThreads = 0;

int main(int argc, char **argv) {
    (void) (argc);
    (void) (argv);
    // Declarations
    static unsigned char y[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char u[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char v[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char yDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
    static char coefficients[FILTER_SIZE * FILTER_SIZE];
    static unsigned char norm;
    unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    while (!preesmStopThreads) {
        // Read a frame
        readYUV(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Set the filter coefficients
        setCoefficients(coefficients, &norm);

        // Apply the filter
        filter(VIDEO_WIDTH, VIDEO_HEIGHT, FILTER_SIZE, BORDER_SIZE, coefficients, &norm, y, yDisp);

        // Display filtered image
        yuvDisplay(0, yDisp, u, v);

        // MD5 check
        MD5_Update(VIDEO_WIDTH * VIDEO_HEIGHT, yDisp);

        // Exit ?
        frameIndex++;
        if (frameIndex == VIDEO_FRAME_COUNT) {
            preesmStopThreads++;
        }
    }

    yuvFinalize();

#ifdef VERBOSE
    printf("Exit program\n");
#endif

    return 0;
}
