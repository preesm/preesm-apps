#ifndef SPLIT_H
#define SPLIT_H

#include <string.h>
#include <stdint.h>
#include <math.h>
#include "image.h"
#include "image_load.h"

//#define VERBOSE

/**
* Function used to split both right and left input images of size width*height into n_slice
* slices of size (width*height/nbSlice). It is the developper responsibility
* to ensure that height is a multiple of nbSlice.
*
* @param n_slice
*        the number of slices produced
* @param width
*        the width of the input images
* @param height
*        the height of the input images
* @param im_r
*        the right input image of size width*height
* @param im_l
*        the left input image of size width*height
* @param slice_r
*        the output buffer containing the n_slice slices of (size (width*height/nbSlice)) from right image
* @param slice_l
*        the output buffer containing the n_slice slices of (size (width*height/nbSlice)) from left image
*/
int split(int n_slice, int width, int height, struct str_image_gray * im_r, struct str_image_gray * im_l, struct str_image_gray * slice_r, struct str_image_gray * slice_l);


/**
* Function used to assemble the  of n_slice slices of size (width*height/nbSlice)
* into an unique output size width*height.
*
* @param n_slice
*        the number of slices assembled
* @param width
*        the width of the output array of uint8_t
* @param height
*        the height of the output array of uint8_t
* @param n_disp
*        the depth of the output array of uint8_t
* @param slice_cost
*        the buffer containing the n_slice census results
* @param cost_out
*        the output array of size width*height*n_disp
*/
int merge(int n_slice, int width, int height, int n_disp, uint8_t * slice_disp_map, uint8_t * disp_map);


/**
* Function used to assemble the census result of n_slice slices into an unique output size width*height.
* This function remove (census_size%2) extra lines at the begining and the end of each slice.
*
* @param n_slice
*        the number of slices assembled
* @param width
*        the width of the output array of uint8_t
* @param height
*        the height of the output array of uint8_t
* @param n_disp
*        the depth of the output array of uint8_t
* @param nb_lines_sup
*        number of lines to remove at the bginning and the end
* @param in
*        the input buffer containing the slice to cut
* @param out
*        the output buffer of size width*height/n_slice
*/
void remove_lines_sup(int n_slice, int width, int height, int n_disp, int nb_lines_sup, uint8_t * in, uint8_t * out);

/**
* Function to split an image of size width*height into n_slice slices. This function does not require
* n_slice to be a multiple of the height, in such case the function create n_slice of the same height by adding zeros where no data exist.
* window_size%2 extra lines are added on top and bottom of the output slices to avoid side effects.
*
* @param n_slice
*        number of slices to produced
* @param width
*        width of the input image
* @param height
*        height of the input image
* @param window_size
*        size of the window to be used on the output images (3 for a 3x3 window)
* @param image
*        input image
* @param slices
*        output buffer containing the n_slice slices
*/
int split_complex(int n_slice, int width, int height, int window_size, struct str_image_gray * image, struct str_image_gray * slices);

/**
* Function to merge a set of n_slice slices into an image of size width*height. The function remove the
* window_size%2 extra lines added on top and bottom of each slice.
*
* @param n_slice
*        number of slices to produced
* @param width
*        width of the input image
* @param height
*        height of the input image
* @param window_size
*        size of the window to be used on the output images (3 for a 3x3 window)
* @param slices
*        input buffer containing the n_slice slices with extra lines
* @param image
*        output buffer  of size height*width
*/
void merge_complex(int n_slice, int width, int height, int window_size, uint8_t * slices, uint8_t * disp_map);

/**
* Same as merge_complex without extra line removing
*
* @param n_slice
*        number of slices to produced
* @param width
*        width of the input image
* @param height
*        height of the input image
* @param slices
*        input buffer containing the n_slice slices
* @param image
*        output buffer  of size height*width
*/
void merge_complex_without_extra_lines(int n_slice, int width, int height, uint8_t * slices, uint8_t * disp_map);




#endif // SPLIT_H
