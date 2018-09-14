/*
	============================================================================
	Name        : sad.c
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the SAD cost.
	============================================================================
*/

#include <string.h>
#include "sad.h"
#include "image_load.h"
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
void sad_cost_d(int height, int width, const uint8_t* iml, const uint8_t* imr, IN uint8_t * disp, uint8_t thres, OUT uint8_t * out)
{

	int x, y;

	/*pointer to walk on buffers*/
	const uint8_t* ptr_l = iml;
	const uint8_t* ptr_r = imr;
	uint8_t* ptr_o = out;

	for(y=0; y<height; y++)
	{
		/*compute border case*/
		for(x=0; x<*disp; x++)
		{
			/*dynamic adaptation and store result*/
			*ptr_o++ = sad_cost(*ptr_l, *ptr_r, thres);

			/*increment input ptr*/
			ptr_l++;
			/*left pointer doesn't move  for the firsts elements*/
		}

		/*compute main loop*/
		for(x=*disp; x<width; x++)
		{
			/*compute*/
			*ptr_o++ = sad_cost(*ptr_l, *ptr_r, thres);

			/*increment input ptr*/
			ptr_l++;
			ptr_r++;
		}

		/*readjusts left image pointer to point on start of next line*/
		ptr_r += *disp;
	}
}

