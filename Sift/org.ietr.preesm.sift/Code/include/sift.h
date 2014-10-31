#ifndef _SIFT_H_
#define _SIFT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#define TIMING

#ifdef TIMING
#include "timer.h"
//#define TIMING_BSS0
//#define TIMING_BSS1
//#define TIMING_BSS2
//#define TIMING_BSS3
//#define TIMING_BSS4
//#define TIMING_BSS5
//#define TIMING_BSS6
//#define TIMING_BSS7
#define TIMING_BOB
#define TIMING_splitOctaves
#define TIMING_EXTREME
#define TIMING_DOG
#define TIMING_INIT
#define TIMING_mergeSS
#define TIMING_ori
#define TIMING_render
#endif

/****************************************
 * Flags
 ***************************************/
// print information
#define VERBOSE 1


/****************************************
 * Global Definitions
 ***************************************/

// maximum number of octaves
#define MAX_O (10)
// maximum nuber of scales per octave
#define MAX_S (10)
// number of bins for orientation histogram
#define ORI_BINS (36)

#define IMG_WIDTH 352
#define IMG_HEIGHT 288
#define IMG_SIZE (IMG_WIDTH*IMG_HEIGHT)
#define MAX_SiftKeypoints 200

/****************************************
 * Data Structures
 ***************************************/

// 128-element descriptor
//#define NUM_OF_DESCRIPTORS (128)
typedef struct SiftKeypoint_t {
    int o; // octave number
    float x; // x coordinate
    float y; // y coordinate
    float s; // scale
    float ori; // orientation in degrees.
    float mag; // magnitude
    //float descriptors [NUM_OF_DESCRIPTORS];
} SiftKeypoint;

// Gradient buffer for orientation and descriptor calculation
extern int current_octave;
extern float* grad_buffer;

/****************************************
 * Functions
 ***************************************/

void init(int w, int h, int S, int* O, int* octavesW, int* octavesH,
	float* sigmas);


void buildOB(unsigned char* img,
             unsigned char* octaves,
             int *O, int S,
             int* octavesW, int* octavesH);

void splitOctaves(unsigned char *octave0, unsigned char *octave1,
		unsigned char *octave2, unsigned char *octave3,
		unsigned char *octave4, unsigned char *octave5,
		unsigned char *octave6, unsigned char *octave7,
		unsigned char *octaves_in, int *O, int *octavesW, int *octavesH);

void buildSS0(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS1(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS2(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS3(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS4(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS5(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS6(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);
void buildSS7(unsigned char* octaves,
             float* scaleSpace,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas);

void mergeSS(float* scale_space_in0, float* scale_space_in1,
	float* scale_space_in2, float* scale_space_in3,
	float* scale_space_in4, float* scale_space_in5,
	float* scale_space_in6, float* scale_space_in7,
	float* scale_space_out, int *O, int S, int *octavesW, int *octavesH);


void DoG(float *dog,
         float *scaleSpace,
         int *O, int S,
         int* octavesW, int* octavesH);

void extreme(int* keyN,
             float* dog,
             int *O, int S,
             int* octavesW, int* octavesH,
			 float* sigmas,
			 float* struct_x, float* struct_y,
			 int* struct_o, float* struct_s);

void orientation(int *keyN,
                 float *scaleSpace,
                 int* octavesW, int* octavesH,float *sigmas,
                 float* struct_x, float* struct_y,
                 int* struct_o, float* struct_s,
                 int * struct_int_x, int * struct_int_y, int * struct_int_o,
                 int * struct_int_s, float *struct_float_ori, int *O, int S);

void  render(int w, int h, unsigned char* y_input,
             unsigned int* x, unsigned int* y, int *o, int *s, float *ori, int *keyN,
			 unsigned char* y_output, float* sigmas, int n_max);

#endif//_SIFT_H_

