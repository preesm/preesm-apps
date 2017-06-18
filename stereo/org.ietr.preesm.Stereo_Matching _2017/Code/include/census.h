/*
 * census.h
 *
 *  Created on: 22 févr. 2016
 *      Author: jmenant
 */

#ifndef CENSUS_H_
#define CENSUS_H_

#include "../include/image.h"
#include "../include/costMatrix.h"

/*!
 * \brief count the number of bit setted in a 8 bit word.
 * \param v input value
 * \return number of bits to one.
 */
#if defined( __GNUC__)
static inline unsigned int bitcount_u8(unsigned int v)
{
    return __builtin_popcount(v);
}
#else
static inline uint8_t bitcount_u8(uint8_t v)
{
    uint8_t retour = ( v & 0x55 ) + ( ( v >> 1 ) & 0x55);
    retour = ( retour & 0x33 ) + ( ( retour >> 2 ) & 0x33 );
    retour = (retour + (retour >> 4)) & 0x0F;
    return retour;
}
#endif


static inline uint8_t censusBytePerPixels(uint8_t winsize)
{
	int tmp = winsize;
	tmp = tmp*tmp + 6;
	tmp = tmp >> 3;
	return tmp;
}

static inline uint8_t census_compare(const uint8_t* cenl, const uint8_t* cenr, size_t bpp)
{
	uint8_t val = 0;
	size_t i;

	for(i=0; i<bpp; i++)
	{
		val += bitcount_u8((*cenr++) ^ (*cenl++));
	}
	return val;
}

void census(const struct str_image_gray* in, uint8_t* out, uint8_t winsize);
void census_cost_d(const uint8_t* cenl, const uint8_t* cenr, size_t bpp, int disp, struct str_image_gray* out);
void census_cost_dxy(const struct dispMatrix_size* size, const struct str_image_gray* iml, const struct str_image_gray* imr, size_t winsize, uint8_t* out);

#endif /* COMMON_CANSI_CENSUS_CENSUS_H_ */
