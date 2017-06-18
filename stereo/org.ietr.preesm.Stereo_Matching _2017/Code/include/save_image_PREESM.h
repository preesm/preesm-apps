#ifndef SAVE_IMAGE_PREESM_H
#define SAVE_IMAGE_PREESM_H

#include <stdio.h>
#include "image_load.h"
#include "x86.h"

#define PATH_REF "../images/reference_PJ2.ppm"
#define PATH_RES "../images/output.ppm"

//#define VERBOSE
//#define COMPARE_ON

/**
* Refines a set of cost maps using BFA aggregation model.
*
* \param[in] height height of the disparity map
* \param[in] width width of the disparity map
* \param[in] disp_map pointer on the disparity map to write
*/
int save_image_PREESM(int height, int width, uint8_t * disp_map);


#endif // SAVE_IMAGE_PREESM_H
