/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Some algorithms used in this code referred to:
	1. OpenCV: http://opencv.org/
	2. VLFeat: http://www.vlfeat.org/

	The SIFT algorithm was developed by David Lowe. More information can be found from:
	David G. Lowe, "Distinctive image features from scale-invariant keypoints," 
	International Journal of Computer Vision, 60, 2 (2004), pp. 91-110.

	Pay attention that the SIFT algorithm is patented. It is your responsibility to use the code
	in a legal way. Patent information:
	Method and apparatus for identifying scale invariant features in an image 
	and use of same for locating an object in an image	David G. Lowe, US Patent 6,711,293 
	(March 23, 2004). Provisional application filed March 8, 1999. Asignee: The University of 
	British Columbia.

	Revision history:
		September, 15, 2013: initial version.
		July 8th, 2014, re-organized source code. 
*/

#ifndef EZSIFT_H
#define EZSIFT_H

#include "image.h"
#include "ordered_chained_list.h"


/****************************************
 * Constant parameters
 ***************************************/

// default number of sampled intervals per octave
#define SIFT_INTVLS 3

// default sigma for initial gaussian smoothing
#define SIFT_SIGMA 1.6f

// the radius of Gaussian filter kernel 
// Gaussian filter mask will be (2*radius+1)x(2*radius+1).
// People use 2 or 3 most.
#define SIFT_GAUSSIAN_FILTER_RADIUS 3.0f

// default threshold on keypoint contrast |D(x)|
#define SIFT_CONTR_THR 8.0f

// default threshold on keypoint ratio of principle curvatures
#define SIFT_CURV_THR 10.0f

// The keypoint refinement smaller than this threshold will be discarded.
#define SIFT_KEYPOINT_SUBPiXEL_THR 0.6f

// double image size before pyramid construction?
// 1 if true, 0 otherwise
#define SIFT_IMG_DBL 1 

// assumed gaussian blur for input image
#define SIFT_INIT_SIGMA 0.5f

// width of border in which to ignore keypoints
#define SIFT_IMG_BORDER 5

// maximum steps of keypoint interpolation before failure
#define SIFT_MAX_INTERP_STEPS 5

// default number of bins in histogram for orientation assignment
#define SIFT_ORI_HIST_BINS 36

// determines gaussian sigma for orientation assignment
#define SIFT_ORI_SIG_FCTR 1.5f // Can affect the orientation computation.

// determines the radius of the region used in orientation assignment
#define SIFT_ORI_RADIUS (3 * SIFT_ORI_SIG_FCTR) // Can affect the orientation computation.

// orientation magnitude relative to max that results in new feature
#define SIFT_ORI_PEAK_RATIO 0.8f

// maximum number of orientations for each keypoint location
//#define SIFT_ORI_MAX_ORI 4

// determines the size of a single descriptor orientation histogram
#define SIFT_DESCR_SCL_FCTR 3.f

// threshold on magnitude of elements of descriptor vector
#define SIFT_DESCR_MAG_THR 0.2f

// factor used to convert floating-point descriptor to unsigned char
#define SIFT_INT_DESCR_FCTR 512.f

// default width of descriptor histogram array
#define SIFT_DESCR_WIDTH 4

// default number of bins per histogram in descriptor array
#define SIFT_DESCR_HIST_BINS 8

// default value of the nearest-neighbour distance ratio threshold
// |DR_nearest|/|DR_2nd_nearest|<SIFT_MATCH_NNDR_THR is considered as a match.
#define SIFT_MATCH_NNDR_THR 0.65f

#define SIFT_INTERP_ORI_HIST 1
#define SIFT_USE_SMOOTH1 1
#define SIFT_ORI_BILINEAR 1


/****************************************
 * Parameters added by ahonorat
 ***************************************/
// arbritary max number of detected keypoints
#define SIFT_MAX_KEYPOINTS 1000 


/****************************************
 * Definitions
 ***************************************/

// this static allocation actually forbids
// to use other image sizes than 800x640
// it corresponds to nBins in extract_descriptor
#define DEGREE_OF_DESCRIPTORS 128
struct SiftKeypoint {
	int octave; // octave number
	int layer;  // layer number
	float rlayer; // real number of layer number

	float r; // normalized row coordinate
	float c; // normalized col coordinate
	float scale; // normalized scale

	float ri;	//row coordinate in that layer. 
	float ci;	//column coordinate in that layer.
	float layer_scale; // the scale of that layer

	float ori; // orientation in degrees.
	float mag; // magnitude

	float descriptors[DEGREE_OF_DESCRIPTORS];
};

// Match pair structure. Use for interest point matching.
struct MatchPair {
	int r1;
	int c1;
	int r2;
	int c2;
};


// Combine two images for interest points matching.
// Images are combined horizontally.
int combine_image(
	struct ImageObj<unsigned char> * out_image,
	struct ImageObj<unsigned char> * image1,
	struct ImageObj<unsigned char> * image2);

// Draw circles to incidate the keypoints.
// Bars in the circle incidate the orientation of the keypoints.
void  draw_keypoints_to_ppm_file(
	const char * out_filename,
	struct ImageObj<unsigned char> * image, 
	struct OrderedList<struct SiftKeypoint> * kpt_list);

// Draw lines between matched keypoints.
// The result image is stored in a ppm file.
int draw_match_lines_to_ppm_file(
	const char * filename,
	struct ImageObj<unsigned char> * image1,
	struct ImageObj<unsigned char> * image2,
	struct OrderedList<struct MatchPair> * match_list);

// Draw matched lines on a color RGB image.
int draw_line_to_rgb_image(
	unsigned char*  data,
	int w, int h,
	struct MatchPair * mp,
	int offset);


/****************************************
 *  SIFT Processing Functions
 ***************************************/
// Initialize SIFT parameters.
void init_sift_parameters(
	bool doubleFirstOctave = true,
	float contrast_threshold = 8.0f,
	float edge_threshold = 10.0f,
	float match_NDDR_threshold = 0.6f);

// Enable doubling of original image.
void double_original_image(bool doubleFirstOctave);

// Efficient Gaussian Blur function.
// 1. Use row buf to handle border pixel.
// 2. hori processing and transpose
int gaussian_blur(
	struct ImageObj<float> * in_image, 
	struct ImageObj<float>   out_image, 
	float * coef1d, int coef1d_size);

// Row filter and then transpose
int row_filter_transpose(
	float * src, 
	float * dst, 
	int w, int h,
	float * coef1d, int gR);

// Compute Gaussian filter coefficients for Gaussian Blur.
void compute_gaussian_coefs(int nGpyrLayers,
			    int * columns_sizes,
			    float ** gaussian_coefs);

// Build Gaussian pyramid.
int build_gaussian_pyramid(
	struct ImageObj<unsigned char> ** octaves,
	struct ImageObj<float> ** gpyr, 
	int nOctaves, 
	int nGpyrLayers);

// Build DoG pyramid. 
int build_dog_pyr(
	struct ImageObj<float> ** gpyr, 
	struct ImageObj<float> ** dogPyr, 
	int nOctaves, 
	int nDogLayers);

// Build gradient and rotation pyramid.
int build_grd_rot_pyr(
	struct ImageObj<float> ** gpyr, 
	struct ImageObj<float> ** grdPyr, 
	struct ImageObj<float> ** rotPyr, 
	int nOctaves, 
	int nLayers);

// Refine local extrema.
bool refine_local_extrema(
	struct ImageObj<float> ** dogPyr, 
	int nOctaves, 
	int nDogLayers, 
	struct SiftKeypoint * kpt);

// Export keypoint list to a file.
int export_kpt_list_to_file(
	const char * filename, 
	struct OrderedList<struct SiftKeypoint> * kpt_list,
	bool bIncludeDescriptor);

// Compute orientation histogram.
float compute_orientation_hist_with_gradient(
	struct ImageObj<float> * grdImage, 
	struct ImageObj<float> * rotImage, 
	struct SiftKeypoint * kpt,
	float * hist);


/****************************************
 *  SIFT Core Functions
 ***************************************/
// Detect keypoints.
int detect_keypoints(
	struct ImageObj<float> ** dogPyr, 
	struct ImageObj<float> ** grdPyr, 
	struct ImageObj<float> ** rotPyr, 
	int nOctaves, 
	int nDogLayers, 
	struct OrderedList<struct SiftKeypoint> * kpt_list);

// Extract descriptor.
int extract_descriptor(
	struct ImageObj<float> ** grdPyr, 
	struct ImageObj<float> ** rotPyr, 
	int nOctaves,
	int nGpyrLayers,
	struct OrderedList<struct SiftKeypoint> * kpt_list);


/****************************************
 *  SIFT Interface Functions
 ***************************************/
// Detect keypoints and extract descriptor.
int sift_cpu(
	struct ImageObj<unsigned char> * image, 
	struct OrderedList<struct SiftKeypoint> * kpt_list, 
	bool bExtractDescriptors);

// Match keypoints from two keypoint lists.
int match_keypoints(
	struct OrderedList<struct SiftKeypoint> * kpt_list1,
	struct OrderedList<struct SiftKeypoint> * kpt_list2,
	struct OrderedList<struct MatchPair> * match_list);



// added ahonorat
template <typename T>
struct ImageObj<T> ** createArrayImg(int number) {
  ImageObj<T> ** tab = (ImageObj<T> **) malloc(sizeof(ImageObj<T> *)*(number+1));
  for (int i = 0; i < number; ++i) {
    tab[i] = CreateImage<T>();
  }
  tab[number] = NULL;
  return tab;
}

template <typename T>
void freeArrayImg(ImageObj<T> ** tab){
  int i = 0;
  while (tab[i] != NULL) {
    release(tab[i]);
    ++i;
  }
  free(tab);
}

template <typename T>
inline T tmin(T n1, T n2) {
  if (n1 < n2) {
    return n1;
  }
  return n2;
}

template <typename T>
inline T tmax(T n1, T n2) {
  if (n1 < n2) {
    return n2;
  }
  return n1;
}


#endif
