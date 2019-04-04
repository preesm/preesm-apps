//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_COMMON_H
#define SQUEEZENET_C_COMMON_H


#define DEFAULT_PATH_FONT    PROJECT_ROOT_PATH "/dat/DejaVuSans.ttf"
#define DEFAULT_PATH_WEIGHTS PROJECT_ROOT_PATH "/dat/weights.bin"
#define DEFAULT_PATH_BIASES  PROJECT_ROOT_PATH "/dat/biases.bin"
#define DEFAULT_PATH_IMG     PROJECT_ROOT_PATH "/dat/cat.jpg"

//#define VERBOSE

#ifdef VERBOSE
#define printINFOVerbose(message) fprintf(stdout, "INFO: %s", message)
#else
#define printINFOVerbose(message)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#endif //SQUEEZENET_C_COMMON_H
