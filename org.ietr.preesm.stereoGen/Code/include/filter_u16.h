/*
	============================================================================
	Name        : filter_u16.h
	Author      : jmenant
	Version     : 1.0
	Copyright   : CECILL-C
	Description : filter implementation.
	============================================================================
*/

#ifndef _FILTER_U16_H_
#define _FILTER_U16_H_

#include <stdint.h>

void hfilter_u16(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps );
void vfilter_u16(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps);
void vfilter_u16_borderUp(int sizex, int nb, uint16_t* in, uint16_t* out, uint16_t* steps);
void vfilter_u16_borderDown(int sizex, int nb, uint16_t* in, uint16_t* out, uint16_t* steps);
void vfilter_u16_slice(int sizex, int sizey, int nb, uint16_t* in, uint16_t* out, uint16_t* steps);

#endif /* _FILTER_U16_H_ */
