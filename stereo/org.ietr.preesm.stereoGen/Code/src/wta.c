/*
	============================================================================
	Name        : wta.c
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the WTA selection.
	============================================================================
*/

#include <string.h>
#include <image_load.h>
#include "wta.h"

void wta_selection(int height, int width, int ndisp, IN const uint8_t* costIN, OUT uint8_t* raw)
{
	int x, y, d;

	uint8_t vmin, disp, tmp;

	for(y=0; y <height; y++) {
		for (x = 0; x < width; x++) {
			vmin = costIN[y*width+x];
			disp = 0;
			for (d = 1; d < ndisp; d++) {
				tmp = costIN[d*height*width +(y*width+x)];
				if (tmp < vmin) {
					vmin = tmp;
					disp = d;
				}
			}
			raw[y*width+x] = disp;
		}
	}
	struct str_image_gray curd;
	image_gray_init(&curd,width,height);
	memcpy(curd.g,raw,sizeof(uint8_t)*width*height);
	image_gray_save("raw.ppm",&curd);
}

