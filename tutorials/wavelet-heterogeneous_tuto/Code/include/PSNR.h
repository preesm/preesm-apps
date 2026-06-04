//
// Created by hmiomand on 25/02/2020.
//
#include <math.h>

#include "preesm.h"

#ifndef WAVELET_PSNR_H
#define WAVELET_PSNR_H

void compute_PSNR(int WIDTH, int HEIGHT, IN unsigned char* reference, IN unsigned char* modified);

void compute_PSNR_float(int WIDTH, int HEIGHT,float* reference, float* modified);

#endif //WAVELET_PSNR_H
