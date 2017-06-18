#ifndef READ_IMAGES_PREESM_H
#define READ_IMAGES_PREESM_H

#include <stdio.h>

#include "image_load.h"
#include "x86.h"

#define PATH_L "../images/teddyL.ppm"
#define PATH_R "../images/teddyR.ppm"

//#define VERBOSE

/**
* Load images both in gray and rgb
*
* \param[in] width Width of the input images
* \param[in] height Height of the input images
* \param[out] im_l_gray Pointer on the loaded image left in gray scale
* \param[out] im_r_gray Pointer on the loaded image right in gray scale
* \param[out] im_l_rgb Pointer on the loaded image left in rgb
* \param[out] im_r_rgb Pointer on the loaded image right in rgb
*/
int load_images(int  width , int  height, struct str_image_gray *im_l_gray, struct str_image_gray *im_r_gray, struct str_image_rgb *im_l_rgb, struct str_image_rgb *im_r_rgb);


#endif // READ_IMAGES_PREESM_H

