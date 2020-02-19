/*
	============================================================================
	Name        : sobel.c
	Author      : kdesnos
	Version     : 1.2
	Copyright   : CECILL-C
	Description : Adapted from sobel-morpho project for brussels demo
	============================================================================
*/
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "sobel.h"

template<class T>
static T clamp(T x) {
    constexpr T TYPE_255 = static_cast<T>(255);
    return x > TYPE_255 ? TYPE_255 : x;
}

void sobel(int width, int height, int background, unsigned char *input, unsigned char *output) {
    /* == Apply the filter == */
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            const auto gx = -input[(j - 1) * width + i - 1] - 2 * input[j * width + i - 1] - input[(j + 1) * width + i - 1] + 
                             input[(j - 1) * width + i + 1] + 2 * input[j * width + i + 1] + input[(j + 1) * width + i + 1];
            const auto gy = -input[(j - 1) * width + i - 1] - 2 * input[(j - 1) * width + i] - input[(j - 1) * width + i + 1] + 
                             input[(j + 1) * width + i - 1] + 2 * input[(j + 1) * width + i] + input[(j + 1) * width + i + 1];
            const auto result = static_cast<int>(sqrt(gx * gx + gy * gy)) + background;
            output[(j - 1) * width + i] = static_cast<unsigned char>(clamp(result));
        }
        /* == Fill the left and right sides == */
        output[(j * width)] = 0;
        output[(j * width) + (width - 1)] = 0;
    }
    
    /* == Fill top and bottom borders == */
    memset(output, 0, static_cast<size_t>(width * height));
    memset(output + (height - 1) * width, 0, static_cast<size_t>(width * height));
}
