//
// Created by farresti on 21/08/18.
//


#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "display.h"
#include "common.h"
#include "squeezenet.h"
#include "labels.h"
#include "utility.h"
#include "md5.h"


static void displayResult(int image_width, int image_height, int best) {
    // 4.1 Initialize SDL
    display_t disp;
    initDisplay(image_width, image_height, &disp);

    // 4.2 Display
    disp.image = IMG_Load(DEFAULT_PATH_IMG);
    displayWithText(&disp, squeezenetLabels[best]);
    printf("Press Any Key to Continue\n");
    getchar();
    endDisplay(&disp);
}

static void cleanBeforeExit(const image_t *image, const param_t *parameters) {
    if (parameters->weights) {
        free((void *) parameters->weights);
    }
    if (parameters->biases) {
        free((void *) parameters->biases);
    }
    if (image->rawPixels) {
        free((void *) image->rawPixels);
    }
}

int main(int argc, char *argv[]) {
    // 1. Get and load user image
    image_t image;
    if (argc < 2) {
        fprintf(stderr, "Invalid number of arguments, expected 1.\n");
        return -1;
    }
    image.rawPixels = loadImageF32(argv[1],
                                   &image.depth, &image.width, &image.height);
    if (!image.rawPixels) {
        return -1;
    }

    // 2. Load network parameters
    param_t parameters;
    if (loadRawWeightsAndBiases(DEFAULT_PATH_WEIGHTS, DEFAULT_PATH_BIASES,
                                &parameters.weights, &parameters.biases) < 0) {
        cleanBeforeExit(&image, &parameters);
        return -1;
    }

    // 3. Performs the prediction
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    double result[IMAGENET_NB_CLASS] = {0};
    if (squeezenetPredict(&image, &parameters, result) < 0) {
        cleanBeforeExit(&image, &parameters);
        return -1;
    }

    // 4. Decode the output of the network to get the corresponding class
    int bestResult = squeezenetDecode(IMAGENET_NB_CLASS, result);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    // 5. Compute the MD5
    MD5_Update(IMAGENET_NB_CLASS * sizeof(double), result);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    fprintf(stderr, "Total time: %lf seconds\n", elapsed);

    // 6.  Display result
//    displayResult(image.width, image.height, bestResult);

    // 7. Clean everything
    cleanBeforeExit(&image, &parameters);
    return 0;
}
