/*
	============================================================================
	Name        : image_load.c
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description : Functions to load and save sevral file format.
	============================================================================
*/

#include "image_load.h"

#include "image_png.h"
#include "image_ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * PNG file format.
 */
#define FTYPE_PNG 1
/**
 * PBM file format.
 */
#define FTYPE_PBM 2
/**
 * PGM file format.
 */
#define FTYPE_PGM 3
/**
 * PPM file format.
 */
#define FTYPE_PPM 4

/**
 * The header of PNG file format.
 */
static const uint8_t png_header[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

/**
 * Compare a header to a reference.
 * @param fileheader The header that has been read.
 * @param nbread Size of header.
 * @param ref Reference header.
 * @param size size of reference header.
 * @return 1 if equal, 0 otherwise.
 */
static int compareHeader(const uint8_t* fileheader, int nbread, const uint8_t* ref, int size)
{
	if(nbread >= size)
	{
		if(memcmp(fileheader, ref, size) == 0)
		{
			return 1;
		}
	}

	return 0;
}

/**
 * Return the file format of a file by reading its header.
 * @param filename name of the file to test
 * @return file format or 0 (if no match found), or error code (<0).
 */
static int fromHeader(const char* filename)
{
	const int maxheader = 8;
	uint8_t header[maxheader];
	int nbread;
	FILE* file = NULL;

	file = fopen(filename, "rb");
	if(file == NULL)
	{
		printf("Unable to open file '%s'\n", filename);
		return -1;
	}

	nbread = fread(header, sizeof(uint8_t), maxheader, file);

	fclose(file);

	/*test PNG*/
	if(compareHeader(header, nbread, png_header, sizeof(png_header)))
	{
		return FTYPE_PNG;
	}

	/*test PXM*/
	if((nbread >= 2) && (header[0] == 'P') && (header[1] >= '1') && (header[1] <= '6'))
	{
		int type = header[1]-'0';
		if(type > 3)
		{
			type -= 3;
		}
		return FTYPE_PBM + type - 1;
	}

	return 0;
}

/**
 * Return the file format based on its extension.
 * @param filename name of the file to test
 * @return file format or 0 (if no match found)
 */
static int fromExtension(const char* filename)
{
	static const char* exts[] =
	{
		"png", "pbm", "pgm", "ppm"
	};

	int i;

	int size = strlen(filename);
	int csize = 0;

	for(i=0; i<(sizeof(exts)/sizeof(exts[0])); i++ )
	{
		csize = strlen(exts[i]);
		if(
			(size > csize) &&
			(filename[size-csize -1] == '.') &&
			(strcmp(exts[i], &filename[size-csize]) == 0)
		)
		{
			return i+1;
		}
	}

	return 0;
}

int image_gray_load(const char* filename, struct str_image_gray* str)
{
	int type = fromHeader(filename);
	switch(type)
	{
	case FTYPE_PNG :
		return image_gray_loadPng(filename, str);
		break;
	case FTYPE_PBM :
	case FTYPE_PGM :
	case FTYPE_PPM :
		return image_gray_loadPxm(filename, str);
		break;
	default :
		printf("Unknown file format for '%s'\n", filename);
		return -1;
		break;
	}
}

int image_rgb_load(const char* filename, struct str_image_rgb* str)
{
	int type = fromHeader(filename);
	switch(type)
	{
	case FTYPE_PNG :
		return image_rgb_loadPng(filename, str);
		break;
	case FTYPE_PBM :
	case FTYPE_PGM :
	case FTYPE_PPM :
		return image_rgb_loadPxm(filename, str);
		break;
	default :
		printf("Unknown file format for '%s'\n", filename);
		return -1;
		break;
	}
}

int image_gray_save(const char* filename, const struct str_image_gray* str)
{
	int type = fromExtension(filename);
	switch(type)
	{
	case FTYPE_PNG :
		return image_gray_savePng(filename, str);
		break;
	case FTYPE_PBM :
	case FTYPE_PGM :
	case FTYPE_PPM :
		return image_gray_savePxm(filename, str, type - FTYPE_PBM + 4);
		break;
	default :
		printf("Unknown file format for '%s'\n", filename);
		return -1;
		break;
	}
}

int image_rgb_save(const char* filename, const struct str_image_rgb* str)
{
	int type = fromExtension(filename);
	switch(type)
	{
	case FTYPE_PNG :
		return image_rgb_savePng(filename, str);
		break;
	case FTYPE_PBM :
	case FTYPE_PGM :
	case FTYPE_PPM :
		return image_rgb_savePxm(filename, str, type - FTYPE_PBM + 4);
		break;
	default :
		printf("Unknown file format for '%s'\n", filename);
		return -1;
		break;
	}
}

