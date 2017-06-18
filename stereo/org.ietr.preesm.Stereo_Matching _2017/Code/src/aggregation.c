#include "bfa.h"
#include <stdio.h>

//#define APPR_NORM

/*!
 * \brief aggregate vertically a cost map.
 * \param height : height of image in pixels
 * \param width : width of image in pixels
 * \param delta : aggregation distance in pixels
 * \param cost_in : pointer to input cost (before vertical aggregation). Size
 *        must be (height*width).
 * \param weight : corresponding weight computed with compute_vweigth with the
 * 		  same delta. Size must be (height*width).
 * \param cost_out : pointer to output cost (after vertical aggregation). Size
 *        must be (height*width).
 */
void aggregateV(
	int height, int width,
	int delta,
	uint8_t* cost_in,
	uint8_t* weight,
	uint8_t* cost_out)
{
	int x,y;

	/*pointer to costs (cost - delta, cost, cost + delta)*/
	uint8_t *p_im, *p_i, *p_ip;
	/*pointer to weight (weight + delta, weight - delta)*/
	uint8_t *p_wp, *p_wm;
	uint8_t *p_out;

	/*weights values*/
	uint8_t wp, wm;
	/*inputs values*/
	uint8_t inp, in, inm;
	uint32_t num;	/*temp value for computing*/
#ifdef APPR_NORM
	uint16_t w0;
#else
	uint32_t den;
#endif
	/*main case*/
	p_im = cost_in;
	p_i = cost_in;


	p_wm = weight;
	p_wp = weight + width*delta;

	p_out = cost_out;
	/*border case, just copy*/
	for(y=0; y<delta; y++)
	{
		for(x=0; x<width; x++)
		{
			*p_out++ = *p_i++;
		}
	}

	p_ip = p_i + width*delta;

	for(y=delta; y<(height-delta); y++)
	{
		for(x=0; x<width; x++)
		{
			/*read inputs*/
			wp = *p_wp++;
			wm = *p_wm++;
			inp = *p_ip++;
			in = *p_i++;
			inm = *p_im++;

			/*compute*/
#ifdef APPR_NORM
			num = (uint16_t)wp*inp;
			num += (uint16_t)wm*inm;
			w0 = 1024 - wp - wm;
			num += (uint32_t)(in*w0);
			/*round result*/
			num = (num + 0x0200) >> 10;
#else
			num = (uint16_t)wp*inp;
			num += (uint16_t)wm*inm;
			num += (uint16_t)in << 8;

			den = wp;
			den += wm;
			den += 256;

			num += den >> 1;
			num = num/den;
#endif


			/*store output*/
			*p_out++ = num;
		}
	}

	/*border case, just copy*/
	for(y=height-delta; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			*p_out++ = *p_i++;
		}
	}
}


/*!
 * \brief aggregate horizontally a cost map.
 * \param height : height of image in pixels
 * \param width : width of image in pixels
 * \param delta : aggregation distance in pixels
 * \param cost_in : pointer to input cost (before horizontal aggregation). Size
 *        must be (height*width).
 * \param weight : corresponding weight computed with compute_hweigth with the
 * 		  same delta. Size must be (height*width).
 * \param cost_out : pointer to output cost (after horizontal aggregation). Size
 *        must be (height*width).
 */
void aggregateH(
	int height, int width,
	int delta,
	uint8_t* cost_in,
	uint8_t* weight,
	uint8_t* cost_out)
{
	int x,y;

	/*pointer to costs (cost - delta, cost, cost + delta)*/
	uint8_t *p_im, *p_i, *p_ip;
	/*pointer to weight (weight + delta, weight - delta)*/
	uint8_t *p_wp, *p_wm;
	uint8_t *p_out;

	/*weights values*/
	uint8_t wp, wm;
	/*inputs values*/
	uint8_t inp, in, inm;
	uint32_t num;	/*temp value for computing*/
	#ifdef APPR_NORM
		uint16_t w0;
	#else
		uint32_t den;
	#endif

	/*main case*/
	p_out = cost_out;
	for(y=0; y<height; y++)
	{

		p_i = cost_in + y*width;
		/*border case, just copy*/
		for(x=0; x<delta; x++)
		{
			*p_out++ = *p_i++;
		}

		p_im = cost_in + y*width;
		p_i = p_im + delta;
		p_ip = p_i + delta;

		p_wm = weight + y*width;
		p_wp = weight + y*width + delta;

		for(x=delta; x<(width-delta); x++)
		{
			/*read inputs*/
			wp = *p_wp++;
			wm = *p_wm++;
			inp = *p_ip++;
			in = *p_i++;
			inm = *p_im++;

			/*compute*/
#ifdef APPR_NORM
			num = (uint16_t)wp*inp;
			num += (uint16_t)wm*inm;
			w0 = 1024 - wp - wm;
			num += (uint32_t)(in*w0);
			/*round result*/
			num = (num + 0x0200) >> 10;
#else
			num = (uint16_t)wp*inp;
			num += (uint16_t)wm*inm;
			num += (uint16_t)in << 8;

			den = wp;
			den += wm;
			den += 256;

			num += den >> 1;
			num = num/den;
#endif
			/*store output*/
			*p_out++ = num;
		}

		/*right border case, just copy*/
		for(x=width-delta; x<width; x++)
		{
			*p_out++ = *p_i++;
		}
	}
}

void bfa_aggregation(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* costOut, const struct str_image_rgb* iml, const struct str_image_rgb* imr, int thr_weight, int cst_cd, int niter, int dmax)
{
	//weight
	int deltas[niter];// = {1, 4, 9, 16, 25, 3};

	int i, d;
	//int niter = sizeof(deltas)/sizeof(deltas[0]);

    for(i=0; i<niter; i++)
    {
        deltas[i] = ((i+1)*(i+1))%dmax;
    }


	/*buffer for algorithm*/
	struct str_image_gray vweight[niter];
	struct str_image_gray hweight[niter];
	struct str_image_gray cost1, cost2, buffval;

	/*compute weight*/
	for(i=0; i<niter; i++)
	{
		image_gray_init(&vweight[i], iml->w, iml->h);
		image_gray_init(&hweight[i], iml->w, iml->h);

		compute_vweigth(vweight[i].h, vweight[i].w,
						deltas[i],
						iml->r, iml->g, iml->b,
						vweight[i].g,
						thr_weight, cst_cd);

		compute_hweigth(hweight[i].h, hweight[i].w,
						deltas[i],
						iml->r, iml->g, iml->b,
						hweight[i].g,
						thr_weight, cst_cd);
	}

	image_gray_init(&cost1, iml->w, iml->h);
	image_gray_init(&cost2, iml->w, iml->h);
	image_gray_init(&buffval, iml->w, iml->h);

	for(d=0; d<size->dsize; d++)
	{
		costMatrix_dxy_getDisparity(size, d, costIn, cost1.g);

		for(i=0; i<niter; i++)
		{
			aggregateV(imr->h, imr->w, deltas[i], cost1.g, vweight[i].g, cost2.g);
			aggregateH(imr->h, imr->w, deltas[i], cost2.g, hweight[i].g, cost1.g);
		}

		costMatrix_dxy_addDisparity(size, d, costOut, cost1.g);
	}

	image_gray_destroy(&cost1);
	image_gray_destroy(&cost2);
	image_gray_destroy(&buffval);

	for(i=0; i<niter; i++)
	{
		image_gray_destroy(&vweight[i]);
		image_gray_destroy(&hweight[i]);
	}
}
