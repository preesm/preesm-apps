/*
 * census.c
 *
 *  Created on: 22 févr. 2016
 *      Author: jmenant
 */

#include "census.h"

void census(const struct str_image_gray* in, uint8_t* out, uint8_t winsize)
{
	imsize x, y, p;
	imsize xc, yc;

	uint8_t bpp = censusBytePerPixels(winsize);
	imsize bit_pos;
	uint8_t byte, ref, val;

	imsize bmin = (winsize/2);
	imsize bmax = (winsize+1)/2;

	int ybmin, ybmax, xbmin, xbmax;

	//zeroing output (required for correct output)
	for(p=0; p<(in->w*in->h*bpp); p++)
	{
		out[p] = 0;
	}

	//loop over image, x, y coordinates and p absolute buffer position
	for(y=0, p=0; y<in->h; y++)
	for(x=0; x<in->w; x++, p++)
	{
		//compute valid range for census
		ybmin = (y > bmin) ? bmin : y;
		ybmax = (y+bmax < in->h) ? bmax : in->h - y;
		xbmin = (x > bmin) ? bmin : x;
		xbmax = (x+bmax < in->w) ? bmax : in->w - x;

		ref = in->g[p];
		byte = 0;

		//zeroing unused first lines (if any)
		bit_pos = (bmin - ybmin)*winsize; //number of bit to zero

		//census computing
		for(yc = (y-ybmin); yc < (y + ybmax); yc++)
		{
			//zeroing start of line if needed
			bit_pos += bmin - xbmin;

			//census core loop
			for(xc = (x-xbmin); xc < (x + xbmax); xc++)
			{
				byte = out[bit_pos >> 3];
				val = in->g[yc*in->w + xc];
				//compare and set correct bit if needed
				byte |= ((val > ref)?0x80:0) >> (bit_pos & 0x07);
				out[bit_pos >> 3] = byte;

				//remove central pixel
				if((xc != x) || (yc != y)) bit_pos++;
			}

			//zeroing end of line if needed
			bit_pos += (bmax - xbmax);
		}
		out += bpp;
	}
}

void census_cost_d(const uint8_t* cenl, const uint8_t* cenr, size_t bpp, int disp, struct str_image_gray* out)
{
	imsize x, y;

	/*pointer to walk on buffers*/
	const uint8_t* ptr_cl = cenl;
	const uint8_t* ptr_cr = cenr;
	uint8_t* ptr_o = out->g;

	/*data for computing*/
	uint8_t temp;

	for(y=0; y<out->h; y++)
	{
		/*compute border case*/
		for(x=0; x<disp; x++)
		{
			/*load inputs*/
			temp = census_compare(ptr_cl, ptr_cr, bpp);

			/*dynamic adaptation and store result*/
			*ptr_o++ = temp;

			/*increment input ptr*/
			ptr_cr += bpp;
			/*left pointer doesn't move  for the firsts elements*/
		}

		/*compute main loop*/
		for(x=disp; x<out->w; x++)
		{
			/*compute*/
			temp = census_compare(ptr_cl, ptr_cr, bpp);

			/*dynamic adaptation and store result*/
			*ptr_o++ = temp;

			/*increment input ptr*/
			ptr_cl+=bpp;
			ptr_cr+=bpp;;
		}

		/*readjusts left image pointer to point on start of next line*/
		ptr_cl += disp*bpp;
	}
}

void census_cost_dxy(const struct dispMatrix_size* size, const struct str_image_gray* iml, const struct str_image_gray* imr, size_t winsize, uint8_t* out)
{
	struct str_image_gray curd;
	uint8_t* cenl;
	uint8_t* cenr;

	size_t bpp = censusBytePerPixels(winsize);
	imsize d, i;
    int k = 128/(winsize*winsize-1);
    if(k<=1) k= 1;

	cenl = malloc(size->xsize*size->ysize*bpp*sizeof(uint8_t));
	cenr = malloc(size->xsize*size->ysize*bpp*sizeof(uint8_t));

	census(iml, cenl, winsize);
	census(imr, cenr, winsize);

	image_gray_init(&curd, size->xsize, size->ysize);

	for(d=0; d< size->dsize; d++)
	{
		census_cost_d(cenl, cenr, bpp, d, &curd);
        for(i=0; i<size->xsize*size->ysize; i++) curd.g[i]*=k;
		costMatrix_dxy_addDisparity(size, d, out, curd.g);
	}

	free(cenl);
	free(cenr);

	image_gray_destroy(&curd);
}
