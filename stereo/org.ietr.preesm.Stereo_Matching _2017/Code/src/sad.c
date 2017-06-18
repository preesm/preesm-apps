/*
 * sad.c
 *
 *  Created on: 25 avr. 2016
 *      Author: jmenant
 */

#include "sad.h"

/**
 * \brief compute a sad between 2 pixels
 * \param p1 : pixel 1 value
 * \param p2 : pixel 2 value
 * \param t : saturation value, 20 is a good value (depend on snr of image)
 */
static inline uint8_t sad_cost(uint8_t p1, uint8_t p2, uint8_t t)
{
	//absolute difference
	uint8_t ret = (p1 > p2)?(p1-p2):(p2-p1);
	//saturation
	ret = (ret > t)?t:ret;
	return ret;
}

/**
 * \brief compute a cost map fo a given disparity
 * \param iml : left image (must be size height*width)
 * \param imr : right image (must be size height*width)
 * \param disp : the given disparity
 * \param thres : saturation value, 20 is a good value (depend on snr of image)
 * \param out : output buffer to store image
 */
void sad_cost_d(const uint8_t* iml, const uint8_t* imr, int disp, uint8_t thres, struct str_image_gray* out)
{

	imsize x, y;

	/*pointer to walk on buffers*/
	const uint8_t* ptr_l = iml;
	const uint8_t* ptr_r = imr;
	uint8_t* ptr_o = out->g;

	for(y=0; y<out->h; y++)
	{
		/*compute border case*/
		for(x=0; x<disp; x++)
		{
			/*dynamic adaptation and store result*/
			*ptr_o++ = sad_cost(*ptr_l, *ptr_r, thres);

			/*increment input ptr*/
			ptr_r++;
			/*left pointer doesn't move  for the firsts elements*/
		}

		/*compute main loop*/
		for(x=disp; x<out->w; x++)
		{
			/*compute*/
			*ptr_o++ = sad_cost(*ptr_l, *ptr_r, thres);

			/*increment input ptr*/
			ptr_l++;
			ptr_r++;
		}

		/*readjusts left image pointer to point on start of next line*/
		ptr_l += disp;
	}
}

/**
 * \brief compute a cost map for all disparity.
 * \param size : size of buffers
 * \param iml : left image (must be size height*width)
 * \param imr : right image (must be size height*width)
 * \param thres : saturation value, 20 is a good value (depend on snr of image)
 * \param out : output buffer to store image (must be xsize*ysize*dsize long)
 */
void sad_cost_dxy(const struct dispMatrix_size* size, const struct str_image_gray* iml, const struct str_image_gray* imr, uint8_t thres, uint8_t* out)
{
	struct str_image_gray curd;
	imsize d;

	image_gray_init(&curd, size->xsize, size->ysize);

	for(d=0; d< size->dsize; d++)
	{
		sad_cost_d(iml->g, imr->g, d, thres, &curd);
		costMatrix_dxy_addDisparity(size, d, out, curd.g);
	}

	image_gray_destroy(&curd);
}

