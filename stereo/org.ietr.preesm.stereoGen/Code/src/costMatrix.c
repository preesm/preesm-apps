/*
	============================================================================
	Name        : costMatrix.c
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code to slice a cost matrix.
	============================================================================
*/
#include "costMatrix.h"
#include "image_load.h"
#include <string.h>
#include <stdio.h>


void costMatrix_dxy_getDisparity(int height,
								 int width,
								 int ndisp,
								 IN uint8_t *d,
								 IN const uint8_t* CostIN,
								 OUT uint8_t* CostOUT)
{
	int x, y;
	int pdisp, pmat;

	for(y=0, pdisp = 0; y<height; y++)
	{
		pmat = y * width * ndisp + *d;
		for(x=0; x<width; x++, pdisp++)
		{
			CostOUT[pdisp] = CostIN[pmat];
			pmat += ndisp;
		}
	}
}

/*Only use this function for cyclopean view*/
void costMatrix_dxy_getLine(int height,
			    int width,
			    int ndisp,
			    IN const uint8_t* CostIN,
			    OUT uint8_t* phiB)
{
	int x, y, dd;
	int halfdispartity = (ndisp-1)/2;
	int width_phib = (width-(halfdispartity + 1));
    for (y = 0; y < height; y++) {
        for (x = 0; x < width_phib; x++) {
            for (dd = 0; dd < halfdispartity + 1; dd++) {
                phiB[y*width_phib*(ndisp+1) + x * (ndisp+1) + dd * 2] = 		CostIN[y*width + (halfdispartity + x + 2*dd) + height*width*(2 * dd)];
                phiB[y*width_phib*(ndisp+1) + x * (ndisp+1) + dd * 2 + 1] = 	CostIN[y*width + (halfdispartity + x + 2*dd + 1) + height*width*(2 * dd + 1)];
            }
        }
    }
}


void costMatrix_debug_dxy_u8(int height, int width, int ndisp, IN const uint8_t* costs, int prefix, OUT uint8_t* costsOUT){
	uint8_t min, max, cur;
	size_t d, p;
	char* str;
	uint8_t* buff;

	min = UINT8_MAX;
	max = 0;

	str = malloc(sizeof(char)*20);

    struct str_image_gray curd;
    image_gray_init(&curd,width,height);

    for(p=0; p<(height*width*ndisp); p++)
	{
		cur = costs[p];
		min = (cur < min) ? cur : min;
		max = (cur > max) ? cur : max;
		costsOUT[p]=costs[p];
	}

	buff = malloc(sizeof(buff[0]) * width * height);

	for(d=0; d<ndisp; d++)
	{
		sprintf(str, "%d/debug_%d.ppm", prefix, (int)d);
        memcpy(curd.g,costs+width*height*d,sizeof(uint8_t)*width*height);
        image_gray_save(str,&curd);
	}
    image_gray_destroy(&curd);

	free(str);
	free(buff);
}


