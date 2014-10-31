#ifndef _IMG_IO_H_
#define _IMG_IO_H_

#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

void draw_circle(unsigned char* yy,
	unsigned int x, unsigned int y, int cR, int xSize, int ySize);
void setPixel(unsigned char* yy,
	unsigned int x, unsigned int y, int xSize, int ySize);
void draw_orientation(unsigned char* yy,
	unsigned int x, unsigned int y, float ori, int cR, int xSize, int ySize);

#endif//_IMG_IO_H_
