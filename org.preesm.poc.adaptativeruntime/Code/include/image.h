
#ifndef _img_h_
#define _img_h_

#include "adaptive_runtime.h"


#define XSAMPLING 800
#define YSAMPLING 600


typedef struct {
	unsigned char r[XSAMPLING * YSAMPLING];
	unsigned char g[XSAMPLING * YSAMPLING];
	unsigned char b[XSAMPLING * YSAMPLING];
} rgbimg;

#endif
