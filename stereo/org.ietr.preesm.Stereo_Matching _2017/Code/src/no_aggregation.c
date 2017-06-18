/*
	============================================================================
	Name        : wta_selection_parallel.c
	Author      : Florian Lemarchand
	Date        : 15/06/17
	Description : This function just copies the input to the output! It just allows us to represent
	a non aggregation actor in the streo matching dataflow graph .
	============================================================================
*/


#include "no_aggregation.h"

void no_aggregation(int select, int n_slice, int height, int width, int n_disp, int nb_lines_sup, uint8_t * in, uint8_t * out)
{
    if(select == 0) // No aggregation
        {
            printf("Removing extra data and No Cost Aggregation \n");
            
            int i, j;
            int number_of_full_slices; // Number of slices filled with only input data the others slices are adjusted with zero
            int height_full; // height of an original block of data to copy. Full slice
            int height_adjusted; // height of an original block of data to copy. Completed slice


            height_full = (int) floor(height/n_slice)+1;
            height_adjusted = (int) floor(height/n_slice);
            number_of_full_slices = height % n_slice ;
            
            /*Sizes to extract and introduce disparities from / into cost maps*/
            const struct dispMatrix_size size_origin_full = {width,height_full + 2 * nb_lines_sup ,n_disp};
            const struct dispMatrix_size size_target_full = {width,height_full ,n_disp};
			
			/* Temporary storages */
            uint8_t * origin_disp_full = (uint8_t *)calloc(width*(height_full + 2 * nb_lines_sup) , sizeof(uint8_t)) ;
			uint8_t * target_disp_full = (uint8_t *)calloc(width*height_full  , sizeof(uint8_t)) ;

            for(i=0 ; i<n_slice ; ++i)
            {
                if(i<number_of_full_slices)//Full Slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						//Extract disparity slice from input buffer
                       costMatrix_dxy_getDisparity(&size_origin_full,j,&in[i*width*(height_full + 2 * nb_lines_sup)*n_disp],origin_disp_full) ;
                        //Remove extra data
					   memcpy(target_disp_full,&origin_disp_full[ nb_lines_sup*width],height_full*width);
					    // Store disparity slice into output buffer
                       costMatrix_dxy_addDisparity(&size_target_full,j,&out[i*width*height_full*n_disp],target_disp_full);
                    }//end for on full disp
                }// END if Full Slice
                else// ELSE Adjusted slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						 //Extract disparity slice from input buffer
                        costMatrix_dxy_getDisparity(&size_origin_full,j,&in[i*width*(height_full + 2 * nb_lines_sup)*n_disp],origin_disp_full) ;
                         //Remove extra data
						memcpy(target_disp_full,&origin_disp_full[ nb_lines_sup*width],height_adjusted*width);
						 // Add a line of 0 to complete the slice
                        memset(&target_disp_full[height_adjusted*width],0,width);
						 // Store disparity slice into output buffer
                        costMatrix_dxy_addDisparity(&size_target_full,j,&out[i*width*height_full*n_disp],target_disp_full);
                    }//end for on adjusted disp
                }  // END ELSE Adjusted slice
            }//end for on slices
			
            free(origin_disp_full);
            free(target_disp_full);

        }// end if select

    else // Other algorithm selected
    {
        ; // Do Nothing
    }
}
