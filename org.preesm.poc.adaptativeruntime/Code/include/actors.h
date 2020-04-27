
#ifndef actors_h_
#define actors_h_

#include "preesm.h"
#include "image.h"
#include <spider.h>

typedef long Param;

void initDisplays();

void initRead();

void read(OUT rgbimg* img);

void computeBrightnessAndForward(IN rgbimg * img_in, OUT double * brightness, OUT rgbimg * img_out);


void doSomething(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter);

void blur(IN rgbimg * img_in, OUT rgbimg * img_out, int decision);

void canny(IN rgbimg * img_in, OUT rgbimg * img_out, int decision);

void sobel(IN rgbimg * img_in, OUT rgbimg * img_out, int decision);

void splitRGB(IN rgbimg * img_in, OUT unsigned char * R, OUT unsigned char * G, OUT unsigned char * B);

void mergeRGB(IN unsigned char * R, IN unsigned char * G, IN unsigned char * B, OUT rgbimg * img_out);

void configActor(IN double * brightness, Param * decision);

void configActor_sink(IN double * brightness);

#endif
