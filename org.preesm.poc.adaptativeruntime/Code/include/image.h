
#ifndef _img_h_
#define _img_h_

#include "adaptive_runtime.h"


#define XSAMPLING 640
#define YSAMPLING 480


typedef struct {
	unsigned char r[XSAMPLING * YSAMPLING];
	unsigned char g[XSAMPLING * YSAMPLING];
	unsigned char b[XSAMPLING * YSAMPLING];
} rgbimg;

#endif
