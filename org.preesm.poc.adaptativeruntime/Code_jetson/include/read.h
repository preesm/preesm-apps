#ifndef READ_H
#define READ_H

#include <spider.h>

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

typedef long Param;

void initRead(int width, int height);

void read(int width, int height, OUT unsigned char *y, OUT unsigned char *u, OUT unsigned char *v);

void generateNothing(int height, int width, int value, OUT unsigned char *out);

#endif //READ_H

