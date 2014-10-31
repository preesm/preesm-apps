#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "img_io.h"

void draw_circle(unsigned char* yy, unsigned int x, unsigned int y, int cR, int xSize, int ySize){
    int cx = -cR, cy = 0, err = 2-2*cR; /* II. Quadrant */
    do {
        setPixel(yy, x-cx, y+cy,xSize,ySize); /*	  I. Quadrant */
        setPixel(yy, x-cy, y-cx,xSize,ySize); /*	 II. Quadrant */
        setPixel(yy, x+cx, y-cy,xSize,ySize); /* III. Quadrant */
        setPixel(yy, x+cy, y+cx,xSize,ySize); /*	 IV. Quadrant */
        cR = err;
        if (cR >  cx)
            err += ++cx*2+1; /* e_xy+e_x > 0 */
        if (cR <= cy)
            err += ++cy*2+1; /* e_xy+e_y < 0 */
    } while (cx < 0);
}// draw_red_circle()

void setPixel(unsigned char* yy, unsigned int x, unsigned int y, int xSize, int ySize) {
    if( (y >= 0) && (y < ySize) && (x >= 0) && (x < xSize)){
        yy[y*xSize + x] = 240;
    }
}// setPixel()

void draw_orientation(unsigned char* yy, unsigned int x, unsigned int y, float ori, int cR, int xSize, int ySize) {
    int xe,ye, dx, sx, dy, sy, err, e2;
    xe = x + cos(ori)*cR;
    ye = y + sin(ori)*cR;

    // Bresenham's line algorithm
    dx =  abs(xe-x);
	sx = x<xe ? 1 : -1;
    dy = -abs(ye-y);
	sy = y<ye ? 1 : -1;
    err = dx+dy; /* error value e_xy */

    for(;;){  /* loop */
        setPixel(yy, x,y,xSize,ySize);
        if (x==xe && y==ye) break;
        e2 = 2*err;
        if (e2 >= dy) { err += dy; x += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y += sy; } /* e_xy+e_y < 0 */
    }
}// draw_red_orientation()
