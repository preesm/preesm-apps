#include "yuv-display.h"
#include "yuv-read.h"
#include "sobel.h"
#include "harris.h"
#include "md5.h"

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
    static char gx[VIDEO_HEIGHT * VIDEO_WIDTH];
    static char gy[VIDEO_HEIGHT * VIDEO_WIDTH];
    static unsigned char yDisp[VIDEO_HEIGHT * VIDEO_WIDTH];

    // Init display
    yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);
    // Init read
    initReadYUV(VIDEO_WIDTH, VIDEO_HEIGHT);

    unsigned int frameIndex = 1;
    while (!preesmStopThreads) {
        // Read a frame
        readYComponent(VIDEO_WIDTH, VIDEO_HEIGHT, y, u, v);

        // Apply Sobel filter
        sobel_raw(VIDEO_WIDTH, VIDEO_HEIGHT, y, gx, gy);

        // Apply Harris detector
        harris(VIDEO_WIDTH, VIDEO_HEIGHT, y, gx, gy, yDisp);

        // Display filtered image
        yuvDisplay(0, yDisp, u, v);

        // Md5 update
        // MD5_Update(WIDTH * HEIGHT, yDisp);

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
