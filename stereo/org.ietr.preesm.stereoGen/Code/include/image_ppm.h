/*
	============================================================================
	Name        : image_ppm.h
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description :
	============================================================================
*/
#ifndef IMAGE_PPM_H_
#define IMAGE_PPM_H_

#include "image.h"

/**
 * The PXM mode 1, pbm file, black and white, ASCII
 */
#define PXM_MODE_PBM_A 1
/**
 * The PXM mode 4, pbm file, black and white, binary
 */
#define PXM_MODE_PBM_B 4
/**
 * The PXM mode 2, pgm file, gray scale, ASCII
 */
#define PXM_MODE_PGM_A 2
/**
 * The PXM mode 5, pgm file, gray scale, binary
 */
#define PXM_MODE_PGM_B 5
/**
 * The PXM mode 3, ppm file, rgb, ASCII
 */
#define PXM_MODE_PPM_A 3.
/**
 * The PXM mode 6, ppm file, rgb, binary
 */
#define PXM_MODE_PPM_B 6

/**
 * Load a pxm (pbm, pgm, ppm) file into a rgb image.
 * @param filename Name of file to load.
 * @param str output image, must not be initialized.
 * @return 0 if success, error code otherwise.
 */
int image_rgb_loadPxm(const char* filename, struct str_image_rgb* str);

/**
 * save a rgb image into a pxm (pbm, pgm, ppm) file.
 * @param filename Name of file to create.
 * @param str image to save.
 * @param mode a number from 1 to 6 to select pxm mode :
 *   - PXM_MODE_PBM_A
 *   - PXM_MODE_PBM_B
 *   - PXM_MODE_PGM_A
 *   - PXM_MODE_PGM_B
 *   - PXM_MODE_PPM_A
 *   - PXM_MODE_PPM_B
 * @return 0 if success, error code otherwise.
 */
int image_rgb_savePxm(const char* filename, const struct str_image_rgb* str, int mode);

/**
 * Load a pxm (pbm, pgm, ppm) file into a rgb image.
 * @param filename Name of file to load.
 * @param str output image, must not be initialized.
 * @return 0 if success, error code otherwise.
 */
int image_gray_loadPxm(const char* filename, struct str_image_gray* str);

/**
 * save a gray scale image into a pxm (pbm, pgm, ppm) file.
 * @param filename Name of file to create.
 * @param str image to save.
 * @param mode a number from 1 to 6 to select pxm mode :
 *   - PXM_MODE_PBM_A
 *   - PXM_MODE_PBM_B
 *   - PXM_MODE_PGM_A
 *   - PXM_MODE_PGM_B
 *   - PXM_MODE_PPM_A
 *   - PXM_MODE_PPM_B
 * @return 0 if success, error code otherwise.
 */
int image_gray_savePxm(const char* filename, const struct str_image_gray* str, int mode);

#endif /* IMAGE_PPM_H_ */
