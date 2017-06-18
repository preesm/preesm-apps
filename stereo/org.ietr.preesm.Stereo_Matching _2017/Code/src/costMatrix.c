/*
 * costMatrix.c
 *
 *  Created on: 5 avr. 2016
 *      Author: jmenant
 */

#include "costMatrix.h"

#include "image_load.h"
#include <string.h>
#include <stdio.h>

void debugs_xy_u8(size_t xs, size_t ys, const uint8_t* costs, uint8_t min, uint8_t max, const char* prefix);

void costMatrix_dxy_addDisparity(const struct dispMatrix_size* size, imsize d, uint8_t* matrix, const uint8_t* curd)
{
	imsize x, y;
	imsize pdisp, pmat;

	for(y=0, pdisp = 0; y<size->ysize; y++)
	{
		pmat = y * size->xsize * size->dsize + d;
		for(x=0; x<size->xsize; x++, pdisp++)
		{
			matrix[pmat] = curd[pdisp];
			pmat += size->dsize;
		}
	}
}

void costMatrix_dxy_getDisparity(const struct dispMatrix_size* size, imsize d, const uint8_t* matrix, uint8_t* curd)
{
	imsize x, y;
	imsize pdisp, pmat;

	for(y=0, pdisp = 0; y<size->ysize; y++)
	{
		pmat = y * size->xsize * size->dsize + d;
		for(x=0; x<size->xsize; x++, pdisp++)
		{
			curd[pdisp] = matrix[pmat];
			pmat += size->dsize;
		}
	}
}
/*Only use this function for cyclopean view*/
void costMatrix_dxy_getLine(const struct dispMatrix_size* size, imsize y, const uint8_t* matrix, uint8_t* curd)
{
	imsize x, dd;
	int halfdispartity = (size->dsize-1)/2;
	int width_phib = (size->xsize-(halfdispartity + 1));

	for (x=0; x< width_phib; x++)
	{
		for (dd=0; dd < halfdispartity + 1; dd++) {
				curd[x*(size->dsize) + dd*2]    = matrix[y*size->dsize*size->xsize +(halfdispartity + x + dd)*(size->dsize) + 2*dd];
				curd[x*(size->dsize) + dd*2 +1] = matrix[y*size->dsize*size->xsize +(halfdispartity + x + dd + 1)*(size->dsize) + 2*dd + 1];
		}
	}
}

void costMatrix_debug_dxy_u8(const struct dispMatrix_size* size, const uint8_t* costs, const char* prefix)
{
	uint8_t min, max, cur;
	size_t d, p;
	char* str;
	uint8_t* buff;

	min = UINT8_MAX;
	max = 0;

	str = malloc(sizeof(char)*(strlen(prefix) + 5));

	for(p=0; p<(size->dsize*size->xsize*size->ysize); p++)
	{
		cur = costs[p];
		min = (cur < min) ? cur : min;
		max = (cur > max) ? cur : max;
	}

	buff = malloc(sizeof(buff[0]) * size->xsize * size->ysize);

	for(d=0; d<size->dsize; d++)
	{
		sprintf(str, "%s_%d", prefix, (int)d);
		for(p=0; p<(size->xsize*size->ysize); p++)
		{
			buff[p] = costs[p*size->dsize + d];
		}
		debugs_xy_u8(size->xsize, size->ysize, buff, min, max, str);
	}

	free(str);
	free(buff);

}

void debugs_xy_u8(size_t xs, size_t ys, const uint8_t* costs, uint8_t min, uint8_t max, const char* prefix)
{
	size_t p, x, y;

	uint8_t cur;

	float tmp, a;

	char*  str = malloc(sizeof(char)*(strlen(prefix) + 5));
	FILE* f;

	struct str_image_gray im;

	sprintf(str, "%s.txt", prefix);
	f = fopen(str, "w");
	if(f)
	{
		fprintf(f, "min : %d, max : %d\n", (int)min, (int)max);
	}

	image_gray_init(&im, xs, ys);

	a = 255./((float)(max-min));

	for(y=0, p=0; y<ys; y++)
	{
		for(x=0; x<xs; x++, p++)
		{
			cur = costs[p];
			if(f)
				fprintf(f, "%3d ", (int)cur);
			tmp = cur - min;
			tmp *= a;
			im.g[p] = tmp;
		}
		if(f)
			fprintf(f, "\n");
	}
	if(f)
		fclose(f);
	sprintf(str, "%s.png", prefix);
	image_gray_save(str, &im);

	image_gray_destroy(&im);
	free(str);
}


void debugs_xy_u16(size_t xs, size_t ys, const uint16_t* costs, uint16_t min, uint16_t max, const char* prefix)
{
	size_t p, x, y;

	uint16_t cur;

	float tmp, a;

	char*  str = malloc(sizeof(char)*(strlen(prefix) + 5));
	FILE* f;

	struct str_image_gray im;

	sprintf(str, "%s.txt", prefix);
	f = fopen(str, "w");
	if(f)
	{
		fprintf(f, "min : %d, max : %d\n", (int)min, (int)max);
	}

	image_gray_init(&im, xs, ys);

	a = (float)UINT8_MAX/((float)(max-min));

	for(y=0, p=0; y<ys; y++)
	{
		for(x=0; x<xs; x++, p++)
		{
			cur = costs[p];
			if(f)
				fprintf(f, "%5d ", (int)cur);
			tmp = cur - min;
			tmp *= a;
			im.g[p] = tmp;
		}
		if(f)
			fprintf(f, "\n");
	}
	if(f)
		fclose(f);
	sprintf(str, "%s.png", prefix);
	image_gray_save(str, &im);

	image_gray_destroy(&im);
	free(str);
}

void costMatrix_debug_dxy_u16(const struct dispMatrix_size* size, const uint16_t* costs, const char* prefix)
{
	uint16_t min, max, cur;
	size_t d, p;
	char* str;
	uint16_t* buff;

	min = UINT16_MAX;
	max = 0;

	str = malloc(sizeof(char)*(strlen(prefix) + 5));

	for(p=0; p<(size->dsize*size->xsize*size->ysize); p++)
	{
		cur = costs[p];
		min = (cur < min) ? cur : min;
		max = (cur > max) ? cur : max;
	}

	buff = malloc(sizeof(buff[0]) * size->xsize * size->ysize);

	for(d=0; d<size->dsize; d++)
	{
		sprintf(str, "%s_%d", prefix, (int)d);
		for(p=0; p<(size->xsize*size->ysize); p++)
		{
			buff[p] = costs[p*size->dsize + d];
		}
		debugs_xy_u16(size->xsize, size->ysize, buff, min, max, str);
	}

	free(str);
	free(buff);

}


