#ifndef IPM_H
#define IPM_H

#include "preesm.h"

void ipm(int width, int height, int x11, int x12, int x21, int x22, int y1,
		int y2, IN unsigned char *input, OUT unsigned char *output);

void ipmReverse(int width, int height, int x11, int x12, int x21, int x22, int y1,
		int y2, IN unsigned char *input, OUT unsigned char *output);

#endif // IPM_H
