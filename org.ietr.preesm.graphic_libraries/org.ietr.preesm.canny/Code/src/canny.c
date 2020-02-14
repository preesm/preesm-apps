/*
 ============================================================================
 Name        : canny.c
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CECILL-C
 Description :
 ============================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canny.h"

void canny(int width, int height, char *gx, char *gy, unsigned char *output) {
    int i, j, k;
    int current, neighbor1, neighbor2;
    int current_x, current_y;
    char neighbor1_x, neighbor1_y;
    char neighbor2_x, neighbor2_y;

    // Zero in the first two lines
    memset(output, 0, 2 * width);

    k = 2 * width;
    // Apply the filter
    for (j = 2; j < height - 2; j++) {
        output[k++] = 0;
        output[k++] = 0;
        for (i = 2; i < width - 2; i++) {
            current_x = gx[k];
            current_y = gy[k];

            // Norm of the current pixel
            current = current_x * current_x + current_y * current_y;
            /**
             * Direction of the derivative at the current pixel.
             * Neighbors are taken in the orthogonal directions.
             */
            if (abs(current_y) < T1 * abs(current_x)) {
                // arg == 0
                neighbor1_x = gx[k - width];
                neighbor1_y = gy[k - width];
                neighbor2_x = gx[k + width];
                neighbor2_y = gy[k + width];
            } else if (abs(current_y) >= T2 * abs(current_x)) {
                // arg == PI / 2 || arg == - PI / 2
                neighbor1_x = gx[k - 1];
                neighbor1_y = gy[k - 1];
                neighbor2_x = gx[k + 1];
                neighbor2_y = gy[k + 1];
            } else if (current_x * current_y > 0) {
                // arg == PI / 4 || arg == -3 * PI / 4
                neighbor1_x = gx[k - width - 1];
                neighbor1_y = gy[k - width - 1];
                neighbor2_x = gx[k + width + 1];
                neighbor2_y = gy[k + width + 1];
            } else {
                // arg == 3 * PI / 4 || arg == -PI / 4
                neighbor1_x = gx[k - width + 1];
                neighbor1_y = gy[k - width + 1];
                neighbor2_x = gx[k + width - 1];
                neighbor2_y = gy[k + width - 1];
            }

            // Norm of the neighbor pixels
            neighbor1 = neighbor1_x * neighbor1_x + neighbor1_y * neighbor1_y;
            neighbor2 = neighbor2_x * neighbor2_x + neighbor2_y * neighbor2_y;

            /**
             * Filtering & Thresholding: A pixel is considered to be an edge if
             * its value is bigger than the two neighbor pixels.
             * A double thresholding is then applied to refine the result.
             */
            if (current > neighbor1 && current > neighbor2
                && current > LOW_THRESHOLD && current < HIGH_THRESHOLD) {
                // Edge point: white pixel
                output[k] = 255;
            } else {
                // Normal point: black pixel
                output[k] = 0;
            }

            k++;
        }
        output[k++] = 0;
        output[k++] = 0;
    }

    // Zero in the last two lines
    memset(output + k, 0, 2 * width);
}
