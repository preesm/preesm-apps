/*
============================================================================
Name        : splitMerge.c
Author      : kdesnos
Version     : 1.3
Copyright   : CECILL-C
Description :
============================================================================
*/
#include <cstring>
#include "splitMerge.h"

void split(int nbSlice, int width, int height, int overlap, unsigned char *input, unsigned char *output) {
    if (output) {
        const auto sliceSize = (width * height) / nbSlice;
        // Fill first and last line(s) with 0
        memset(output, 0, width * overlap);
        // First Slice
        memcpy(output + width * overlap, input, sliceSize);
        // Copy next line(s) if several slice
        if (nbSlice > 1) {
            memcpy(output + width * overlap + sliceSize, input + sliceSize, width * overlap);
        }
        // Slice other than first and last
        for (auto i = 1; i < nbSlice - 1; i++) {
            const auto destIndex = i * (sliceSize + 2 * width * overlap);
            memcpy(output + destIndex,
                   input + ((i * sliceSize) - (width * overlap)),
                   sliceSize + (2 * width * overlap));
        }
        // Last Slice
        if (nbSlice > 1) {
            const auto lastSlice = nbSlice - 1;
            const auto destIndex = lastSlice * (sliceSize + 2 * width * overlap);
            // we have lastSlice = nbSlice -1;
            memcpy(output + destIndex,
                   input + ((lastSlice * sliceSize) - (width * overlap)),
                   sliceSize + (width * overlap));
        }
        // Last line
        memset(output + (height + overlap * (nbSlice * 2 - 1)) * width, 0, (width * overlap));
    } else {
        // Output has been splitted and is null
        // Fill first and last line with 0
        memset(input - (width * overlap), 0, (width * overlap));
        // Last line
        memset(input + (height * width), 0, (width * overlap));
    }
}


void merge(int nbSlice, int width, int height, unsigned char *input, unsigned char *output) {
    const auto sliceSize = (width * height) / nbSlice;
    // Copy the slice content except the first and last lines
    for (auto i = 0; i < nbSlice; ++i) {
        const auto idx = i * (sliceSize + 2 * width);
        memcpy(output + (i * sliceSize), input + (idx + width), sliceSize);
    }
}
