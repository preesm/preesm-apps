/*
	============================================================================
	Name        : wta_selection_parallel.c
	Author      : Florian Lemarchand
	Date        : 23/04/17
	Description : Functions designed to use code wta.h with different parameters.
                  Actually used for PREESM parallel implementation of WTA selection
                  algorithm.
	============================================================================
*/

#include "wta_selection_parallel.h"

void wta_selection_parallel(int width, int height, int n_disp, int n_slice, int select, const uint8_t* slice_cost, uint8_t* slice_disp)
{
    if(select == 1)
    {
        printf("Disparity Selection done using WTA \n");
		// Define a size structure required for function of wta.h
        struct dispMatrix_size size = {width,(floor(height/n_slice)+1),n_disp};

        #ifdef VERBOSE
            printf("WTA on image of size : (%d,%d) \n",width,height/n_slice);
        #endif // VERBOSE

        wta_selection(&size,slice_cost,slice_disp);

        #ifdef VERBOSE
            printf("WTA Cost Construction Succeded! \n");
        #endif // VERBOSE
    }
    else
    {
        ;
    }


}

