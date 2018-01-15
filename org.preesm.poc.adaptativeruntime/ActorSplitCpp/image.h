
#ifndef _img_h_
#define _img_h_

#include "adaptive_runtime.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

typedef struct {
	unsigned char r[XSAMPLING * YSAMPLING];
	unsigned char g[XSAMPLING * YSAMPLING];
	unsigned char b[XSAMPLING * YSAMPLING];
} rgbimg;


void _getBrightness(const Mat& frame, double& brightness);
void matToRGB(Mat openCVImage,rgbimg * outimg);
Mat RGBToMat(rgbimg* img);

#endif
