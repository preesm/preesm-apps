#include "census_PREESM_parallel.h"




void census_PREESM(struct str_image_gray * slice_r, struct str_image_gray * slice_l, int width, int height,int n_disp, int census_size, int select, uint8_t * slice_cost)
{
    if(select == 0)
    {
        printf("Cost Construction done using CENSUS \n");
		
		//Define the size structure necessary for functions of census.h
        struct dispMatrix_size size = {slice_r->w,slice_r->h,n_disp};

        #ifdef VERBOSE
            printf("Census on image : (%d,%d) \n",slice_r->h,slice_r->w);
        #endif // VERBOSE

        census_cost_dxy(&size, slice_r,slice_l, census_size, slice_cost); // image l and r switched due to an error in the Judicael's Code


        #ifdef VERBOSE
            printf("Census cost construction succeed! \n\n");
        #endif // VERBOSE
    }
    else
    {
        ;
    }

}
