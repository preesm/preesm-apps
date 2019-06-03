/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Description:
	This image class is a helper class designed for image related operations. 
	There is definitely room to optimize these functions. 

	Revision history:
		September, 15, 2013: initial version.
		July 8th, 2014: fixed arrary access bug in sample_2x(). Thanks Kyungmo Koo.
*/
#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

#include <typeinfo>

#include "img_io.h"

template <typename T> 
struct ImageObj
{
	int w;
	int h;
	T * data;
};


// Member function definition
template <typename T>
struct ImageObj<T> * CreateImage()
{
  struct ImageObj<T> * img = (struct ImageObj<T> *) malloc(sizeof(struct ImageObj<T>));
	img->w = 0;
	img->h = 0;
	img->data = NULL;
	return img;
}

template <typename T>
struct ImageObj<T> * CreateImage(int _w, int _h)
{
  struct ImageObj<T> * img = (struct ImageObj<T> *) malloc(sizeof(struct ImageObj<T>));
	img->w = _w;
	img->h = _h;
	img->data = (T *) malloc(sizeof(T)*_w*_h);
	return img;
}

// Copy construction function
template <typename T> 
struct ImageObj<T> * CreateImage(struct ImageObj<T> * img)
{
    struct ImageObj<T> * copy = (struct ImageObj<T> *) malloc(sizeof(struct ImageObj<T>));
	copy->w = img->w;
	copy->h = img->h;
	copy->data = (T *) malloc(sizeof(T)*img->w*img->h);
	memcpy(copy->data, img->data, img->w * img->h * sizeof(T));
	return copy;
}

template <typename T> 
void initCopy(struct ImageObj<T> * img_dst, struct ImageObj<T> * img_src)
{
	img_dst->w = img_src->w;
	img_dst->h = img_src->h;
	img_dst->data = (T *) malloc(sizeof(T)*img_src->w*img_src->h);
	memcpy(img_dst->data, img_src->data, img_src->w * img_src->h * sizeof(T));
}

template <typename T> 
void init(struct ImageObj<T> * img, int _w, int _h)
{
	img->w = _w;
	img->h = _h;
	img->data = (T *) malloc(sizeof(T)*_w*_h);
}

template <typename T> 
void reinit(struct ImageObj<T> * img, int _w, int _h)
{
	img->w = _w;
	img->h = _h;
	if (img->data != NULL) {
	  free(img->data);
	}
	img->data = (T *) malloc(sizeof(T)*_w*_h);
}

template <typename T> 
void release(struct ImageObj<T> * img)
{
	img->w = 0;
	img->h = 0;
	if (img->data != NULL) {
	  free(img->data);
	}
	free(img);
}


template <typename T> 
int read_pgm(struct ImageObj<T> * img,  const char * filename)
{
	FILE* in_file;
	char ch, type;
	int w, h;
	int dummy;
	unsigned char * _data;

	in_file = fopen(filename, "rb");
	if (! in_file)
	{
		fprintf(stderr, "ERROR(0): Fail to open file %s\n", filename);
		return -1;
	}
	/* Determine pgm image type (only type three can be used)*/
	ch = getc(in_file);
	if(ch != 'P')
	{
		printf("ERROR(1): Not valid pgm/ppm file type\n");
		return -1;
	}
	ch = getc(in_file);
	/* Convert the one digit integer currently represented as a character to
	* an integer(48 == '0') */
	type = ch - 48;
	if(type != 5)
	{
		printf("ERROR(2): this file type (P%d) is not supported!\n", type);
		return -1;
	}
	while(getc(in_file) != '\n');      /* Skip to end of line*/
	while (getc(in_file) == '#'){       /* Skip comment lines */
		while (getc(in_file) != '\n');
	}
	fseek(in_file, -1, SEEK_CUR);     /* Backup one character*/

	fscanf(in_file,"%d", &w);
	fscanf(in_file,"%d", &h);
	fscanf(in_file,"%d", &dummy);  /* Skipped here */
	while(getc(in_file) != '\n');

	init(img, w, h);
	if (typeid(T) == typeid(unsigned char))
	{
		fread(img->data, sizeof(unsigned char), (w)*(h), in_file);
	}else{
	  _data = (unsigned char *) malloc(sizeof(unsigned char) * w * h);
		fread(_data, sizeof(unsigned char), (w)*(h), in_file);
		
		for (int i = 0; i < h; i ++)
		{
			for (int j = 0; j < w; j ++)
			{
				img->data[i * w + j] = (T)(_data[i * w + j]);
			}
		}
		free(_data);
	}
	fclose(in_file);
	return 0;
}


template <typename T> 
int write_pgm(struct ImageObj<T> * img,  const char * filename)
{
	FILE* out_file;

	if (img->w <= 0 || img->h <= 0)
	{
		fprintf(stderr, "write_pgm(%s):Invalid image width or height\n", filename);
		return -1;
	}

	out_file = fopen(filename, "wb");
	if (! out_file){
		fprintf(stderr, "Fail to open file: %s\n", filename);
		return -1;
	}

	fprintf(out_file, "P5\n");
	fprintf(out_file, "%d %d\n255\n", img->w, img->h);

	ImageObj<unsigned char> * tmpImage = to_uchar(img);
	fwrite(tmpImage->data, sizeof(unsigned char), img->w * img->h, out_file);

	fclose(out_file);
	release(tmpImage);
	return 0;
}


template <typename T> 
struct ImageObj<unsigned char> * to_uchar(struct ImageObj<T> * img)
{
	struct ImageObj<unsigned char> * dstImage = CreateImage<unsigned char>(img->w, img->h);

	for (int r = 0; r < img->h; r ++)
	{
		for(int c = 0; c < img->w; c ++)
		{
			// Negative number, truncate to zero.
			float temp = img->data[r * img->w  + c];
			dstImage->data[r * img->w + c] = temp >= 0 ? (unsigned char)temp : 0;
		}
	}
	return dstImage;
}

template <typename T> 
struct ImageObj<float> * to_float(struct ImageObj<T> * img)
{
	struct ImageObj<float> * dstImage = CreateImage<float>(img->w, img->h);

	for (int i = 0; i < img->h; i ++)
	{
		for (int j = 0; j < img->w; j ++)
		{
			dstImage->data[i * img->w + j] = img->data[i * img->w + j];
		}
	}
	return dstImage;
}

// Upsample the image by 2x, linear interpolation.
template <typename T> 
void upsample_2x(struct ImageObj<T> * img_dst, struct ImageObj<T> * img_src)
{
  float scale = 2.0f;

  int srcW = img_src->w, srcH = img_src->h;
  int dstW = srcW << 1, dstH = srcH << 1;
  init(img_dst, dstW, dstH);

  T * srcData = img_src->data;
  T * dstData = img_dst->data;

  int end_col = dstW - ceilf(scale);	
  for (int r = 0; r < dstH; r ++)
    {
      float ori_r = r / scale;
      int r1 = (int) ori_r;
      float dr = ori_r - r1;
      for (int c = 0; c < end_col ; c ++)
	{
	  float ori_c = c / scale;
	  int c1 = (int) ori_c;
	  float dc = ori_c - c1;

	  int idx = r1 * srcW + c1;
	  dstData[r * dstW + c] = /* (unsigned char) */ ((1-dr) * (1-dc) * srcData[idx]
							 + dr * (1-dc) * (r1 < srcH - 1 ? srcData[idx + srcW] : srcData[idx])
							 + (1-dr)* dc * srcData[idx + 1]
							 + dr * dc * ((r1 < srcH - 1) ? srcData[idx + srcW + 1] : srcData[idx]));
	}
      for (int c = end_col; c < dstW ; c ++)
	{
			
	  float ori_c = c / scale;
	  int c1 = (int) ori_c;
	  float dc = ori_c - c1;
	  int idx = r1 * srcW + c1;
	  dstData[r * dstW + c] = /* (unsigned char) */ ((1-dr) * (1-dc) * srcData[idx]
							 + dr * (1-dc) * (r1 < srcH - 1 ? srcData[idx + srcW] : srcData[idx])
							 + (1-dr)* dc * srcData[idx]
							 + dr * dc * srcData[idx]);
	}
    }
}

// Downsample the image by 2x, nearest neighbor interpolation.
template <typename T> 
void downsample_2x(struct ImageObj<T> * img_dst, struct ImageObj<T> * img_src)
{
	int srcW = img_src->w, srcH = img_src->h;
	int dstW = srcW >> 1, dstH = srcH >> 1;
	init(img_dst, dstW, dstH);

	T * srcData = img_src->data;
	T * dstData = img_dst->data;

	for (int r = 0; r < dstH; r ++)
	{
	  int ori_r = r << 1;
		for (int c = 0; c < dstW; c ++)
		{
			int ori_c = c << 1;
			dstData[r * dstW + c] = srcData[ori_r * srcW + ori_c];
		}
	}
}


#endif
