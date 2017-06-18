/*
	============================================================================
	Name        : load_images_PREESM.c
	Author      : Florian Lemarchand
	Date        : 17/04/17
	Description : Functions to load images in both gray and rgb
	============================================================================
*/

#include "load_images_PREESM.h"


int load_images(int  width , int  height, struct str_image_gray *im_l_gray, struct str_image_gray *im_r_gray, struct str_image_rgb *im_l_rgb, struct str_image_rgb *im_r_rgb)
{
	/* STRUCTURES INITIALISATION */
    image_gray_init(im_r_gray,width,height);
    image_gray_init(im_l_gray,width,height);
    image_rgb_init(im_r_rgb,width,height);
    image_rgb_init(im_l_rgb,width,height);

	/* IMAGES LOADING AND SIZE CHECK */
    if(!(image_gray_load(PATH_R ,im_r_gray) || image_gray_load(PATH_L ,im_l_gray) || image_rgb_load(PATH_R ,im_r_rgb)||image_rgb_load(PATH_L ,im_l_rgb)))
    {
            if( (im_l_gray->h != im_r_gray->h) || (im_l_gray->w != im_r_gray->w) )
            {
                printf("Input images don't have the same size! \n");
                return 1;
            }

            if (im_l_gray->h != height)
            {
                printf("Parameter height does not match with left image size: \n");
                printf("(height = %d) != (image_left.h = %d) \n", height , im_l_gray->h);
                return 1;
            }

             if (im_r_gray->h != height)
            {
                printf("Parameter height does not match with right image size: \n");
                printf("(height = %d) != (image_right.h = %d) \n", height , im_r_gray->h);
                return 1;
            }

            if (im_l_gray->w != width)
            {
                printf("Parameter width does not match with left image size! \n");
                printf("(width = %d) != (image_left.w = %d) \n", width , im_l_gray->w);
                return 1;
            }

            if(im_r_gray->w != width)
            {
                printf("Parameter width does not match with right image size! \n");
                printf("(width = %d) != (image_right.w = %d) \n", width , im_r_gray->w);
                return 1;
            }



        #ifdef VERBOSE
        printf("Images loaded! \n");
        #endif // VERBOSE

        startTiming(3);
    }


    else  return 1;


    return 0;
}


