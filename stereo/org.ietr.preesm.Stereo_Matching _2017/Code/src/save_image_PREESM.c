/*
	============================================================================
	Name        : load_images_PREESM.c
	Author      : Florian Lemarchand
	Date        : 17/04/17
	Description : Function to save an array of uint8_t as an image
	============================================================================
*/

#include "save_image_PREESM.h"

int save_image_PREESM(int height, int width, uint8_t * disp_map)
{
    
    struct str_image_gray im ; // structure to fill

	// structure init
    if(image_gray_init(&im, width, height)) 
        return 1;
		
	// assign the uint8_t array as the data of the structure
    im.g = disp_map ; 
	
	// save the image
    if(image_gray_save(PATH_RES, &im))
        return 1;

    #ifdef VERBOSE
    printf("Result disparity map writing succed! \n");
    #endif // VERBOSE

	/*  Compare pixel by pixel the input to a reference image. The different pixel are set to 255 to highlight them  */
    #ifdef COMPARE_ON
    struct ref;
    int i;

    image_gray_init(&ref,width,height);
    image_gray_load(PATH_REF,&ref);


    for(i=0 ; i < height*width ; ++i)
    {
        if(im.g[i] != ref.g[i])
        {
            im.g[i]=
            printf("\n\n+++++++++++++++++++++++++++ Comparison FAILED! ++++++++++++++++++++++++++++++ \nFirst deference at cell  %d \n\n\n",i);
            printf("Expected: %d , Obtained: %d \n",ref.g[i],im.g[i]);
            im.g[i]=255;
        }
    }

    image_gray_save(PATH_RES,&im);

    printf("\n\n+++++++++++++++++++++++++++ Comparison OK! ++++++++++++++++++++++++++++++  \n\n\n");


    #endif // COMPARE_ON


    return 0 ;
}
