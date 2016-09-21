/*
	============================================================================
	Name        : image_png.h
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description :
	============================================================================
*/

#ifndef IMAGE_PNG_H_
#define IMAGE_PNG_H_

#include "image.h"

int image_rgb_loadPng(const char* filename, struct str_image_rgb* str);
int image_gray_loadPng(const char* filename, struct str_image_gray* str);
int image_rgb_savePng(const char* filename, const struct str_image_rgb* str);
int image_gray_savePng(const char* filename, const struct str_image_gray* str);

#endif /* IMAGE_PNG_H_ */
