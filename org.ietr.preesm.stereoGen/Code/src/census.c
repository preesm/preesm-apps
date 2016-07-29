/*
 * census.c
 *
 *  Created on: 22 févr. 2016
 *      Author: jmenant
 */

#include "census.h"

void census(int height, int width, uint8_t censusSize,IN const uint8_t* in, OUT uint8_t* out)
{
	int x, y, p;
	int xc, yc;

	uint8_t bpp = censusBytePerPixels(censusSize);
	int bit_pos;
	uint8_t byte, ref, val;

	int bmin = (censusSize/2);
	int bmax = (censusSize+1)/2;

	int ybmin, ybmax, xbmin, xbmax;

	//zeroing output (required for correct output)
	for(p=0; p<(width*height*bpp); p++)
	{
		out[p] = 0;
	}

	//loop over image, x, y coordinates and p absolute buffer position
	for(y=0, p=0; y<height; y++)
	for(x=0; x<width; x++, p++)
	{
		//compute valid range for census
		ybmin = (y > bmin) ? bmin : y;
		ybmax = (y+bmax < height) ? bmax : height - y;
		xbmin = (x > bmin) ? bmin : x;
		xbmax = (x+bmax < width) ? bmax : width - x;

		ref = in[p];
		byte = 0;

		//zeroing unused first lines (if any)
		bit_pos = (bmin - ybmin)*censusSize; //number of bit to zero

		//census computing
		for(yc = (y-ybmin); yc < (y + ybmax); yc++)
		{
			//zeroing start of line if needed
			bit_pos += bmin - xbmin;

			//census core loop
			for(xc = (x-xbmin); xc < (x + xbmax); xc++)
			{
				byte = out[bit_pos >> 3];
				val = in[yc*width + xc];
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

void census_cost_d(int height, int width, int bpp, IN const uint8_t* lcen, IN const uint8_t* rcen, IN uint8_t * disp, OUT uint8_t * CostOUT)
{
	int x, y;

	/*pointer to walk on buffers*/
	const uint8_t* ptr_cl = lcen;
	const uint8_t* ptr_cr = rcen;
	uint8_t* ptr_o = CostOUT;

	/*data for computing*/
	uint8_t temp;

	for(y=0; y<height; y++)
	{
		/*compute border case*/
		for(x=0; x<*disp; x++)
		{
			/*load inputs*/
			temp = census_compare(ptr_cl, ptr_cr, bpp);

			/*dynamic adaptation and store result*/
			*ptr_o++ = temp;

			/*increment input ptr*/
			ptr_cl += bpp;
			/*left pointer doesn't move  for the first elements*/
		}

		/*compute main loop*/
		for(x=*disp; x<width; x++)
		{
			/*compute*/
			temp = census_compare(ptr_cl, ptr_cr, bpp);

			/*dynamic adaptation and store result*/
			*ptr_o++ = temp;

			/*increment input ptr*/
			ptr_cl+=bpp;
			ptr_cr+=bpp;
		}

		/*readjusts left image pointer to point on start of next line*/
		ptr_cr += *disp*bpp;
	}
}
