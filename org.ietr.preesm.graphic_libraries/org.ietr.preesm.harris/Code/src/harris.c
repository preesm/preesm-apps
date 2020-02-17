/*
 ============================================================================
 Name        : harris.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include "harris.h"

/**
 * Constant used to normalize the results of sobel filter.
 * HARRIS_NORM_FACTOR = 3060. * 3060. = 9363600.
 */
#define HARRIS_NORM_FACTOR    9363600.

void harris(int width, int height, unsigned char *y, char *Ix, char *Iy, unsigned char *output) {
    for (int  j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int a = (j - 1) * width + i;
            int b = a + width;
            int c = b + width;

            // Components in the x-kernel
            int x11 = Ix[a - 1];
            int x12 = Ix[a];
            int x13 = Ix[a + 1];
            int x21 = Ix[b - 1];
            int x22 = Ix[b];
            int x23 = Ix[b + 1];
            int x31 = Ix[c - 1];
            int x32 = Ix[c];
            int x33 = Ix[c + 1];

            // Components in the y-kernel
            int y11 = Iy[a - 1];
            int y12 = Iy[a];
            int y13 = Iy[a + 1];
            int y21 = Iy[b - 1];
            int y22 = Iy[b];
            int y23 = Iy[b + 1];
            int y31 = Iy[c - 1];
            int y32 = Iy[c];
            int y33 = Iy[c + 1];

            // Component 1-1 in the Harris matrix
            double m11 = x11 * x11 + x12 * x12 + x13 * x13 + x21 * x21
                         + x22 * x22 + x23 * x23 + x31 * x31 + x32 * x32 + x33 * x33;

            m11 /= HARRIS_NORM_FACTOR;

            // Component 2-2 in the Harris matrix
            double m22 = y11 * y11 + y12 * y12 + y13 * y13 + y21 * y21
                         + y22 * y22 + y23 * y23 + y31 * y31 + y32 * y32 + y33 * y33;

            m22 /= HARRIS_NORM_FACTOR;

            // Component 1-2 in the Harris matrix
            double m12 = x11 * y11 + x12 * y12 + x13 * y13 + x21 * y21
                         + x22 * y22 + x23 * y23 + x31 * y31 + x32 * y32 + x33 * y33;

            m12 /= HARRIS_NORM_FACTOR;

            // Determinant of the Harris matrix
            double det = m11 * m22 - m12 * m12;
            // Trace of the Harris matrix
            double trace = m11 + m22;
            // Harris response
            double R = det - HARRIS_K * trace * trace;

            if (R > HARRIS_THRESHOLD) {
                // Corner detected: white pixel
                output[b] = 255;
            } else {
                // Normal point: black pixel
                output[b] = 0;
            }
        }
    }
}
