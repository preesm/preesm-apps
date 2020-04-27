#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "preesm.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int preesmStopThreads = 0;

int main(int argc, char **argv) {
    (void) (argc);
    (void) (argv);
    // Declarations
    static unsigned char y[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char u[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char v[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char yRotated[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char uRotated[VIDEO_HEIGHT * VIDEO_WIDTH / 4];
    static unsigned char vRotated[VIDEO_HEIGHT * VIDEO_WIDTH / 4];
    static unsigned char yDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char uDisp[VIDEO_HEIGHT * VIDEO_WIDTH / 4];
    static unsigned char vDisp[VIDEO_HEIGHT * VIDEO_WIDTH / 4];
    unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    while (!preesmStopThreads) {
        // Read a frame
        readYUV(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Rotate Y
        rotateClockWise(VIDEO_WIDTH, VIDEO_HEIGHT, y, yRotated);
        rotateClockWise(VIDEO_HEIGHT, VIDEO_WIDTH, yRotated, yDisp);

        // Rotate U
        rotateClockWise(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, u, uRotated);
        rotateClockWise(VIDEO_HEIGHT / 2, VIDEO_WIDTH / 2, uRotated, uDisp);

        // Rotate V
        rotateClockWise(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, v, vRotated);
        rotateClockWise(VIDEO_HEIGHT / 2, VIDEO_WIDTH / 2, vRotated, vDisp);

        // Display filtered image
        yuvDisplay(0, yDisp, uDisp, vDisp);

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
