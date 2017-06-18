/*
 * wta.c
 *
 *  Created on: 25 avr. 2016
 *      Author: jmenant
 */

#include "wta.h"

void wta_selection(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* dispout)
{
	imsize x, y, d, pcost, pdisp;

	uint8_t vmin, disp, tmp;

	for(y=0, pcost=0, pdisp = 0; y <size->ysize; y++)
	for(x=0; x <size->xsize; x++, pdisp++)
	{
		vmin = costIn[pcost++];
		disp = 0;
		for(d=1; d<size->dsize; d++, pcost++)
		{
			tmp = costIn[pcost];
			if(tmp < vmin)
			{
				vmin = tmp;
				disp = d;
			}
		}
		dispout[pdisp] = disp;
	}
}

