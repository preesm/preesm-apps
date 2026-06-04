#ifndef TOP
#define TOP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preesm.h"

void Source_Highpass_filter(int FILTER_SIZE, OUT float* filter);
void Source_Lowpass_filter(int FILTER_SIZE, OUT float* filter);

void reverse_filter(int FILTER_SIZE, IN float* input, OUT float* output);

void reshape_image(int WIDTH, int HEIGHT, IN unsigned char* in_High_High, IN unsigned char* in_High_Low, IN unsigned char* in_Low_High, IN unsigned char* in_Low_Low, OUT unsigned char* y);

void reshape_image_float(int WIDTH, int HEIGHT, IN float* in_High_High, IN float* in_High_Low, IN float* in_Low_High, IN float* in_Low_Low, OUT float* y);

void reshape_uv(int WIDTH, int HEIGHT, IN unsigned char* input, OUT unsigned char* output);

void writePGM_ASCII(IN int WIDTH, IN int HEIGHT, IN unsigned char* data);

void uchar_to_float(int WIDTH, int HEIGHT, IN unsigned char* input, OUT float* output);

void float_to_uchar(int WIDTH, int HEIGHT, IN float* input, OUT unsigned char* output);

void passthrough(int WIDTH, int HEIGHT, IN unsigned char* input, OUT unsigned char* output);

#endif
