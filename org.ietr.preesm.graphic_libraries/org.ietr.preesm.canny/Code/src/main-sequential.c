#include "preesm.h"
#include "yuv-read.h"
#include "yuv-display.h"

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
    static char gx[VIDEO_HEIGHT * VIDEO_WIDTH];
    static char gy[VIDEO_HEIGHT * VIDEO_WIDTH];
    unsigned int frameIndex = 1;

    // Init display
    yuvDisplayInit(0, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    while (!preesmStopThreads) {
        // Read a frame
        readYComponent(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Apply Sobel filter
        sobel_raw(VIDEO_WIDTH, VIDEO_HEIGHT, y, gx, gy);

        // Apply Canny filter
        canny(VIDEO_WIDTH, VIDEO_HEIGHT, gx, gy, y);

        // Display filtered image
        yuvDisplay(0, y, u, v);

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
