
#include "image.h"


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


// see http://answers.opencv.org/question/24260/how-to-determine-an-image-with-strong-or-weak-illumination-in-opencv/
// and https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color
void _getBrightness(const Mat& frame, double& brightness) {
	Mat temp, color[3], lum;
	temp = frame;
	split(temp, color);
	color[0] = color[0] * 0.299;
	color[1] = color[1] * 0.587;
	color[2] = color[2] * 0.114;
	lum = color[0] + color [1] + color[2];
	Scalar summ = sum(lum);
	//-- percentage conversion factor
	brightness = summ[0]/(((256.0-1)*frame.rows * frame.cols)) * 2;
	temp.release();
	color[0].release();
	color[1].release();
	color[2].release();
	lum.release();
}

// https://stackoverflow.com/questions/27114425/opencv-convert-rgb-matrix-to-1d-array
void matToRGB(Mat openCVImage, rgbimg* outimg) {
	for (int y = 0; y < YSAMPLING; ++y) {
	   cv::Vec3b* pointerToRgbPixel = openCVImage.ptr<cv::Vec3b>(y);
	   for (int x = 0; x < XSAMPLING; ++x, ++pointerToRgbPixel) {
	       uint8_t blue = (*pointerToRgbPixel )[0];
	       uint8_t green = (*pointerToRgbPixel )[1];
	       uint8_t red = (*pointerToRgbPixel )[2];
	       outimg->r[y*XSAMPLING + x] = red;
	       outimg->g[y*XSAMPLING + x] = green;
	       outimg->b[y*XSAMPLING + x] = blue;
	   }
	}
	openCVImage.release();
}

Mat RGBToMat(rgbimg* img) {
	unsigned char * res = (unsigned char *) malloc (XSAMPLING * YSAMPLING * 3);
	for (int y = 0; y < YSAMPLING; y++) {
		for (int x = 0; x < XSAMPLING; x++) {
			res[(y * XSAMPLING + x) * 3 + 0] = img->b[y * XSAMPLING + x];
			res[(y * XSAMPLING + x) * 3 + 1] = img->g[y * XSAMPLING + x];
			res[(y * XSAMPLING + x) * 3 + 2] = img->r[y * XSAMPLING + x];
		}
	}
	Mat src =  Mat(YSAMPLING,XSAMPLING, CV_8UC3, res).clone();
	free(res);
	return src;
}
