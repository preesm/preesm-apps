//
// Created by hmiomand on 25/02/2020.
//
#include "preesm.h"

#ifndef WAVELET_SSIM_H
#define WAVELET_SSIM_H

void compute_SSIM(int WIDTH, int HEIGHT, IN unsigned char* reference, IN unsigned char* modified);

double mean(int nb_value, unsigned char* values);

double variance(int nb_value, unsigned char* values);

double covariance(int nb_value, unsigned char* values_1, unsigned char* values_2);

void compute_SSIM_float(int WIDTH, int HEIGHT, float* reference, float* modified);

double mean_f(int nb_value, float* values);

double variance_f(int nb_value, float* values);

double covariance_f(int nb_value, float* values_1, float* values_2);

#endif //WAVELET_SSIM_H
