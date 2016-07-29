/*
 * filter_u16.c
 *
 *  Created on: 6 avr. 2016
 *      Author: jmenant
 */

#include "filter_u16.h"

void hfilter_u16(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps )
{
	int x, y;	/*position in image of current pixels*/
	int i;		/*iterate over pixels*/
	int s;		/*iterate over steps*/
	uint32_t tmp;	/*accumulator*/

	for(y=0; y<sizey; y++)
	{
		/*left border*/
		for(x=0; x<nb; x++)
		{
			tmp = 0;
			for(i=0, s=(nb-x); i<(nb + x + 1); i++, s++)
			{
				tmp += (uint32_t)in[y*sizex + i]*steps[s];
			}
			*out++ = tmp>>16;
		}

		/*nominal case*/
		for(x=nb; x<(sizex-nb); x++)
		{
			tmp = 0;
			for(i=(x-nb), s=0; i<=(x+nb); i++, s++)
			{
				tmp += (uint32_t)in[y*sizex + i]*steps[s];

			}
			*out++ = tmp>>16;
		}

		/*right border*/
		for(x=(sizex-nb); x<sizex; x++)
		{
			tmp = 0;
			for(i=x-nb, s=0; i<sizex; i++, s++)
			{
				tmp += (uint32_t)in[y*sizex + i]*steps[s];
			}
			*out++ = tmp>>16;
		}
	}
}

void vfilter_u16_borderUp(int sizex, int nb, uint16_t* in, uint16_t* out, uint16_t* steps)
{
	int x, y;
	int i;
	int s;

	uint32_t tmp;

	for(y=0; y<nb; y++)
	{
		for(x=0; x<sizex; x++)
		{
			tmp = 0;
			for(i=0, s=(nb-y); i<(nb+1+y); i++, s++)
			{
				tmp += (uint32_t)in[i*sizex + x]*steps[s];
			}
			*out++ = tmp>>16;
		}
	}
}

void vfilter_u16_borderDown(int sizex, int nb, uint16_t* in, uint16_t* out, uint16_t* steps)
{
	int x, y;
	int i;
	int s;

	uint32_t tmp;

	for(y=0; y<nb; y++)
	{
		for(x=0; x<sizex; x++)
		{
			tmp = 0;
			for(i = y, s=0; i<(2*nb); i++, s++)
			{
				tmp += (uint32_t)in[i*sizex + x] * steps[s];
			}
			*out++ = tmp>>16;
		}
	}
}

void vfilter_u16_slice(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps)
{
	int x, y;
	int i;
	int s;

	uint32_t tmp;

	for(y=nb; y<(sizey-nb); y++)
	{
		for(x=0; x<sizex; x++)
		{
			tmp = 0;
			for(i= ( y - nb ), s=0;  s<(2*nb+1); i++, s++)
			{
				tmp += (uint32_t)in[i*sizex + x]*steps[s];
			}
			*out++ = tmp>>16;
		}
	}
}

void vfilter_u16(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps)
{
	/*up border case*/
	vfilter_u16_borderUp(sizex, nb, in, out, steps);

	/*nominal case*/
	vfilter_u16_slice(sizex, sizey, nb, in, out + nb*sizex, steps);

	/*down border case*/
	vfilter_u16_borderDown(sizex, nb, in + (sizey-2*nb)*sizex, out + (sizey-nb)*sizex, steps);
}
