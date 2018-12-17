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
    displayWithText(&disp, squeezenet_labels[best]);
    printf("Press Any Key to Continue\n");
    getchar();
    endDisplay(&disp);
}

int main(int argc, char *argv[]) {
    // 1. Get and load user image
    int image_depth = 0;
    int image_width = 0;
    int image_height = 0;
    float *image = loadImageF32(DEFAULT_PATH_IMG,
                                &image_depth, &image_width, &image_height);
    if (!image) {
        return -1;
    }

    // 2. Load network parameters
    float *weights = NULL;
    float *biases = NULL;
    loadRawWeightsAndBiases(DEFAULT_PATH_WEIGHTS,
                            DEFAULT_PATH_BIASES,
                            &weights, &biases);

    // 3. Do inference
    struct timespec start, finish;
    double elapsed;
     
    clock_gettime(CLOCK_MONOTONIC, &start);
    double result[N_LABELS] = {0};
    if (squeezenetPredict(image, image_width, image_height, image_depth, weights, biases, result) < 0) {
        return -1;
    }
    int best_result = squeezenetDecode(N_LABELS, result);
	MD5_Update(N_LABELS * sizeof(double), result);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    fprintf(stderr, "Total time: %lf seconds\n",elapsed);

    // 4.  Display result
//    displayResult(image_width, image_height, best_result);

    // 5. Clean everything
    free(weights);
    free(biases);
    free(image);
    return 0;
}
