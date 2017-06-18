/*
	============================================================================
	Name        : mux.c
	Author      : Florian Lemarchand
	Date        : 14/06/17
	Description : Mux or demux data from/to one of a bunch of channels depending on a select parameter
	============================================================================
*/

#include "mux.h"

int mux_construction(struct str_image_gray * in, struct str_image_gray * out0, struct str_image_gray * out1, int select)
{
    if(select == 0) 
    {
		// Structure init
        image_gray_init(out0,in->w,in->h);
		// Data copy
        memcpy(out0->g,in->g,in->w*in->h);
        return 0;
    }
    else if(select == 1)
    {
		// Structure init
        image_gray_init(out1,in->w,in->h);
		// Data copy
        memcpy(out1->g,in->g,in->w*in->h);
        return 0;
    }
    else
    {
        fprintf(stderr,"Incorrect value of select in %s. Should be 0 or 1\n",__FUNCTION__);
        return -1;
    }
}

int mux(int size, uint8_t * in, uint8_t * out0, uint8_t * out1, int select)
{

    if(select == 0)
    {
		// Data copy
        memcpy(out0,in,size);
        return 0;
    }
    else if(select == 1)
    {
		// Data copy
        memcpy(out1,in,size);
        return 0;
    }
    else
    {
        fprintf(stderr,"Incorrect value of select in %s. Should be 0 or 1\n",__FUNCTION__);
        return -1;
    }
}


int demux(int size, uint8_t * in0, uint8_t * in1, uint8_t * out, int select)
{
    if(select == 0)
    {	// Data copy
        memcpy(out,in0,size);
        return 0;
    }
    else if(select == 1)
    {
		// Data copy
        memcpy(out,in1,size);
        return 0;
    }
    else
    {
        fprintf(stderr,"Incorrect value of select in %s. Should be 0 or 1\n",__FUNCTION__);
        return -1;
    }
}
