/*
 ============================================================================
 Name        : medianFilter.h
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C, IETR, INSA Rennes
 Description : Application of a 3x3 median filter to an image.
 ============================================================================
 */

#include "medianFilter.h"
#include <algorithm>
#include <cstring>

#define SWAP(x, y) ((x ^= y), (y ^= x), (x ^= y))
#define SORT(a, b) { if ((a)>(b)) std::swap((a),(b)); }

unsigned char median(unsigned char *p) {
    SORT(p[1], p[2]);
    SORT(p[4], p[5]);
    SORT(p[7], p[8]);
    SORT(p[0], p[1]);
    SORT(p[3], p[4]);
    SORT(p[6], p[7]);
    SORT(p[1], p[2]);
    SORT(p[4], p[5]);
    SORT(p[7], p[8]);
    SORT(p[0], p[3]);
    SORT(p[5], p[8]);
    SORT(p[4], p[7]);
    SORT(p[3], p[6]);
    SORT(p[1], p[4]);
    SORT(p[2], p[5]);
    SORT(p[4], p[7]);
    SORT(p[4], p[2]);
    SORT(p[6], p[4]);
    SORT(p[4], p[2]);
    return (p[4]);
}

void medianFilter(int height, int width, unsigned char *rawDisparity, unsigned char *filteredDisparity) {
    // Process pixels one by one
    for (auto j = 1; j < height - 1; ++j) {
        for (auto i = 1; i < width - 1; ++i) {
            unsigned char pixels[9];
            // output pixel is the median of a 3x3 window
            // Get the 9 pixels
            memcpy(pixels, rawDisparity + (j - 1) * width + i - 1, 3);
            memcpy(pixels, rawDisparity + j * width + i - 1, 3);
            memcpy(pixels, rawDisparity + (j + 1) * width + i - 1, 3);
            // Sort the 9 values
            filteredDisparity[(j - 1) * width + i] = median(pixels);
        }

    }
}
