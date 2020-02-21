/*
 ============================================================================
 Name        : filter.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <cstring>
#include <cstdio>
#include "filter.h"

void filter(int width, int height, int filterSize, int borderSize,
            char *coefficients, int *norm, unsigned char *input,
            unsigned char *output) {
    // apply the filter
    for (auto j = borderSize; j < height - borderSize; ++j) {
        const auto currentLine = j * width;
        for (auto i = borderSize; i < width - borderSize; i++) {
            output[currentLine + i] = 0;
            for (auto k = -filterSize / 2; k < filterSize / 2; ++k) {
                const auto lineWithOffset = (j + k) * width;
                for (auto l = -filterSize / 2; l < filterSize / 2; ++l) {
                    output[currentLine + i] += input[lineWithOffset + i + l] * coefficients[k * filterSize + l];
                }
            }
            output[currentLine + i] /= (*norm);
        }

        /* == Set borders to zero == */
        memset(output + (j * width), 0, (size_t) borderSize * sizeof(char));
        memset(output + (j * width) + (width - borderSize), 0, (size_t) borderSize * sizeof(char));
    }

    /* == Set borders to zero == */
    memset(output, 0, ((size_t) (borderSize * width) * sizeof(char)));
    memset(output + (height - 2 * borderSize) * width, 0, ((size_t) (borderSize * width) * sizeof(char)));
}

