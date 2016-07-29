/*
	============================================================================
	Name        : image_load.h
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description : Functions to load and save sevral file format.
	============================================================================
*/

#ifndef IMAGE_LOAD_H_
#define IMAGE_LOAD_H_


#include "image.h"

/**
 * @brief Load a gray scale image from a file.
 *
 * It determines the image format by reading the header (do not care about
 * extension), and then call the correct loading function.
 * @param filename file to open.
 * @param str output image, must not be initialized.
 * @return 0 if success, error code otherwise.
 */
int image_gray_load(const char* filename, struct str_image_gray* str);
/**
 * @brief Load a RGB image from a file.
 *
 * It determines the image format by reading the header (do not care about
 * extension), and then call the correct loading function.
 * @param filename file to open.
 * @param str output image, must not be initialized.
 * @return 0 if success, error code otherwise.
 */
int image_rgb_load(const char* filename, struct str_image_rgb* str);
/**
 * @brief Save a gray scale image into a file.
 *
 * It determines the image format by the filename extension.
 * @param filename file to open.
 * @param str image to save.
 * @return 0 if success, error code otherwise.
 */
int image_gray_save(const char* filename, const struct str_image_gray* str);
/**
 * @brief Save a RGB scale image into a file.
 *
 * It determines the image format by the filename extension.
 * @param filename file to open.
 * @param str image to save.
 * @return 0 if success, error code otherwise.
 */
int image_rgb_save(const char* filename, const struct str_image_rgb* str);


#endif /* IMAGE_LOAD_H_ */
