#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/ARM_CortexA7.h"
#include "image.h"
#include "v4l2uvc.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void _getBrightness(const Mat& frame, double& brightness);
void matToRGB(Mat openCVImage,rgbimg * outimg);
Mat RGBToMat(rgbimg* img);

#define array_size(x)  (sizeof(x) / sizeof((x)[0]))
const char* displays[] = { "output", "output1", "output2" };

void initDisplays() {
	for (unsigned int i = 0; i < array_size(displays); i++) {
		namedWindow(displays[i], 1);
	}
}

VideoCapture* cap;
VideoCapture* cap1;
VideoCapture* cap2;
void initRead() {
//	cap = new VideoCapture(0);
//	cap1 = new VideoCapture(1);
//	cap2 = new VideoCapture(2);
}

void read(rgbimg* img) {

	cam(img->r, img->g, img->b, XSAMPLING, YSAMPLING, 0);
}

void computeBrightness(rgbimg * img, double * b) {
	Mat src =  RGBToMat(img);
	_getBrightness(src, *b);
	src.release();
}

void display(rgbimg * img, unsigned int displayID) {
	Mat m = RGBToMat(img);
	imshow(displays[displayID], m);
	waitKey(1);
	m.release();
}

void computeBrightnessAndForward(IN rgbimg * img_in, OUT double * brightness, OUT rgbimg * img_out) {
	computeBrightness(img_in, brightness);
	memcpy(img_out, img_in, sizeof(rgbimg));
}

void configActor(IN double * brightness, long * param) {
	if ((*brightness) > 0.8) {
		*param = 1;
	} else {
		*param = 0;
	}
}

void blur(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter) {
	if (someParameter) {
		Mat m = RGBToMat(img_in);
	    GaussianBlur(m, m, Size(7,7), 1.5, 1.5);
		matToRGB(m, img_out);
	} else {
		memcpy(img_out, img_in, sizeof(rgbimg));
	}
}

void canny(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter) {
	if (someParameter) {
		Mat m = RGBToMat(img_in);
        Canny(m,m,100,200);
        cvtColor(m,m,COLOR_GRAY2RGB);
		matToRGB(m, img_out);
		m.release();
	} else {
		memcpy(img_out, img_in, sizeof(rgbimg));
	}
}

void sobel(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter) {
	if (someParameter) {
		Mat m = RGBToMat(img_in);
	    int scale = 1;
	    int delta = 0;
	    int ddepth = CV_16S;
	    Sobel( m, m, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
	    matToRGB(m, img_out);
		m.release();
	} else {
		memcpy(img_out, img_in, sizeof(rgbimg));
	}
}

void splitRGB(IN rgbimg * img_in, OUT unsigned char * R, OUT unsigned char * G, OUT unsigned char * B) {
	memcpy(R, img_in->r, XSAMPLING * YSAMPLING);
	memcpy(G, img_in->g, XSAMPLING * YSAMPLING);
	memcpy(B, img_in->b, XSAMPLING * YSAMPLING);
}


void mergeRGB(IN unsigned char * R, IN unsigned char * G, IN unsigned char * B, OUT rgbimg * img_out) {
	memcpy(img_out->r, R, XSAMPLING * YSAMPLING);
	memcpy(img_out->g, G, XSAMPLING * YSAMPLING);
	memcpy(img_out->b, B, XSAMPLING * YSAMPLING);
}

void doSomething(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter) {
	if (someParameter) {
		Mat m = RGBToMat(img_in);
		matToRGB(m, img_out);
		m.release();
	} else {
		memcpy(img_out, img_in, sizeof(rgbimg));
	}
}
