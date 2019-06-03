/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Revision history:
		September, 15, 2013: initial version.
*/

#ifndef COMMOM_H
#define COMMOM_H

#include <stdarg.h>
#include <math.h>

// *** Optimization options ***
#define SIFT_USE_FAST_FUNC				1

// *** Dump functions to get intermediate results ***
#define DUMP_OCTAVE_IMAGE				0
#define DUMP_GAUSSIAN_PYRAMID_IMAGE 0
#define DUMP_DOG_IMAGE					0

// Print out matched keypoint pairs in match_keypoints() function.
#define	PRINT_MATCH_KEYPOINTS 0


// *** Macro definition ***
// Macro definition#define PI				3.141592653589793f
#define _2PI			6.283185307179586f
#define PI_4			0.785398163397448f
#define PI_3_4			 2.356194490192345f
#define SQRT2			1.414213562373095f



// *** Fast math functions ***
// Fast Atan2() function
#define EPSILON_F	1.19209290E-07F
static inline float fast_atan2_f (float y, float x)
{
  float angle, r ;
  float const c3 = 0.1821F ;
  float const c1 = 0.9675F ;
  float abs_y    = fabsf (y) + EPSILON_F ;

  if (x >= 0) {
    r = (x - abs_y) / (x + abs_y) ;
    angle = PI_4; //
  } else {
    r = (x + abs_y) / (abs_y - x) ;
    angle = PI_3_4; //
  }
  angle += (c3*r*r - c1) * r ;

  return (y < 0) ? _2PI - angle : angle;
}

// Fast Sqrt() function
static inline float fast_resqrt_f (float x)
{
	/* 32-bit version */
	union {
		float x ;
		int  i ;
	} u ;

	float xhalf = (float) 0.5 * x ;

	/* convert floating point value in RAW integer */
	u.x = x ;

	/* gives initial guess y0 */
	u.i = 0x5f3759df - (u.i >> 1);

	/* two Newton steps */
	u.x = u.x * ( (float) 1.5  - xhalf*u.x*u.x) ;
	u.x = u.x * ( (float) 1.5  - xhalf*u.x*u.x) ;
	return u.x ;
}

static inline float fast_sqrt_f (float x)
{
	return (x < 1e-8) ? 0 : x * fast_resqrt_f (x) ;
}

static int good_octave(int nOctaves, int imgDouble, int img_height, int img_width) {
  int i = 1;
  for (; i < nOctaves; i++) {
    if (img_width % ((int) pow(2,i)) != 0 || img_height % ((int) pow(2,i)) != 0) {
	break;
      }
  }
  int octaveMax = i + imgDouble;
  if (octaveMax < imgDouble+3) {
    fprintf(stderr, "The size is not enough divisible by two (nOctaves = %d), leaving.\n", nOctaves);
    exit(-1);
  }
  fprintf(stderr, "!!! The original octave (%d) was too large, so we computed a new one (%d).\n", nOctaves, octaveMax);
  return octaveMax;
}

#endif
