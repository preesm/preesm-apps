/*
	============================================================================
	Name        : sad_cost_parallel.c
	Author      : Florian Lemarchand
	Date        : 23/04/17
	Description : Functions designed to use code from sad.h with different parameters.
                  Actually used for PREESM parallel implementation of SAD cost
                  construction algorithm.
	============================================================================
*/

#include "sad_cost_parallel.h"

void sad_cost_parallel(const struct str_image_gray * slice_l, const struct str_image_gray * slice_r, int width, int height, int n_disp, int thres, int select, uint8_t * out)
{
    if(select == 1)
    {
        printf("Cost Construction done using SAD \n");
        // Check that the images have the same size
        if((slice_l->w != slice_r->w) || (slice_l->h != slice_r->h))
        {
            fprintf(stderr,"Dimensions of Images Do Not Concord in : %s",__FUNCTION__);
            return;
        }
		// Size required for sad from sad.h
        struct dispMatrix_size size = {slice_l->w,slice_l->h,n_disp};

        #ifdef VERBOSE
            printf("SAD on image of size : (%d,%d) \n",slice_l->w,slice_l->h);
        #endif // VERBOSE

        sad_cost_dxy(&size,slice_r,slice_l,thres,out);

        #ifdef VERBOSE
            printf("SAD Cost Construction Succeded! \n");
        #endif // VERBOSE
    }
    else
    {
        ;
    }

}

