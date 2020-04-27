#include <stdlib.h>
#include <string.h>

#include "preesm.h"
#include "yuv-information.h"

#ifdef VERBOSE

#include <stdio.h>

#endif

int preesmStopThreads = 0;

extern int nbDisplay;
extern int display_h;
extern int display_w;

int main(int argc, char **argv) {
    (void) (argc);
    (void) (argv);
    // Declarations
    static unsigned char y[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char u[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char v[(VIDEO_HEIGHT * VIDEO_WIDTH) / 4];
    static unsigned char yFiltered[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char ySub[VIDEO_HEIGHT * VIDEO_WIDTH / 4];
    static unsigned char uSub[VIDEO_HEIGHT * VIDEO_WIDTH / 16];
    static unsigned char vSub[VIDEO_HEIGHT * VIDEO_WIDTH / 16];
    static unsigned char yDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char uDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char vDisp[VIDEO_HEIGHT * VIDEO_WIDTH];
    unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    while (!preesmStopThreads) {
        // Read a frame
        readYUV(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Apply Gaussian filter
        gaussian(VIDEO_WIDTH, VIDEO_HEIGHT, y, yFiltered);

        // Sub-Sampling
        subsample(VIDEO_WIDTH, VIDEO_HEIGHT, yFiltered, ySub);
        subsample(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, u, uSub);
        subsample(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, v, vSub);

        // Up-Sampling
        upsample(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, ySub, yDisp);
        upsample(VIDEO_WIDTH / 4, VIDEO_HEIGHT / 4, uSub, uDisp);
        upsample(VIDEO_WIDTH / 4, VIDEO_HEIGHT / 4, vSub, vDisp);

        // Display sampled image
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
