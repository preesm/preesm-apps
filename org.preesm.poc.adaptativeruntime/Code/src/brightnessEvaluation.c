/*
 ============================================================================
 Name        : brightnessEvaluation.c
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C
 Description : Evaluate the average brightness of an array of char
 ============================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "brightnessEvaluation.h"

void evalBrightness(int height, int width, int background, unsigned char * in,
		float * brightness, unsigned char * out) {
	int i, j;
	int nb = 0;
	long sum = 0;
	long avg;
	long var = 0;

	// Eval average of char
	for (i = 0; i < height; i += 16) {
		for (j = 0; j < width; j += 16) {
			nb++;
			sum += in[i * width + j] - background;
		}
	}
	avg = sum / nb;

	// Eval variance
	for (i = 0; i < height; i += 16) {
		for (j = 0; j < width; j += 16) {
			long diff = (in[i * width + j] - background - avg);
			var += diff * diff;
		}
	}

	var /= nb;
	var = sqrt(abs(var));
	*brightness = var / (255.0 - background);

	memcpy(out, in, height * width * sizeof(unsigned char));

	Param decision;
	makeDecision(brightness, &decision);
	if (decision) {
		for (i = height - height /10; i < height ; i++) {
			for(j=0;j<width /10; j+=4){
				*(int*)(out+i*width+j) = 0x0000FF00;
			}
		}
	}
}

void makeDecision(float* brightness, Param * decision) {
	(*brightness > 0.1) ? *decision = 1 : *decision = 0;
}

void generateNothing(int height, int width, int value, OUT unsigned char * out) {
	memset(out, value, height * width * sizeof(unsigned char));
}
