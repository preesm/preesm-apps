#include <time.h>
#include <stdio.h>

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
	brightness = summ[0]/((pow(2,8)-1)*frame.rows * frame.cols) * 2;
}

#define XSAMPLING 800
#define YSAMPLING 600

typedef struct {
	unsigned char r[XSAMPLING * YSAMPLING];
	unsigned char g[XSAMPLING * YSAMPLING];
	unsigned char b[XSAMPLING * YSAMPLING];
} rgbimg;

rgbimg * matToRGB(Mat openCVImage) {

	rgbimg* res = (rgbimg*) malloc(sizeof(rgbimg));
	int h = openCVImage.size().height;
	int w = openCVImage.size().width;
	for (int y = 0; y < h; ++y) {

	   // Option 1: get a pointer to a 3-channel element
	   cv::Vec3b* pointerToRgbPixel = openCVImage.ptr<cv::Vec3b>(y);

	   for (int x = 0; x < w; ++x, ++pointerToRgbPixel) {

	       uint8_t blue = (*pointerToRgbPixel )[0];
	       uint8_t green = (*pointerToRgbPixel )[1];
	       uint8_t red = (*pointerToRgbPixel )[2];
	       res->r[y*w + x] = red;
	       res->g[y*w + x] = green;
	       res->b[y*w + x] = blue;

	       //DoSomething(red, green, blue);
	   }
	}
	return res;
}

unsigned char * interleave(rgbimg* img) {
	unsigned char * res = (unsigned char *) malloc (XSAMPLING * YSAMPLING * 3);

	for (int y = 0; y < YSAMPLING; y++) {
		for (int x = 0; x < XSAMPLING; x++) {
			res[(y * XSAMPLING + x) * 3 + 0] = img->b[y * XSAMPLING + x];
			res[(y * XSAMPLING + x) * 3 + 1] = img->g[y * XSAMPLING + x];
			res[(y * XSAMPLING + x) * 3 + 2] = img->r[y * XSAMPLING + x];
		}
	}

	return res;
}

int main(int, char**) {
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	namedWindow("input", 1);
	namedWindow("resized", 1);
	namedWindow("trans", 1);
	for (;;) {
		Mat inputFrame;
		cap >> inputFrame; // get a new frame from camera
		imshow("input", inputFrame);
		//resize frame to the specified sampling size
		Mat resizedFrame;
		resize(inputFrame, resizedFrame, Size(XSAMPLING, YSAMPLING), INTER_LINEAR);

		//compute brightness
		double brightness;
		_getBrightness(resizedFrame, brightness);

		char str[21];
		sprintf(str, "brightness = %7.4f", brightness);
		putText(resizedFrame, str, cvPoint(20, 20), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255, 255, 255), 1, CV_AA);

		imshow("resized", resizedFrame);


//		Mat grayFrame;
        cvtColor(resizedFrame, resizedFrame, COLOR_BGR2GRAY);

		rgbimg * rrr = matToRGB(resizedFrame);
		unsigned char* pixels = interleave(rrr);

		Mat src =  Mat(YSAMPLING,XSAMPLING, CV_8UC3, pixels);
		imshow("trans", src);


		if (waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
