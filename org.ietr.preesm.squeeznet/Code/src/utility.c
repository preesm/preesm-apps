#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "utility.h"

float *loadImageF32(const char *path, int *depth, int *width, int *height) {
    float *image = NULL;
    if (!path || !depth || !width || !height) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        fprintf(stderr, "       path: %p.\n", path);
        fprintf(stderr, "       depth: %p.\n", depth);
        fprintf(stderr, "       width: %p.\n", width);
        fprintf(stderr, "       height: %p.\n", height);
        return NULL;
    }

    // 1. Using SDL to load the image
    printINFOVerbose("IMG_Load --> START.\n");
    SDL_Surface *image_surface = IMG_Load(path);
    if (!image_surface) {
        fprintf(stderr, "ERROR: Failed to create image:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        return NULL;
    }
    printINFOVerbose("IMG_Load --> SUCCESS.\n");

    *width = image_surface->w;
    *height = image_surface->h;
    *depth = 3;

    // 2. Convert the image to F32
    SDL_Surface *image_surface_rgba = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(image_surface);
    if (!image_surface_rgba) {
        fprintf(stderr, "ERROR: Failed to convert image:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        return NULL;
    }
    image = malloc((*width) * (*height) * 3 * sizeof(float));
    if (!image) {
        SDL_FreeSurface(image_surface_rgba);
        fprintf(stderr, "ERROR: Failed to allocate memory for the image.\n");
        return NULL;
    }
    int offset_channel2 = (*width) * (*height);
    int offset_channel3 = (*width) * (*height) * 2;
    for (int i = 0; i < (*width); ++i) {
        for (int j = 0; j < (*height); ++j) {
            int pixel_coord = i + j * (*width);
            Uint32 pixel = ((Uint32 *) image_surface_rgba->pixels)[pixel_coord];
            Uint8 pixel_red = (Uint8) ((pixel & image_surface_rgba->format->Rmask)
                    >> image_surface_rgba->format->Rshift);
            Uint8 pixel_blue = (Uint8) ((pixel & image_surface_rgba->format->Bmask)
                    >> image_surface_rgba->format->Bshift);
            Uint8 pixel_green = (Uint8) ((pixel & image_surface_rgba->format->Gmask)
                    >> image_surface_rgba->format->Gshift);

            image[pixel_coord] = pixel_red;
            image[pixel_coord + offset_channel2] = pixel_green;
            image[pixel_coord + offset_channel3] = pixel_blue;
        }
    }
    printINFOVerbose("Convert image to F32 --> SUCCESS.\n");

    // Freeing the surface
    SDL_FreeSurface(image_surface_rgba);
    return image;
}

int readImageRawF32(IN int width, IN int height, OUT float *out) {
    // 1. Using SDL to load the image
    printINFOVerbose("IMG_Load --> START.\n");
    SDL_Surface *imageSurface = IMG_Load(DEFAULT_PATH_IMG);
    if (!imageSurface) {
        fprintf(stderr, "ERROR: Failed to create image:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        return -1;
    }
    printINFOVerbose("IMG_Load --> SUCCESS.\n");

    int realWidth = imageSurface->w;
    int realHeight = imageSurface->h;

    if (realWidth != width || realHeight != height) {
        fprintf(stderr, "ERROR: Expected image of size [%d]x[%d], got [%d]x[%d]\n", width, height, realWidth,
                realHeight);
        SDL_FreeSurface(imageSurface);
        return -1;
    }

    // 2. Convert the image to F32
    SDL_Surface *imageSurfaceRGBA = SDL_ConvertSurfaceFormat(imageSurface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(imageSurface);
    if (!imageSurfaceRGBA) {
        fprintf(stderr, "ERROR: Failed to convert image:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        return -1;
    }
    int offsetChannel2 = (width) * (height);
    int offsetChannel3 = (width) * (height) * 2;
    for (int i = 0; i < (width); ++i) {
        for (int j = 0; j < (height); ++j) {
            int pixelCoord = i + j * (width);
            Uint32 pixel = ((Uint32 *) imageSurfaceRGBA->pixels)[pixelCoord];
            Uint8 pixelRed = (Uint8) ((pixel & imageSurfaceRGBA->format->Rmask) >> imageSurfaceRGBA->format->Rshift);
            Uint8 pixelBlue = (Uint8) ((pixel & imageSurfaceRGBA->format->Bmask) >> imageSurfaceRGBA->format->Bshift);
            Uint8 pixelGreen = (Uint8) ((pixel & imageSurfaceRGBA->format->Gmask) >> imageSurfaceRGBA->format->Gshift);

            out[pixelCoord] = pixelRed;
            out[pixelCoord + offsetChannel2] = pixelGreen;
            out[pixelCoord + offsetChannel3] = pixelBlue;
        }
    }
    printINFOVerbose("Convert image to F32 --> SUCCESS.\n");

    // Freeing the surface
    SDL_FreeSurface(imageSurfaceRGBA);
    return 0;
}

int loadRawWeightsAndBiases(const char *pathWeights, const char *pathBiases, const float **weights, const float **biases) {
    if (!pathWeights || !pathBiases || !weights || !biases) {
        fprintf(stderr, "ERROR: Null pointer passed as input.\n");
        return -1;
    }
    // 0. Try to open files
    FILE *fileWeights = fopen(pathWeights, "rb");
    if (!fileWeights) {
        fprintf(stderr, "ERROR: Failed to open weights file with path:\n");
        fprintf(stderr, "       %s\n", pathWeights);
        return -1;
    }
    printINFOVerbose("fopen fileWeights --> SUCCESS\n");
    FILE *fileBiases = fopen(pathBiases, "rb");
    if (!fileBiases) {
        fclose(fileWeights);
        fprintf(stderr, "ERROR: Failed to open biases file with path:\n");
        fprintf(stderr, "       %s\n", pathBiases);
        return -1;
    }
    printINFOVerbose("fopen fileBiases --> SUCCESS\n");
    // 1. Load raw weights
    /* Structure is as follows */
    /* weights_layer_input_0_layer_output_0 | weights_layer_input_1_layer_output_0 | .. | weights_layer_input_M_layer_output_N */
    fseek(fileWeights, 0, SEEK_END);
    size_t sizeWeightsFile = (size_t) ftell(fileWeights);
    fseek(fileWeights, 0, SEEK_SET);
    (*weights) = malloc(sizeWeightsFile);
    if (!(*weights)) {
        fprintf(stderr, "ERROR: Failed to allocate memory for weights.\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    if (fread((void *) (*weights), sizeof(float), sizeWeightsFile / 4, fileWeights) != (sizeWeightsFile / 4)) {
        printINFOVerbose("reading weights --> FAILURE\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    printINFOVerbose("reading weights --> SUCCESS\n");
    char strSize[40];
    sprintf(strSize, "sizeWeightsFile: %ld\n", sizeWeightsFile / 4);
    printINFOVerbose(strSize);

    // 2. Load raw biases
    fseek(fileBiases, 0, SEEK_END);
    size_t sizeBiasesFile = (size_t) ftell(fileBiases);
    fseek(fileBiases, 0, SEEK_SET);
    (*biases) = malloc(sizeBiasesFile);
    if (!(*biases)) {
        fprintf(stderr, "ERROR: Failed to allocate memory for biases.\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    if (fread((void *) (*biases), sizeof(float), sizeBiasesFile / 4, fileBiases) != sizeBiasesFile / 4) {
        printINFOVerbose("reading biases --> FAILURE\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    printINFOVerbose("reading biases --> SUCCESS\n");
    sprintf(strSize, "sizeBiasesFile: %ld\n", sizeBiasesFile / 4);
    printINFOVerbose(strSize);

    // 3. Close files
    fclose(fileWeights);
    fclose(fileBiases);
    return 0;
}

int genRawWeightsAndBiases(IN long sizeWeights, IN long sizeBiases,
                           OUT float *weights, OUT float *biases) {
    // 0. Try to open files
    FILE *fileWeights = fopen(DEFAULT_PATH_WEIGHTS, "rb");
    if (!fileWeights) {
        fprintf(stderr, "ERROR: Failed to open weights file with path:\n");
        fprintf(stderr, "       %s\n", DEFAULT_PATH_WEIGHTS);
        return -1;
    }
    printINFOVerbose("fopen fileWeights --> SUCCESS\n");
    FILE *fileBiases = fopen(DEFAULT_PATH_BIASES, "rb");
    if (!fileBiases) {
        fclose(fileWeights);
        fprintf(stderr, "ERROR: Failed to open biases file with path:\n");
        fprintf(stderr, "       %s\n", DEFAULT_PATH_BIASES);
        return -1;
    }
    printINFOVerbose("fopen biases_file --> SUCCESS\n");
    // 1. Load raw weights
    /* Structure is as follows */
    /* weights_layer_input_0_layer_output_0 | weights_layer_input_1_layer_output_0 | .. | weights_layer_input_M_layer_output_N */
    fseek(fileWeights, 0, SEEK_END);
    size_t realSizeWeights = (size_t) ftell(fileWeights) / 4;
    fseek(fileWeights, 0, SEEK_SET);
//    if (realSizeWeights != sizeWeights) {
//        fprintf(stderr, "ERROR: Expected size of [%ld] for weights file, got [%ld].\n", sizeWeights, realSizeWeights);
//        fclose(fileWeights);
//        fclose(fileBiases);
//        return -1;
//    }
    if (fread(weights, sizeof(float), (size_t) sizeWeights, fileWeights) != (sizeWeights)) {
        printINFOVerbose("reading weights --> FAILURE\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    printINFOVerbose("reading weights --> SUCCESS\n");

    // 2. Load raw biases
    fseek(fileBiases, 0, SEEK_END);
    size_t realSizeBiases = (size_t) ftell(fileBiases) / 4;
    fseek(fileBiases, 0, SEEK_SET);
//    if (realSizeBiases != sizeBiases) {
//        fprintf(stderr, "ERROR: Expected size of [%ld] for biases file, got [%ld].\n", sizeBiases, realSizeBiases);
//        fclose(fileWeights);
//        fclose(fileBiases);
//        return -1;
//    }
    if (fread(biases, sizeof(float), (size_t) sizeBiases, fileBiases) != sizeBiases) {
        printINFOVerbose("reading biases --> FAILURE\n");
        fclose(fileWeights);
        fclose(fileBiases);
        return -1;
    }
    printINFOVerbose("reading biases --> SUCCESS\n");

    // 3. Close files
    fclose(fileWeights);
    fclose(fileBiases);
    return 0;
}



