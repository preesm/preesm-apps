/*
	============================================================================
	Name        : census.h
	Author      : jmenant
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for BFA aggregation.
	============================================================================
*/

#ifndef CENSUS_H_
#define CENSUS_H_


#include <stdint.h>
#include "preesm.h"
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

static inline uint8_t census_compare(const uint8_t* cenl, const uint8_t* cenr, uint8_t bpp)
{
	uint8_t val = 0;
	int i;

	for(i=0; i<bpp; i++)
	{
		val += bitcount_u8((*cenr++) ^ (*cenl++));
	}
	return val;
}

void census(int height, int width, uint8_t censusSize,IN const uint8_t* in, OUT uint8_t* out);
void census_cost_d(int height, int width, int bpp, IN const uint8_t* lcen, IN const uint8_t* rcen, IN uint8_t * disp, OUT uint8_t * CostOUT);


#endif /* COMMON_CANSI_CENSUS_CENSUS_H_ */
