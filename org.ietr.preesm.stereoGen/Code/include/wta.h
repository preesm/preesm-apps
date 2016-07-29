/*
	============================================================================
	Name        : wta.h
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the WTA selection.
	============================================================================
*/

#ifndef _WTA_H_
#define _WTA_H_

#include "costMatrix.h"
#include "preesm.h"

void wta_selection(int height, int width, int ndisp, IN const uint8_t* costIn, OUT uint8_t* raw);

#endif /* _WTA_H_ */
