/*
	============================================================================
	Name        : bfa_aggregation_parallel.c
	Author      : Florian Lemarchand
	Version     : 1.0
	Date        : 23/04/17
	Description : Functions designed to use code bfa.h with different parameters.
                  Actually used for PREESM parallel implementation of BFA cost
                  aggregation algorithm.
	============================================================================
*/

#include "bfa_aggregation_parallel.h"

void bfa_aggregation_parallel(const struct str_image_rgb * im_l, const struct str_image_rgb * im_r, uint8_t * costs, uint8_t * refined_costs, int width, int height, int n_disp, int n_slice, int threshold_BFA, int cst_cd, int niter, int dmax, int nb_lines_sup, int select)
{
   if(select == 1) // BFA slected
        {
            printf("Removing extra data and Cost Aggregation done using BFA \n");

            int i, j;
            int number_of_full_slices; // Number of slices filled with only input data the others slices are adjusted with zero
            int height_full; // height of an original block of data to copy. Full slice
            int height_adjusted; // height of an original block of data to copy. Completed slice


            height_full = (int) floor(height/n_slice)+1;
            height_adjusted = (int) floor(height/n_slice);
            number_of_full_slices = height % n_slice ;


            /*Sizes to extract disparities into buffers*/
            const struct dispMatrix_size size_origin_full = {width,height_full + 2 * nb_lines_sup ,n_disp};
            const struct dispMatrix_size size_target_full = {width,height_full ,n_disp};

			/* Temporary storages */
            uint8_t * origin_disp_full = (uint8_t *)calloc(width*(height_full + 2 * nb_lines_sup) , sizeof(uint8_t)) ;
            uint8_t * target_disp_full = (uint8_t *)calloc(width*height_full  , sizeof(uint8_t)) ;
            uint8_t * unsliced_cost_map = (uint8_t *)calloc(width*height*n_disp  , sizeof(uint8_t)) ;
            uint8_t * refined_unsliced_cost_map = (uint8_t *)calloc(width*height*n_disp  , sizeof(uint8_t)) ;



            for(i=0 ; i<n_slice ; ++i)
            {
                if(i<number_of_full_slices)//Full Slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						//Extract disparity slice from input buffer
                       costMatrix_dxy_getDisparity(&size_origin_full,j,&costs[i*width*(height_full + 2 * nb_lines_sup)*n_disp],origin_disp_full) ;
                        //Remove extra data and copy to unsliced cost map 
					   memcpy(&unsliced_cost_map[height*width*j+i*height_full*width],&origin_disp_full[ nb_lines_sup*width],height_full*width);
                    }//end for on full disp
                }// END if Full Slice
                else// ELSE Adjusted slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						 //Extract disparity slice from input buffer
                        costMatrix_dxy_getDisparity(&size_origin_full,j,&costs[i*width*(height_full + 2 * nb_lines_sup)*n_disp],origin_disp_full) ;
						 //Remove extra data and copy to unsliced cost map 
						memcpy(&unsliced_cost_map[height*width*j+number_of_full_slices*height_full*width+(i-number_of_full_slices)*height_adjusted*width],&origin_disp_full[ nb_lines_sup*width],height_adjusted*width);
                    }//end for on adjusted disp
                }  // END ELSE Adjusted slice
            }//end for on slices

			/* BFA proceeding */
            const struct dispMatrix_size size = {width, height ,n_disp};
            bfa_aggregation(&size,unsliced_cost_map,refined_unsliced_cost_map,im_l,im_r,threshold_BFA,cst_cd,niter,dmax);

            free(unsliced_cost_map); // Not used anymore -> free

            for(i=0 ; i<n_slice ; ++i)
            {
                if(i<number_of_full_slices)//Full Slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						// extract disparity slice from unscliced cost map
                       memcpy(target_disp_full, &refined_unsliced_cost_map[height*width*j+i*height_full*width], height_full*width);
                        //introduce disparity slice into output buffer
					   costMatrix_dxy_addDisparity(&size_target_full,j,&refined_costs[i*width*height_full*n_disp],target_disp_full);
                    }//end for on full disp
                }// END if Full Slice
                else// ELSE Adjusted slice
                {
                    for(j=0 ; j<n_disp ; ++j)
                    {
						 // extract disparity slice from unscliced cost map
                        memcpy(target_disp_full, &refined_unsliced_cost_map[height*width*j+number_of_full_slices*height_full*width+(i-number_of_full_slices)*height_adjusted*width], height_adjusted*width);
                         //Complete slice with zeros
						memset(&target_disp_full[height_adjusted*width],0,width);
						 //introduce disparity slice into output buffer
                        costMatrix_dxy_addDisparity(&size_target_full,j,&refined_costs[i*width*height_full*n_disp],target_disp_full);

                    }//end for on adjusted disp
                }  // END ELSE Adjusted slice
            }//end for on slices

            free(origin_disp_full);
            free(target_disp_full);

        }// if select
    else // Other algorithm selected
    {
        ;//do nothing
    }//else select
}

