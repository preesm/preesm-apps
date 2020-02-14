/*
	============================================================================
	Name        : weight_calc.c
	Author      : jmenant
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for BFA aggregation.
	============================================================================
*/
#include <string.h>
#include <math.h>

#include "../include/bfa.h"

#define LIN_METH

/*
 * \brief compute vertical weight for a specific delta.
 * \param height : height of image in pixels.
 * \param width : width of image in pixels.
 * \param delta : aggregation distance in pixels.
 * \param imr : red values of input image. Size must be (height*width).
 * \param img : green values of input image. Size must be (height*width).
 * \param imb : blues values of input image. Size must be (height*width).
 * \param out : Ouput weight table. Size must be (height*width).
 */
void compute_vweight(
	int height, int width,
	int thr_weight,
	int cst_cd,
	IN uint8_t * deltas,
	IN const uint8_t* iml,
	OUT uint8_t* out)
{

	/*index variables*/
	unsigned int x, y;
	unsigned int idxp = 0, idx = 0;

	/*compute variables*/
#ifdef LIN_METH
	uint16_t acc;
	uint8_t cr, cg, cb, d1, temp;

	/*constants*/
	uint8_t constdistance = 255-(*deltas)*cst_cd;
#else

	float acc, temp;

	float constdistance = -*delta/36.;
	float cr, cg, cb, d1;
#endif


	idx = 0;
	idxp = *deltas*width*3;

	/*loop around image*/
	/* we takes a pixel at y and y + delta, stops at height-delta */
	for(y=0; y<(height-*deltas); y++)
	{
		for(x=0; x<width; x++)
		{
			/*get cur rgb*/
			cr = iml[idx+0];
			cg = iml[idx+1];
			cb = iml[idx+2];

			/*compute formula*/

#ifdef LIN_METH
			/*pixel similarity (sum of absolute difference of RGB values)*/
			d1 = iml[idxp+0];
			acc =  (d1>cr)?(d1-cr):(cr-d1);
			d1 = iml[idxp+1];
			acc += (d1>cg)?(d1-cg):(cg-d1);
			d1 = iml[idxp+2];
			acc += (d1>cb)?(d1-cb):(cb-d1);

			/*saturation*/
			temp = (acc > thr_weight)?(thr_weight):acc;
			/*reverse value and enlarge dynamic*/
			temp = (thr_weight - temp)*(255/thr_weight);
			/*Adjusts value with a distance coefficient (fixed multiplication)*/
			temp = ((uint16_t)(temp*constdistance+0x80))>>8;
#else
			d1 = (float)imr[idxp] - cr;
			acc =  d1*d1;
			d1 = (float)img[idxp] - cg;
			acc +=  d1*d1;
			d1 = (float)imb[idxp] - cb;
			acc +=  d1*d1;

			acc = sqrtf(acc)/16.;
			temp = exp(constdistance - acc)*255.;
#endif


			/*store results*/
			out[idx/3] = temp;

			idx+=3;
			idxp+=3;
		}
	}
}

/*
 * \brief compute horizontal weight for a specific delta.
 * \param height : height of image in pixels.
 * \param width : width of image in pixels.
 * \param delta : aggregation distance in pixels.
 * \param imr : red values of input image. Size must be (height*width).
 * \param img : green values of input image. Size must be (height*width).
 * \param imb : blues values of input image. Size must be (height*width).
 * \param out : Ouput weight table. Size must be (height*width).
 */
void compute_hweight(
	int height, int width,
	int thr_weight,
	int cst_cd,
	IN uint8_t * deltas,
	IN const uint8_t* iml,
	OUT uint8_t* out)
{

	/*index variables*/
	unsigned int x, y;
	unsigned int idxp = 0, idx = 0;

#ifdef LIN_METH
	/*compute variables*/
	uint16_t acc;
	uint8_t cr, cg, cb, d1, temp;

	/*constants*/
	uint8_t constdistance = 255-(*deltas)*cst_cd;
#else

	float acc, temp;

	float constdistance = -*delta/36.;
	float cr, cg, cb, d1;
#endif

	/*loop around image*/
	for(y=0; y<height; y++)
	{
		idx = width*y*3;
		idxp = idx + *deltas*3;
		/* we takes a pixel at x and x + delta, stops at width-delta */
		for(x=0; x<(width-*deltas); x++)
		{
			/*get cur rgb*/
			cr = iml[idx+0];
			cg = iml[idx+1];
			cb = iml[idx+2];

			/*compute formula*/

#ifdef LIN_METH
			/*pixel similarity (sum of absolute difference of RGB values)*/
			d1 = iml[idxp+0];
			acc =  (d1>cr)?(d1-cr):(cr-d1);
			d1 = iml[idxp+1];
			acc += (d1>cg)?(d1-cg):(cg-d1);
			d1 = iml[idxp+2];
			acc += (d1>cb)?(d1-cb):(cb-d1);

			/*saturation*/
			temp = (acc > thr_weight)?(thr_weight):acc;
			/*reverse value and enlarge dynamic*/
			temp = (thr_weight - temp)*(255/thr_weight);
			/*Adjusts value with a distance coefficient (fixed point  multiplication)*/
			temp = ((uint16_t)(temp*constdistance))>>8;
#else

			d1 = (float)imr[idxp] - cr;
			acc =  d1*d1;
			d1 = (float)img[idxp] - cg;
			acc +=  d1*d1;
			d1 = (float)imb[idxp] - cb;
			acc +=  d1*d1;

			acc = sqrtf(acc)/16.;
			temp = exp(constdistance - acc)*255.;
#endif

			out[idx/3] = temp;

			idx+=3;
			idxp+=3;
		}
	}
}