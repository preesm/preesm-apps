#include <time.h>
#include <stdio.h>

#include "image.h"

#define array_size(x)  (sizeof(x) / sizeof((x)[0]))
const char* displays[] = { "input" }; //, "resized", "transfered" };

void initDisplays() {
	for (unsigned int i = 0; i < array_size(displays); i++) {
		namedWindow(displays[i], 1);
	}
}

VideoCapture* cap;
int initRead() {
	cap = new VideoCapture(0);
	if (!cap->isOpened())
		return -1;
	return 0;
}

void read(rgbimg* img) {
	Mat inputFrame;
	(*cap) >> inputFrame;
//	imshow("input",inputFrame);
	Mat resizedFrame;
	resize(inputFrame, resizedFrame, Size(XSAMPLING, YSAMPLING), INTER_LINEAR);
//	imshow("resized",resizedFrame);
	matToRGB(resizedFrame, img);
}

void computeBrightness(rgbimg * img, double * b) {
	Mat src =  RGBToMat(img);
	_getBrightness(src, *b);
}

void display(rgbimg * img, unsigned int displayID) {
	Mat m = RGBToMat(img);
	imshow(displays[displayID], m);
}

char Shared[2880000]; //  size:= 2880000*char
char *const Read__broadcast__0 = (char*) (Shared+0);  // Read > broadcast size:= 1440000*char
char *const broadcast__Display__0 = (char*) (Shared+1440000);  // broadcast > Display size:= 1440000*char
rgbimg *const img__in__0 = (rgbimg*) (Shared+0);  // Read_img > broadcast_in size:= 1440000*rgbimg
rgbimg *const out1_0_0__img__0 = (rgbimg*) (Shared+1440000);  // broadcast_out1_0_0 > Display_img size:= 1440000*rgbimg


void doSomething(IN rgbimg * img_in, OUT rgbimg * img_out, int someParameter) {
	if (someParameter) {
		Mat m = RGBToMat(img_in);

        cvtColor(m, m, COLOR_BGR2GRAY);
        GaussianBlur(m, m, Size(7,7), 1.5, 1.5);
        Canny(m, m, 0, 30, 3);

		matToRGB(m, img_out);
	} else {
		memcpy(img_out, img_in, sizeof(rgbimg));
	}
}

int main(int, char**) {
	initDisplays();
	initRead();
	unsigned long int size = sizeof(rgbimg);
	int ss = (int) size;
	printf("sizeof = %d\n",ss);
	for (;;) {
		read(img__in__0);


		memcpy(out1_0_0__img__0+0, img__in__0+0, 1*sizeof(rgbimg));

		doSomething(out1_0_0__img__0, img__in__0, 1);

		display(img__in__0, 0);
		if (waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
