#include <stdlib.h>
#include <string.h>

#include "preesm.h"

// #define VERBOSE
#ifdef VERBOSE

#include <stdio.h>

#endif

#define KERNEL_SIZE 3
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
    static char coefficients[KERNEL_SIZE * KERNEL_SIZE];
    static unsigned char norm;
    unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);


    while (!preesmStopThreads) {
        // Read a frame
        readYComponent(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Set coefficients
        setCoefficients(coefficients, &norm);

        // Convolution
        convolution(VIDEO_WIDTH, VIDEO_HEIGHT, KERNEL_SIZE, BORDER_SIZE, coefficients, &norm, y, yDisp);

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
    fprintf(stderr, "Exit program\n");
#endif

    return 0;
}
