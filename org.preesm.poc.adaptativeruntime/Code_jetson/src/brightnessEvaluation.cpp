/*
 ============================================================================
 Name        : brightnessEvaluation.c
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C
 Description : Evaluate the average brightness of an array of char
 ============================================================================
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "brightnessEvaluation.h"

void computeBrightnessAndForward(int height, int width, int background, unsigned char *in, float *brightness, unsigned char *out) {
    /* == Forward input to output == */
    memcpy(out, in, height * width * sizeof(unsigned char));

    /* == Evaluate average value of each pixel with sub-sampling == */
    long sum = 0;
    const auto count = ((height / 16) * (width / 16));
    for (auto y = 0; y < height; y += 16) {
        for (auto x = 0; x < width; x += 16) {
            sum += in[y * width + x] - background;
        }
    }
    /* == Compute average == */
    const auto avg = sum / count;

    /* == Evaluate the variance of each pixel with sub-sampling == */
    long var = 0;
    for (auto i = 0; i < height; i += 16) {
        for (auto j = 0; j < width; j += 16) {
            const auto diff = (in[i * width + j] - background - avg);
            var += (diff * diff);
        }
    }
    /* == Compute variance == */
    var = sqrt(std::abs(var / count));
    (*brightness) = static_cast<float>(var) / (255.f - static_cast<float>(background));
}

void makeDecision(float *brightness, Param *decision) {
    ((*brightness) > 0.1f) ? (*decision) = 1 : (*decision) = 0;
}
