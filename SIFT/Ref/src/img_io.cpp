/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Part of "img_io.cpp" code referred to David Lowe's code
	and code from here https://sites.google.com/site/5kk73gpu2011/.

	Revision history:
		September, 15, 2013: initial version.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "image.h"
#include "img_io.h"


void write_float_pgm(const char* filename, float* data, int w, int h, int mode)
{
	int i, j;
	struct ImageObj<unsigned char> * charImg = CreateImage<unsigned char>(w,h);
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			if(mode == 1){ // clop
				if( data[i*w+j] >= 255.0){
					charImg->data[i*w+j] = 255;
				} else if(data[i*w+j] <= 0.0){
					charImg->data[i*w+j]=0;
				} else{
					charImg->data[i*w+j]=(int)data[i*w+j];
				}
			}else if(mode == 2){ // abs, x10, clop
				int tmpInt = 
					(int)(fabs(data[i*w+j])*10.0);
				if( fabs(data[i*w+j]) >= 255){
					charImg->data[i*w+j] = 255;
				} else if(tmpInt <= 0){
					charImg->data[i*w+j] = 0;
				} else{
					charImg->data[i*w+j] = tmpInt;
				}
			}else{
				return;
			}
		}
	}
	write_pgm<unsigned char>(charImg, filename);
	release<unsigned char>(charImg);
}// write_float_pgm()

void setPixelRed(PPM_IMG* img, int r, int c) {
		if( (r >= 0) && (r < img->h) && (c >= 0) && (c < img->w)){
			img->img_r[r*img->w + c] = 0;
			img->img_g[r*img->w + c] = 0;
			img->img_b[r*img->w + c] = 255;
		}
}// setPixelRed()

void draw_red_circle(PPM_IMG* imgPPM, int r, int c, int cR){
		int cx = -cR, cy = 0, err = 2-2*cR; /* II. Quadrant */
		do {
			setPixelRed(imgPPM, r-cx, c+cy); /*	  I. Quadrant */
			setPixelRed(imgPPM, r-cy, c-cx); /*	 II. Quadrant */
			setPixelRed(imgPPM, r+cx, c-cy); /* III. Quadrant */
			setPixelRed(imgPPM, r+cy, c+cx); /*	 IV. Quadrant */
			cR = err;
			if (cR >  cx)
				err += ++cx*2+1; /* e_xy+e_x > 0 */
			if (cR <= cy)
				err += ++cy*2+1; /* e_xy+e_y < 0 */
		} while (cx < 0);
}// draw_red_circle()


void draw_circle(PPM_IMG* imgPPM, int r, int c, int cR, float thickness)
{
	int x,y;
	float f = thickness;
	for(x=-cR; x<=+cR; x++)  // column
	{
		for(y=-cR; y<=+cR; y++) // row
		{
			if ( (((x*x)+(y*y))>(cR*cR)-(f/2)) && (((x*x)+(y*y))<(cR*cR)+(f/2)) ) 
				setPixelRed(imgPPM, y + r, x + c);
		}
	}
}

//http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void rasterCircle(PPM_IMG* imgPPM, int r, int c, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	int x0 = r;
	int y0 = c;

	setPixelRed(imgPPM, x0, y0 + radius);
	setPixelRed(imgPPM, x0, y0 - radius);
	setPixelRed(imgPPM, x0 + radius, y0);
	setPixelRed(imgPPM, x0 - radius, y0);

	while(x < y)
	{
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) 
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    
		setPixelRed(imgPPM, x0 + x, y0 + y);
		setPixelRed(imgPPM, x0 - x, y0 + y);
		setPixelRed(imgPPM, x0 + x, y0 - y);
		setPixelRed(imgPPM, x0 - x, y0 - y);
		setPixelRed(imgPPM, x0 + y, y0 + x);
		setPixelRed(imgPPM, x0 - y, y0 + x);
		setPixelRed(imgPPM, x0 + y, y0 - x);
		setPixelRed(imgPPM, x0 - y, y0 - x);
	}
}


void draw_red_orientation(PPM_IMG* imgPPM, int x, int y, float ori, int cR) 
{
	int xe = (int) (x + cos(ori)*cR), ye = (int) (y + sin(ori)*cR);
	// Bresenham's line algorithm
	int dx =  abs(xe-x), sx = x<xe ? 1 : -1;
	int dy = -abs(ye-y), sy = y<ye ? 1 : -1;
	int err = dx+dy, e2; /* error value e_xy */

	for(;;)
	{  /* loop */
		//setPixelRed(imgPPM, x, y);
		setPixelRed(imgPPM, y, x);
		if (x==xe && y==ye) break;
		e2 = 2*err;
		if (e2 >= dy) { err += dy; x += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y += sy; } /* e_xy+e_y < 0 */
	}
}// draw_red_orientation()



void write_gray2ppm(const char* filename, unsigned char* data, int w, int h)
{
	FILE* fp;
	if ((fp = fopen(filename, "wb")) == NULL) {
		printf("Cannot write to file %s\n", filename);
		return;
	}
	//printf("Saving %s...", aFilename);
	/* Write header */
	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", w, h);
	fprintf(fp, "255\n");

	fwrite(data, sizeof(unsigned char), w*h*3, fp);
	fclose(fp);
}


void write_rgb2ppm(const char * filename, unsigned char* r, unsigned char* g, unsigned char* b, int w, int h) 
{
		FILE * out_file;
		int i;

		unsigned char* obuf = (unsigned char*)malloc(3*w*h*sizeof(unsigned char));

		for(i = 0; i < w*h; i ++){
			obuf[3*i + 0] = r[i];
			obuf[3*i + 1] = g[i];
			obuf[3*i + 2] = b[i];
		}
		out_file = fopen(filename, "wb");
		fprintf(out_file, "P6\n");
		fprintf(out_file, "%d %d\n255\n", w, h);
		fwrite(obuf,sizeof(unsigned char), 3*w*h, out_file);
		fclose(out_file);
		free(obuf);
}// write_ppm()
