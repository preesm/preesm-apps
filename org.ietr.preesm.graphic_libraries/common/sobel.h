/*
 ============================================================================
 Name        : sobel.h
 Author      : zhzhang
 Version     : 1.1
 Copyright   : CeCILL-C
 Description : 2D Sobel filtering function
 ============================================================================
 */

#ifndef SOBEL_H
#define SOBEL_H

#include "preesm.h"

/**
 * @brief Compute the x / y gradient of an image using the sobel filter.
 *        see: https://fr.wikipedia.org/wiki/Filtre_de_Sobel
 * @param width   Width the input image.
 * @param height  Height the input image.
 * @param input   Pointer to the input pixel buffer.
 * @param gx      Pointer to the output x gradient computed with the sobel filter.
 * @param gy      Pointer to the output y gradient computed with the sobel filter.
 */
void sobel_raw(int width, int height, IN unsigned char *input, OUT char *gx, OUT char *gy);

/**
 * @brief Apply the sobel filter on an image.
 *        see: https://fr.wikipedia.org/wiki/Filtre_de_Sobel
 * @param width   Width the input image.
 * @param height  Height the input image.
 * @param input   Pointer to the input pixel buffer.
 * @param output  Pointer to the output image.
 */
void sobel(int width, int height, IN unsigned char *input, OUT unsigned char *output);

#endif
