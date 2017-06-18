#include "bp1d_PREESM.h"


void bp1d_PREESM_parallel(const uint8_t* slice_cost, int height, int width, int n_slice, int n_disp, int phi0, int select, uint8_t* slice_disp_map)
{
    if(select == 0)
    {
        printf("Disparity Selection done using BP1D \n");
		
		//Define the size structure necessary for functions of census.h
        const struct dispMatrix_size size = {width,(int) floor(height/n_slice)+1 ,n_disp};
        #ifdef VERBOSE
                printf("BP1D on image : (%d,%d) \n",(int)floor(height/n_slice)+1,width);
        #endif // VERBOSE

        bp1d_selection(&size, slice_cost, slice_disp_map, phi0);

        #ifdef VERBOSE
            printf("BP1D selection succeed! \n");
        #endif // VERBOSE
    }
    else
    {
        ;
    }

}

