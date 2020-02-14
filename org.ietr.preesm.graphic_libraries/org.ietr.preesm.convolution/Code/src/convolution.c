/*
 ============================================================================
 Name        : convolution.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <string.h>
#include <stdlib.h>

#include "convolution.h"

void convolution(int width, int height, int kernelSize, int borderSize,
                 char *coefficients, unsigned char *norm, unsigned char *input,
                 unsigned char *output) {
    int i, j, k;
    int a, b, c;
    int res;

    k = 0;
    for (i = 0; i < borderSize * width; i++) {
        output[k++] = 0;
    }

    // apply the kernel
    for (j = 0; j < height - 2 * borderSize; j++) {
        for (i = 0; i < borderSize; i++) {
            output[k++] = 0;
        }
        for (i = 0; i < width - 2 * borderSize; i++) {
            res = 0;
            c = 0;
            for (a = kernelSize - 1; a >= 0; a--) {
                for (b = kernelSize - 1; b >= 0; b--) {
                    res += input[(j + a) * width + i + b] * coefficients[c++];
                }
            }
            res /= (*norm);
            output[k++] = res;
        }
        for (i = 0; i < borderSize; i++) {
            output[k++] = 0;
        }
    }

    for (i = 0; i < borderSize * width; i++) {
        output[k++] = 0;
    }
}
