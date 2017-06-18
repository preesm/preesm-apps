/*
	============================================================================
	Name        : mux.h
	Author      : Florian Lemarchand
	Date        : 14/06/17
	Description : Mux or demux data from one or to one of a bunch of channels depending on a select parameter
	============================================================================
*/


#ifndef MUX_H
#define MUX_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "image.h"

/**
* Function to transmit an image to one of two outputs
* Designed for Cost Construction step of PREESM Stereo Matching process
*
* @param in
*        data to transmit
* @param out0
*        output channel 1
* @param out1
*        output channel 2
* @param select
*        parameter to select the targeted output. 0 for out0, 1 for out1
*/

int mux_construction(struct str_image_gray * in, struct str_image_gray * out0, struct str_image_gray * out1, int select);


/**
* Function used to transmit a block of data to one out of two outputs
*
* @param size
*        size of the block of data to transmit
* @param in
*        data to transmit
* @param out0
*        output channel 1
* @param out1
*        output channel 2
* @param select
*        parameter to select the targeted output. 0 for out0, 1 for out1
*/

int mux(int size, uint8_t * in, uint8_t * out0, uint8_t * out1, int select);

/**
* Function used to transmit a block of data to an output from one of two inputs.
*
* @param size
*        size of the block of data to transmit
* @param in0
*        data to transmit 1
* @param in1
*        data to transmit 2
* @param out
*        output channel
* @param select
*        parameter to select the input to transmit. 0 for in0, 1 for in1
*/

int demux(int size, uint8_t * in0, uint8_t * in1, uint8_t * out, int select);

#endif // MUX_H
